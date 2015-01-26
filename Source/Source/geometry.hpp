#ifndef _GEOMETRY
#define _GEOMETRY

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

// Modfied by David Lazell

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <string>
using namespace std;

namespace Geometry
{
	inline float det(float x1, float y1, float x2, float y2, float x3, float y3);
	bool isOnLine(float px, float py, float x1, float y1, float x2, float y2);
	bool pointsMatch(float x1, float y1, float x2, float y2);
	bool isOnSegment(float px, float py, float x1, float y1, float x2, float y2);
	b2Vec2 hitRay(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	b2Vec2 hitSegment(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    vector<vector<b2Vec2>> calcShapes(vector<b2Vec2>& verts);
    void err(void);

	/**
	* Separates a non-convex polygon into convex polygons and adds them as fixtures to the <code>body</code> parameter.<br/>
	* There are some rules you should follow (otherwise you might get unexpected results) :
	* <ul>
	* <li>This class is specifically for non-convex polygons. If you want to create a convex polygon, you don't need to use this class - Box2D's <code>b2PolygonShape</code> class allows you to create convex shapes with the <code>setAsArray()</code>/<code>setAsVector()</code> method.</li>
	* <li>The vertices must be in clockwise order.</li>
	* <li>No three neighbouring points should lie on the same line segment.</li>
	* <li>There must be no overlapping segments and no "holes".</li>
	* </ul> <p/>
	* @param body The b2Body, in which the new fixtures will be stored.
	* @param fixtureDef A b2FixtureDef, containing all the properties (friction, density, etc.) which the new fixtures will inherit.
	* @param verticesVec The vertices of the non-convex polygon, in clockwise order.
	* @param scale <code>[optional]</code> The scale which you use to draw shapes in Box2D. The bigger the scale, the better the precision. The default value is 30.
	* @see b2PolygonShape
	* @see b2PolygonShape.SetAsArray()
	* @see b2PolygonShape.SetAsVector()
	* @see b2Fixture
	* */
	void Separate(b2World& world, b2BodyDef& bodyDef, b2FixtureDef& fixtureDef, vector<b2Vec2>& vertices, unsigned int scale = 30) {
		int n = vertices.size();
		vector<b2Vec2> vec;
		b2Vec2 *b2Points = (b2Vec2*)alloca(sizeof(b2Vec2) * vertices.size());

		for (int i = 0; i<n; i++)
			vec.push_back(b2Vec2(vertices[i].x * scale, vertices[i].y * scale));

		vector<vector<b2Vec2>> figsVec = calcShapes(vec);

		b2Body* body = world.CreateBody(&bodyDef);

		for (auto vec : figsVec) {
			vector<b2Vec2> verticesVec;
			for (unsigned int i = 0; i < vec.size(); i++)
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
	}

	/**
	* Checks whether the vertices in <code>verticesVec</code> can be properly distributed into the new fixtures (more specifically, it makes sure there are no overlapping segments and the vertices are in clockwise order).
	* It is recommended that you use this method for debugging only, because it may cost more CPU usage.
	* <p/>
	* @param verticesVec The vertices to be validated.
	* @return An integer which can have the following values:
	* <ul>
	* <li>0 if the vertices can be properly processed.</li>
	* <li>1 If there are overlapping lines.</li>
	* <li>2 if the points are <b>not</b> in clockwise order.</li>
	* <li>3 if there are overlapping lines <b>and</b> the points are <b>not</b> in clockwise order.</li>
	* </ul>
	* */

	int Validate(vector<b2Vec2>& verts) {
		int n = verts.size();
		int ret = 0;
		bool fl2 = false;

		for (int i = 0; i<n; i++) {
			int i2 = (i<n - 1 ? i + 1 : 0);
			int i3 = (i>0 ? i - 1 : n - 1);

			bool fl = false;
			for (int j = 0; j < n; j++) {
				if (j != i && j != i2) {
					if (!fl) {
						float d = det(verts[i].x, verts[i].y, verts[i2].x, verts[i2].y, verts[j].x, verts[j].y);
						if (d > 0)
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

	vector<vector<b2Vec2>> calcShapes(vector<b2Vec2>& verts) {
		vector<vector<b2Vec2>> figsVec;
		queue<vector<b2Vec2>> queue;
		queue.push(verts);

		while (!queue.empty())
		{
			vector<b2Vec2> vec = queue.front();
			int n = vec.size();
			bool isConvex = true;

			for (int i = 0; i<n; i++)
			{
				int i1 = i;
				int i2 = (i<n - 1 ? i + 1 : i + 1 - n);
				int i3 = (i<n - 2 ? i + 2 : i + 2 - n);

				b2Vec2 p1 = vec[i1];
				b2Vec2 p2 = vec[i2];
				b2Vec2 p3 = vec[i3];

				float d = det(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
				if (d<0) {
					isConvex = false;
					float minLen = std::numeric_limits<float>::max();
					b2Vec2 hitV;
					int h, k, j1, j2;

					for (int j = 0; j<n; j++) {
						if (j != i1&&j != i2) {
							j1 = j;
							j2 = (j<n - 1 ? j + 1 : 0);

							b2Vec2 v1 = vec[j1];
							b2Vec2 v2 = vec[j2];

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
					while (true)
					{
						if (k != j2)
							vec1.push_back(vec[k]);
						else
						{
							if (h<0 || h >= n) err();
							if (!isOnSegment(v2.x, v2.y, vec[h].x, vec[h].y, p1.x, p1.y))
								vec1.push_back(vec[k]);
							break;
						}

						h = k;
						if (k - 1<0) k = n - 1;
						else k--;
					}

					std::reverse(vec1.begin(), vec1.end());

					h = -1;
					k = i2;
					while (true) {
						if (k != j1)
							vec2.push_back(vec[k]);
						else {
							if (h<0 || h >= n)
								err();
							if (k == j1 && !isOnSegment(v1.x, v1.y, vec[h].x, vec[h].y, p2.x, p2.y))
								vec2.push_back(vec[k]);
							break;
						}

						h = k;
						if (k + 1>n - 1) k = 0;
						else k++;
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
		if (x2 - x1 > 0.1 || x1 - x2 > 0.1)	{
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
#endif // _GEOMETRY