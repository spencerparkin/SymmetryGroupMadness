// Rectangle.h

#pragma once

#include "c3ga/c3ga.h"

class Texture;

class Rectangle_
{
public:

	Rectangle_( void );
	virtual ~Rectangle_( void );

	void ShrinkToMatchAspectRatio( double aspectRatio );
	void ExpandToMatchAspectRatio( double aspectRatio );

	bool ContainsPoint( const c3ga::vectorE3GA& point ) const;

	void LinearMap( const Rectangle_& targetRectangle, const c3ga::vectorE3GA& pointIn, c3ga::vectorE3GA& pointOut ) const;

	void CalculateUVs( const c3ga::vectorE3GA& point, double& u, double& v, const Texture* texture ) const;

	double GetArea( void ) const;
	double GetAspectRatio( void ) const;
	double GetWidth( void ) const;
	double GetHeight( void ) const;

	double xMin, xMax;
	double yMin, yMax;
};

// Rectangle.h
