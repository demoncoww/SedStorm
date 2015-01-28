/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011-2014 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

// Modified by David Lazell

#ifndef _CONCAVEPOLYGON_HPP
#define _CONCAVEPOLYGON_HPP

#include <Thor/Math/TriangulationFigures.hpp> // for thor::Edge

#include <SFML/Graphics.hpp> // for sf::Shape and sf::ConvexShape

#include <vector>
#include <memory> // for unique_ptr and shared_ptr
#include "Geometry.h" // for splitting a concave polygon into multiple convex polygons

typedef std::vector< std::unique_ptr<sf::Shape> >	    ShapeContainer;
typedef std::vector< std::shared_ptr<sf::Shape> >	    SharedShapeContainer;
typedef std::vector< thor::Edge<const sf::Vector2f> >   EdgeContainer;

class ConcavePolygon : public virtual sf::Shape // we want to share the Transformable base class instance with Shape
{
public:
    explicit                    ConcavePolygon();
    void						swap(ConcavePolygon& other);

	SharedShapeContainer&		GetConvexShapesVector();

	bool IsConvexShape()		{ return m_isConvex; }

    // sf::ConvexShape has these as well:
    virtual unsigned int		getPointCount() const;
    virtual sf::Vector2f		getPoint(unsigned int index) const;
    void						setPointCount(unsigned int count);
    void						setPoint(unsigned int index, sf::Vector2f position);

    // members of Shape we don't have, do these work??
    // void setTexture(const Texture* texture, bool resetRect = false);
    // void setTextureRect(const IntRect& rect);
    // const Texture* getTexture() const;
    // const IntRect& getTextureRect() const;
    // FloatRect getLocalBounds() const;
    // FloatRect getGlobalBounds() const;
    
    // members of Shape that we do have
    // TODO: change these to use the built in shape member variables, instead of duplicating functionality
    void						setFillColor(const sf::Color& fillColor);
    void						setOutlineColor(const sf::Color& outlineColor);
    void						setOutlineThickness(float outlineThickness);
    sf::Color					getFillColor() const;
    sf::Color					getOutlineColor() const;
    float						getOutlineThickness() const;

private:
    virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Computes how the shape can be split up into convex shapes.
    void						decompose() const;

    // Forms the outline out of the given edges.
    void						formOutline() const;

private:
	std::vector<sf::Vector2f>	mPoints;
    sf::Color					mFillColor;
    sf::Color					mOutlineColor;
    float						mOutlineThickness;
	mutable bool				m_isConvex;

    // mutable = legal to assign the following from a const member function
    mutable EdgeContainer		mEdges;
	mutable SharedShapeContainer		m_ConvexShapes;
    mutable ShapeContainer		mEdgeShapes;
	mutable bool				m_NeedsConvexShapeUpdate;
    mutable bool				mNeedsEdgeUpdate;
};

inline void swap(ConcavePolygon& lhs, ConcavePolygon& rhs) {
	lhs.swap(rhs);
}

#endif // _CONCAVEPOLYGON_HPP
