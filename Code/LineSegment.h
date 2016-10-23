// LineSegment.h

#pragma once

#include "c3ga/c3ga.h"
#include "List.h"

class Triangle;

class LineSegment
{
public:

	LineSegment( void );
	LineSegment( const c3ga::vectorE3GA& vertex0, const c3ga::vectorE3GA& vertex1 );
	virtual ~LineSegment( void );

	bool CutTriangle( const Triangle& triangle, TriangleList& cutTriangleList ) const;

	const c3ga::vectorE3GA& GetVertex( int i ) const { return vertex[ i % 2 ]; }

private:

	c3ga::vectorE3GA vertex[2];
};

// LineSegment.h
