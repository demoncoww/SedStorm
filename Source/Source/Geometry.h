#ifndef __GEOMETRY__HPP__
#define __GEOMETRY__HPP__

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <list>
#include <cmath>
#include <limits>
#include <algorithm>
#include <queue>
#include <string>
using std::vector;
using std::queue;
using std::string;

/*	This namespace has the following high level functions available:

	// This function will slice a polygon(convex or concave) into multiple polygons
	std::vector<std::vector<Point>> Slice(std::vector<Point> points, Point p1, Point p2);

	// Separates a non-convex polygon into convex polygons and adds them as fixtures to the 'body' parameter
	b2Body* Separate(b2World& world, b2BodyDef& bodyDef, b2FixtureDef& fixtureDef, vector<b2Vec2>& vertices, unsigned int scale = 30);

	// makes sure there are no overlapping segments and the vertices are in CCW order
	int Validate(vector<b2Vec2>& verts);

	// breaks down a simple concave polygon into a vector of convex polygons
	vector<vector<b2Vec2>> CalcShapes(vector<b2Vec2>& verts);
*/
	
namespace Geometry
{
	// function prototypes
	float det(float x1, float y1, float x2, float y2, float x3, float y3);
	bool isOnLine(float px, float py, float x1, float y1, float x2, float y2);
	bool pointsMatch(float x1, float y1, float x2, float y2);
	bool isOnSegment(float px, float py, float x1, float y1, float x2, float y2);
	template <typename VectorType>
	VectorType hitRay(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	template <typename VectorType>
	VectorType hitSegment(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	template <typename VectorType>
	vector<vector<VectorType>> CalcShapes(vector<VectorType> const& verts);
	void err(void);

	/*
    * Convex Separator for Box2D Flash
    *
    * This class has been written by Antoan Angelov.
    * It is designed to work with Erin Catto's Box2D physics library.
    *
    * Everybody can use this software for any purpose, under two restrictions:
    * 1. You cannot claim that you wrote this software.
    * 2. You can not remove or alter this notice.
    *
    */

    // Modied by David Lazell for C++

    /**
    * Separates a non-convex polygon into convex polygons and adds them as fixtures to the 'body' parameter.
    * There are some rules you should follow (otherwise you might get unexpected results) :
    *
    * This class is specifically for non-convex polygons.
    * The vertices must be in counter-clockwise order.
    * No three neighbouring points should lie on the same line segment.
    * There must be no overlapping segments and no "holes".
    *
    * @param world : A b2World to add the new body to.
    * @param bodyDef : A b2bodyDef, containing all the properties (type, position, etc.) which the new body will inherit.
    * @param fixtureDef : A b2FixtureDef, containing all the properties (friction, density, etc.) which the new fixtures will inherit.
    * @param vertices : The vertices of the non-convex polygon, in CCW order.
    * @param scale : [optional] The scale which you use to draw shapes in Box2D. The bigger the scale, the better the precision. The default value is 30.
    * @return A b2Body* of the body that was added to the world.
    * */
	template <typename VectorType>
	b2Body* Separate(b2World& world, b2BodyDef& bodyDef, b2FixtureDef& fixtureDef, vector<VectorType>& vertices, unsigned int scale = 30) {
        int n = vertices.size();
        vector<VectorType> vec;
		b2Vec2* b2Points = (b2Vec2*)alloca(sizeof(b2Vec2) * vertices.size());

        for (int i = 0; i<n; ++i)
            vec.push_back(VectorType(vertices[i].x * scale, vertices[i].y * scale));

        vector<vector<VectorType>> figsVec = CalcShapes(vec);

        b2Body* body = world.CreateBody(&bodyDef);

        for (auto const& vec : figsVec) {
            vector<VectorType> verticesVec;
            for (unsigned int i = 0; i < vec.size(); ++i)
                verticesVec.push_back(VectorType(vec[i].x / scale, vec[i].y / scale));

            b2PolygonShape b2Shape;
            unsigned int numVerts = verticesVec.size();
            for (unsigned int i = 0; i < numVerts; ++i)
				b2Points[i] = b2Vec2(verticesVec[i].x, verticesVec[i].y);
            b2Shape.Set(b2Points, numVerts);

            fixtureDef.shape = &b2Shape;
            //fixtureDef.density = 1;
            body->CreateFixture(&fixtureDef);
        }
        return body;
    }

    /**
    * Checks whether the vertices in 'verticesVec' can be properly distributed into the new fixtures
    *  (more specifically, it makes sure there are no overlapping segments and the vertices are in CCW order).
    * It is recommended that you use this method for debugging only, because it may cost more CPU usage.
    *
    * @param verts : The vertices to be validated.
    * @return : An integer which can have the following values:
    *
    * 0 if the vertices can be properly processed.
    * 1 If there are overlapping lines.
    * 2 if the points are _not_ in CCW order.
    * 3 if there are overlapping lines _and_ the points are _not_ in CCW order.
    *
    * */

	template <typename VectorType>
	int Validate(vector<VectorType>& verts) {
        int n = verts.size();
        int ret = 0;
        bool fl2 = false;

        for (int i = 0; i < n; ++i) {
            int i2 = (i<n - 1 ? i + 1 : 0);
            int i3 = (i>0 ? i - 1 : n - 1);

            bool fl = false;
            for (int j = 0; j < n; ++j) {
                if (j != i && j != i2) {
                    if (!fl) {
                        float d = det(verts[i].x, verts[i].y, verts[i2].x, verts[i2].y, verts[j].x, verts[j].y);
                        if (d < 0)
                            fl = true;
                    }
                    if (j != i3) {
                        int j2 = (j < n - 1 ? j + 1 : 0);
						VectorType hit = hitSegment<VectorType>(verts[i].x, verts[i].y, verts[i2].x, verts[i2].y, verts[j].x, verts[j].y, verts[j2].x, verts[j2].y);
                        if (hit.x != 0.0f || hit.y != 0.0f)
                            ret = 1;
                    }
                }
            }
            if (!fl)
                fl2 = true;
        }

        if (fl2) {
            if (ret == 1)
                ret = 3;
            else
                ret = 2;
        }

        return ret;
    }

    // breaks down a simple concave polygon into a vector of convex polygons
    template <typename VectorType>
	vector<vector<VectorType>> CalcShapes(vector<VectorType> const& verts) {
        vector<vector<VectorType>> figsVec;
        queue<vector<VectorType>> queue;
        queue.push(verts);

        while (!queue.empty()) {
            vector<VectorType> vec = queue.front();
            int n = vec.size();
            bool isConvex = true;

            for (int i = 0; i < n; ++i) {
                int i1 = i;
                int i2 = (i<n - 1 ? i + 1 : i + 1 - n);
                int i3 = (i<n - 2 ? i + 2 : i + 2 - n);

                VectorType& p1 = vec[i1];
                VectorType& p2 = vec[i2];
                VectorType& p3 = vec[i3];

                float d = det(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
                if (d > 0) {
                    isConvex = false;
                    float minLen = std::numeric_limits<float>::max();
                    VectorType hitV;
                    int h, k, j1, j2;

                    for (int j = 0; j < n; ++j) {
                        if (j != i1 && j != i2) {
                            j1 = j;
                            j2 = (j < n - 1 ? j + 1 : 0);

                            VectorType& v1 = vec[j1];
                            VectorType& v2 = vec[j2];

							VectorType v = hitRay<VectorType>(p1.x, p1.y, p2.x, p2.y, v1.x, v1.y, v2.x, v2.y);

                            if (v.x != 0.0f || v.y != 0.0f) {
                                float dx = p2.x - v.x;
                                float dy = p2.y - v.y;
                                float t = dx*dx + dy*dy;

                                if (t < minLen) {
                                    h = j1;
                                    k = j2;
                                    hitV = v;
                                    minLen = t;
                                }
                            }
                        }
                    }

                    if (minLen == std::numeric_limits<float>::max())
                        err();

                    vector<VectorType> vec1, vec2;

                    j1 = h;
                    j2 = k;
                    VectorType v1 = vec[j1];
                    VectorType v2 = vec[j2];

                    if (!pointsMatch(hitV.x, hitV.y, v2.x, v2.y))
                        vec1.push_back(hitV);
                    if (!pointsMatch(hitV.x, hitV.y, v1.x, v1.y))
                        vec2.push_back(hitV);

                    h = -1;
                    k = i1;
                    while (true) {
                        if (k != j2)
                            vec1.push_back(vec[k]);
                        else {
                            if (h<0 || h >= n)
                                err();
                            if (!isOnSegment(v2.x, v2.y, vec[h].x, vec[h].y, p1.x, p1.y))
                                vec1.push_back(vec[k]);
                            break;
                        }

                        h = k;
                        if (k - 1 < 0) k = n - 1;
                        else k--;
                    }

                    std::reverse(vec1.begin(), vec1.end());

                    h = -1;
                    k = i2;
                    while (true) {
                        if (k != j1)
                            vec2.push_back(vec[k]);
                        else {
                            if (h < 0 || h >= n)
                                err();
                            if (k == j1 && !isOnSegment(v1.x, v1.y, vec[h].x, vec[h].y, p2.x, p2.y))
                                vec2.push_back(vec[k]);
                            break;
                        }

                        h = k;
                        if (k + 1 > n - 1) k = 0;
                        else ++k;
                    }

                    queue.push(vec1);
                    queue.push(vec2);
                    queue.pop();
                    break;
                }
            }
            if (isConvex) {
                figsVec.push_back(queue.front());
                queue.pop();
            }
        }
        return figsVec;
    }

	template <typename VectorType>
	VectorType hitRay(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
        float t1 = x3 - x1;
        float t2 = y3 - y1;
        float t3 = x2 - x1;
        float t4 = y2 - y1;
        float t5 = x4 - x3;
        float t6 = y4 - y3;
        float t7 = t4*t5 - t3*t6;
        float a = (t5*t2 - t6*t1) / t7;
        float px = x1 + a*t3;
        float py = y1 + a*t4;
        bool b1 = isOnSegment(x2, y2, x1, y1, px, py);
        bool b2 = isOnSegment(px, py, x3, y3, x4, y4);

        if (b1 && b2)
            return VectorType(px, py);

        return
            VectorType(0.0f, 0.0f);
    }

	template <typename VectorType>
	VectorType hitSegment(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
        float t1 = x3 - x1;
        float t2 = y3 - y1;
        float t3 = x2 - x1;
        float t4 = y2 - y1;
        float t5 = x4 - x3;
        float t6 = y4 - y3;
        float t7 = t4*t5 - t3*t6;
        float a = (t5*t2 - t6*t1) / t7;
        float px = x1 + a*t3;
        float py = y1 + a*t4;
        bool b1 = isOnSegment(px, py, x1, y1, x2, y2);
        bool b2 = isOnSegment(px, py, x3, y3, x4, y4);

        if (b1 && b2)
            return VectorType(px, py);

        return
            VectorType(0.0f, 0.0f);
    }
}
#endif // __GEOMETRY__HPP__