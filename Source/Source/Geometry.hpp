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

namespace Geometry
{
    // The following code was translated from http://polyk.ivank.net/polyk.js
    // This static library will be used to slice both concave and convex polygons

    struct Point
    {
        float x;
        float y;
        bool flag;

        Point() : x(0.0f), y(0.0f), flag(false) { }
        Point(float _x, float _y) : x(_x), y(_y), flag(false) { }

        inline bool operator==(Point const &other) { return (x == other.x && y == other.y && flag == other.flag); }
    };

    //Axis-aligned Bounding Box
    struct AABB
    {
        float x;
        float y;
        float width;
        float height;
    };

    // a in rectangle (b, c)
    bool inRectangle(Point a, Point b, Point c) {
        float minx = fmin(b.x, c.x), maxx = fmax(b.x, c.x);
        float miny = fmin(b.y, c.y), maxy = fmax(b.y, c.y);

        if (minx == maxx) return (miny <= a.y && a.y <= maxy);
        if (miny == maxy) return (minx <= a.x && a.x <= maxx);

        return (minx <= a.x + 1e-10 && a.x - 1e-10 <= maxx && miny <= a.y + 1e-10 && a.y - 1e-10 <= maxy);
    }


    bool convex(Point a, Point b, Point c) {
        return (a.y - b.y) * (c.x - b.x) + (b.x - a.x) * (c.y - b.y) > 0;
    }

    std::vector<Point> getPoints(std::vector<Point> points, int ind0, int ind1) {
        unsigned int n = points.size();
        std::vector<Point> nps;
        if (ind1 < ind0) ind1 += n;
        for (int i = ind0; i <= ind1; i++) nps.push_back(points[i%n]);
        return nps;
    }

    int firstWithFlag(std::vector<Point> points, int index) {
        int n = points.size();
        for (;;) {
            index = (index + 1) % n;
            if (points[index].flag) return index;
        }
    }

    float squaredDistance(Point a, Point b) {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        return ((dx * dx + dy * dy));
    }

    bool hasLineIntersection(Point a1, Point a2, Point b1, Point b2, Point &I) {
        float dax = (a1.x - a2.x), dbx = (b1.x - b2.x);
        float day = (a1.y - a2.y), dby = (b1.y - b2.y);

        float Den = dax * dby - day * dbx;
        if (Den == 0) return false;	// parallel

        float A = (a1.x * a2.y - a1.y * a2.x);
        float B = (b1.x * b2.y - b1.y * b2.x);

        I.x = (A*dbx - dax*B) / Den;
        I.y = (A*dby - day*B) / Den;

        if (inRectangle(I, a1, a2) && inRectangle(I, b1, b2)) {
            return true;
        }
        return false;
    }

    bool pointInTriangle(Point point, Point tri1, Point tri2, Point tri3) {
        float v0x = tri3.x - tri1.x;
        float v0y = tri3.y - tri1.y;
        float v1x = tri2.x - tri1.x;
        float v1y = tri2.y - tri1.y;
        float v2x = point.x - tri1.x;
        float v2y = point.y - tri1.y;

        float dot00 = v0x * v0x + v0y * v0y;
        float dot01 = v0x * v1x + v0y * v1y;
        float dot02 = v0x * v2x + v0y * v2y;
        float dot11 = v1x * v1x + v1y * v1y;
        float dot12 = v1x * v2x + v1y * v2y;

        float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
        float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

        // Check if point is in triangle
        return (u >= 0) && (v >= 0) && (u + v < 1);
    }

    //Returns true when its edges don't cross each other
    bool isSimple(std::vector<Point> points) {
        int n = points.size(); //
        if (n < 3) return true;	// simple if it is a triangle
        Point a1, a2, b1, b2;
        Point c;

        for (int i = 0; i < n; ++i) {
            a1.x = points[i].x;
            a1.y = points[i].y;
            if (i == n - 1) {
                a2.x = points[0].x;
                a2.y = points[0].y;
            } else {
                a2.x = points[i + 1].x;
                a2.y = points[i + 1].y;
            }

            for (int j = 0; j < n; ++j) {
                if (abs(i - j) < 2) continue;
                if (j == n - 1 && i == 0) continue;
                if (i == n - 1 && j == 0) continue;

                b1.x = points[j].x;
                b1.y = points[j].y;
                if (j == n - 1) {
                    b2.x = points[0].x;
                    b2.y = points[0].y;
                } else {
                    b2.x = points[j + 1].x;
                    b2.y = points[j + 1].y;
                }

                //if the intersection point doesn't exist in rectangle (a1, a2) or rectangle (b1, b2)
                if (hasLineIntersection(a1, a2, b1, b2, c)) return false;
            }
        }
        return true;
    }

    //Checks if polygon is convex. Polygon is convex, when each inner angle is <= 180°
    bool isConvex(std::vector<Point> points) {
        if (points.size() < 3) return true;
        int n = points.size() - 2; //second to last index
        for (int i = 0; i < n; i++) {
            if (!convex(points[i], points[i + 1], points[i + 2])) return false;
        }
        if (!convex(points[n], points[n + 1], points[0])) return false;
        if (!convex(points[n + 1], points[0], points[2])) return false;
        return true;
    }

    //verified it works for rectangle or trapazoid
    float getArea(std::vector<Point> points) {
        if (points.size() < 3) return 0;
        int n = points.size() - 1; //last index
        float sum = 0;
        for (int i = 0; i < n; i++) {
            sum += (points[i + 1].x - points[i].x) * (points[i + 1].y + points[i].y);
        }
        sum += (points[0].x - points[n].x) * (points[0].y + points[n].y);
        return (-sum * 0.5f);
    }

    AABB calculateAABB(std::vector<Point> points) {
        float minx = std::numeric_limits<float>::max();
        float miny = std::numeric_limits<float>::max();
        float maxx = -minx;
        float maxy = -miny;
        for (unsigned int i = 0; i < points.size(); i++) {
            minx = fmin(minx, points[i].x);
            maxx = fmax(maxx, points[i].x);
            miny = fmin(miny, points[i].y);
            maxy = fmax(maxy, points[i].y);
        }
        AABB aabb;
        aabb.x = minx;
        aabb.y = miny;
        aabb.width = maxx - minx;
        aabb.height = maxy - miny;
        return aabb;
    }

    //Returns a vector of ints in the format [a.1, a.2, a.3, b.1, b.2, b.3 ...]
    //Where each 3 consecutive elements are indices of the polygon that will create a triangle
    //Example - Polygon = [(0,0), (1,0), (1,1), (0,1)]
    //			Polygon.triangulate = [0,1,2,  0,2,3]
    std::vector<int> triangulate(std::vector<Point> points) {
        std::vector<int> tgs;
        std::vector<int> avl;
        int n = points.size();
        if (n < 2) return tgs; // return empty vector if there's only one point in Polygon
        for (int i = 0; i < n; ++i) { avl.push_back(i); }

        int i = 0;
        int al = n;
        while (al > 3) {
            int i0 = avl[(i + 0) % al];
            int i1 = avl[(i + 1) % al];
            int i2 = avl[(i + 2) % al];

            //points of triangle
            Point a = points[i0];
            Point b = points[i1];
            Point c = points[i2];
            bool earFound = false;

            if (convex(a, b, c)) {
                for (int j = 0; j < al; ++j) {
                    int vi = avl[j];
                    if (vi == i0 || vi == i1 || vi == i2) continue;
                    if (pointInTriangle(points[vi], a, b, c)) {
                        earFound = false; break;
                    }
                }
            }
            if (earFound) {
                tgs.push_back(i0);
                tgs.push_back(i1);
                tgs.push_back(i2);

                avl.erase(avl.begin() + ((i + 1) % al));	//remove element from vector
                al--;
                i = 0;
            } else if (i++ > 3 * al) break;	//no convex angles
        }
        tgs.push_back(avl[0]);
        tgs.push_back(avl[1]);
        tgs.push_back(avl[2]);
        return tgs;
    }

    bool containsPoint(std::vector<Point> points, Point pt) {
        int n = points.size();
        float ax;
        float ay = points[n - 2].y - pt.y;
        float bx = points[n - 1].x - pt.x;
        float by = points[n - 1].y - pt.y;

        bool lup;
        for (int i = 0; i < n; ++i) {
            ax = bx;
            ay = by;
            bx = points[i].x - pt.x;
            by = points[i].y - pt.y;
            if (ay == by) continue;
            lup = by > ay;
        }

        int depth = 0;
        for (int i = 0; i<n; i++) {
            ax = bx;
            ay = by;
            bx = points[i].x - pt.x;
            by = points[i].y - pt.y;
            if (ay < 0 && by < 0) continue;	// both "up" or both "down"
            if (ay > 0 && by > 0) continue;	// both "up" or both "down"
            if (ax < 0 && bx < 0) continue; // both points on the left

            if (ay == by && fmin(ax, bx) <= 0) return true;
            if (ay == by) continue;

            float lx = ax + (bx - ax) * (-ay) / (by - ay);
            if (lx == 0) return true;				 // point on edge
            if (lx > 0) depth++;
            if (ay == 0 && lup && by > ay) depth--;	 // hit vertex, both up
            if (ay == 0 && !lup && by < ay) depth--; // hit vertex, both down
            lup = by>ay;
        }

        return (depth & 1) == 1; // check what this does
    }

    // This function will slice a polygon(convex or concave) into multiple polygons 
    std::vector<std::vector<Point>> slice(std::vector<Point> points, Point p1, Point p2) {
        std::vector<std::vector<Point>> result;
        std::vector<Point> iscs;	// intersection points

        //Adds instersected points to the polygon
        for (unsigned int i = 0; i < points.size(); i++) {
            Point isc;
            bool intersected = hasLineIntersection(p1, p2, points[i], points[(i + 1) % points.size()], isc);

            if (intersected && (iscs.size() == 0 || squaredDistance(isc, iscs[0]) > 1e-10) && (iscs.size() == 0 || squaredDistance(isc, iscs[iscs.size() - 1]) > 1e-10)) {
                isc.flag = true;
                iscs.push_back(isc);
                points.insert(points.begin() + (i + 1), isc);
                i++;
            }
        }

        if (iscs.size() < 2) return result;
        std::sort(iscs.begin(), iscs.end(), [p1](Point u, Point v)-> bool {
            return squaredDistance(p1, u) < squaredDistance(p1, v);
        });

        int dir = 0;
        //While there are two or more intersections pionts on the polygon edges
        while (iscs.size() >= 2) {
            int n = points.size();
            Point i0 = iscs[0], i1 = iscs[1]; //first and second intersection points to deal with
            auto it = std::find(points.begin(), points.end(), iscs[0]);
            auto it2 = std::find(points.begin(), points.end(), iscs[1]);
            int ind0, ind1;
            bool solved = false;
            if (it != points.end())
                ind0 = (it - points.begin());
            if (it2 != points.end())
                ind1 = (it2 - points.begin());

            if (firstWithFlag(points, ind0) == ind1) solved = true;
            else {
                i0 = iscs[1];
                i1 = iscs[0];
                it = std::find(points.begin(), points.end(), iscs[0]);
                it2 = std::find(points.begin(), points.end(), iscs[1]);
                if (it != points.end())
                    ind0 = (it - points.begin());
                if (it2 != points.end())
                    ind1 = (it2 - points.begin());
                if (firstWithFlag(points, ind0) == ind1) solved = true;
            }
            if (solved) {
                dir--;
                points[ind0].flag = points[ind1].flag = false;
                result.push_back(getPoints(points, ind0, ind1));	//push new polygon 
                points = getPoints(points, ind1, ind0);				//update old polygon
                iscs.erase(iscs.begin(), iscs.begin() + 2);			// removes first two elements from iscs
                if (iscs.size() == 0) result.push_back(points);
            } else {
                dir++;
                std::reverse(iscs.begin(), iscs.end());
            }
            if (dir > 1) break;
        }
        return result;
    }

    // function prototypes
    inline float det(float x1, float y1, float x2, float y2, float x3, float y3);
    bool isOnLine(float px, float py, float x1, float y1, float x2, float y2);
    bool pointsMatch(float x1, float y1, float x2, float y2);
    bool isOnSegment(float px, float py, float x1, float y1, float x2, float y2);
    b2Vec2 hitRay(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    b2Vec2 hitSegment(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    vector<vector<b2Vec2>> calcShapes(vector<b2Vec2>& verts);
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
    b2Body* Separate(b2World& world, b2BodyDef& bodyDef, b2FixtureDef& fixtureDef, vector<b2Vec2>& vertices, unsigned int scale = 30) {
        int n = vertices.size();
        vector<b2Vec2> vec;
        b2Vec2 *b2Points = (b2Vec2*)alloca(sizeof(b2Vec2) * vertices.size());

        for (int i = 0; i<n; ++i)
            vec.push_back(b2Vec2(vertices[i].x * scale, vertices[i].y * scale));

        vector<vector<b2Vec2>> figsVec = calcShapes(vec);

        b2Body* body = world.CreateBody(&bodyDef);

        for (auto const& vec : figsVec) {
            vector<b2Vec2> verticesVec;
            for (unsigned int i = 0; i < vec.size(); ++i)
                verticesVec.push_back(b2Vec2(vec[i].x / scale, vec[i].y / scale));

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

    int Validate(vector<b2Vec2>& verts) {
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
                        b2Vec2 hit = hitSegment(verts[i].x, verts[i].y, verts[i2].x, verts[i2].y, verts[j].x, verts[j].y, verts[j2].x, verts[j2].y);
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
    vector<vector<b2Vec2>> calcShapes(vector<b2Vec2>& verts) {
        vector<vector<b2Vec2>> figsVec;
        queue<vector<b2Vec2>> queue;
        queue.push(verts);

        while (!queue.empty()) {
            vector<b2Vec2> vec = queue.front();
            int n = vec.size();
            bool isConvex = true;

            for (int i = 0; i < n; ++i) {
                int i1 = i;
                int i2 = (i<n - 1 ? i + 1 : i + 1 - n);
                int i3 = (i<n - 2 ? i + 2 : i + 2 - n);

                b2Vec2& p1 = vec[i1];
                b2Vec2& p2 = vec[i2];
                b2Vec2& p3 = vec[i3];

                float d = det(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
                if (d > 0) {
                    isConvex = false;
                    float minLen = std::numeric_limits<float>::max();
                    b2Vec2 hitV;
                    int h, k, j1, j2;

                    for (int j = 0; j < n; ++j) {
                        if (j != i1 && j != i2) {
                            j1 = j;
                            j2 = (j < n - 1 ? j + 1 : 0);

                            b2Vec2& v1 = vec[j1];
                            b2Vec2& v2 = vec[j2];

                            b2Vec2 v = hitRay(p1.x, p1.y, p2.x, p2.y, v1.x, v1.y, v2.x, v2.y);

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

                    vector<b2Vec2> vec1, vec2;

                    j1 = h;
                    j2 = k;
                    b2Vec2 v1 = vec[j1];
                    b2Vec2 v2 = vec[j2];

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

    b2Vec2 hitRay(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
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
            return b2Vec2(px, py);

        return
            b2Vec2(0.0f, 0.0f);
    }

    b2Vec2 hitSegment(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
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
            return b2Vec2(px, py);

        return
            b2Vec2(0.0f, 0.0f);
    }

    bool isOnSegment(float px, float py, float x1, float y1, float x2, float y2) {
        bool b1 = ((x1 + 0.1 >= px && px >= x2 - 0.1) || (x1 - 0.1 <= px && px <= x2 + 0.1));
        bool b2 = ((y1 + 0.1 >= py && py >= y2 - 0.1) || (y1 - 0.1 <= py && py <= y2 + 0.1));
        return (b1 && b2 && isOnLine(px, py, x1, y1, x2, y2));
    }

    bool pointsMatch(float x1, float y1, float x2, float y2) {
        float dx = (x2 >= x1 ? x2 - x1 : x1 - x2);
        float dy = (y2 >= y1 ? y2 - y1 : y1 - y2);
        return (dx < 0.1 && dy < 0.1);
    }

    bool isOnLine(float px, float py, float x1, float y1, float x2, float y2) {
        if (x2 - x1 > 0.1 || x1 - x2 > 0.1) {
            float a = (y2 - y1) / (x2 - x1);
            float possibleY = a * (px - x1) + y1;
            float diff = (possibleY > py ? possibleY - py : py - possibleY);
            return (diff < 0.1);
        }
        return (px - x1 < 0.1 || x1 - px < 0.1);
    }

    float det(float x1, float y1, float x2, float y2, float x3, float y3) {
        return x1*y2 + x2*y3 + x3*y1 - y1*x2 - y2*x3 - y3*x1;
    }

    void err() {
        throw new string("A problem has occurred. Use the Validate() method to see where the problem is.");
    }
}
#endif // __GEOMETRY__HPP__