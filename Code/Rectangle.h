// Rectangle.h

#pragma once

#include "c3ga/c3ga.h"

class Rectangle_
{
public:

	Rectangle_( void );
	virtual ~Rectangle_( void );

	void ShrinkToMatchAspectRatio( double aspectRatio );
	void ExpandToMatchAspectRatio( double aspectRatio );

	void LinearMap( const Rectangle_& targetRectangle, c3ga::vectorE3GA& point ) const;

	double GetAspectRatio( void ) const;
	double GetWidth( void ) const;
	double GetHeight( void ) const;

	double xMin, xMax;
	double yMin, yMax;
};

// Rectangle.h
