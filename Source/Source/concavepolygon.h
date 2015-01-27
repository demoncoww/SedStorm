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

#include <Thor/Math/TriangulationFigures.hpp>
#include <Thor/Config.hpp>

#include <Aurora/SmartPtr/CopiedPtr.hpp>
#include <Aurora/Tools/Swap.hpp>

#include <SFML/Graphics.hpp>

#include <vector>

class ConcavePolygon : public virtual sf::Shape
{
public:
    explicit ConcavePolygon();
    void						swap(ConcavePolygon& other);

    // sf::ConvexShape has these:
    void						setPointCount(unsigned int count);
    virtual unsigned int		getPointCount() const;
    void						setPoint(unsigned int index, sf::Vector2f position);
    virtual sf::Vector2f		getPoint(unsigned int index) const;

    // members of Shape we dont have:
    // void setTexture(const Texture* texture, bool resetRect = false);
    // void setTextureRect(const IntRect& rect);
    // const Texture* getTexture() const;
    // const IntRect& getTextureRect() const;
    // FloatRect getLocalBounds() const;
    // FloatRect getGlobalBounds() const;
    
    // members of Shape that we do have 
    void						setFillColor(const sf::Color& fillColor);
    void						setOutlineColor(const sf::Color& outlineColor);
    void						setOutlineThickness(float outlineThickness);
    sf::Color					getFillColor() const;
    sf::Color					getOutlineColor() const;
    float						getOutlineThickness() const;

private:
    typedef std::vector< aurora::CopiedPtr<sf::Shape> >	    ShapeContainer;
    typedef std::vector< sf::Vector2f >					    PointContainer;
    typedef std::vector< thor::Edge<const sf::Vector2f> >   EdgeContainer;

    struct TriangleGenerator;


private:
    virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Computes how the shape can be split up into convex triangles.
    void						decompose() const;

    // Forms the outline out of the given edges.
    void						formOutline() const;

private:
    PointContainer				mPoints;
    sf::Color					mFillColor;
    sf::Color					mOutlineColor;
    float						mOutlineThickness;

    mutable EdgeContainer		mEdges;
    mutable ShapeContainer		mTriangleShapes;
    mutable ShapeContainer		mEdgeShapes;
    mutable bool				mNeedsTriangleUpdate;
    mutable bool				mNeedsEdgeUpdate;
};

AURORA_GLOBAL_SWAP(ConcavePolygon)

#endif // _CONCAVEPOLYGON_HPP
