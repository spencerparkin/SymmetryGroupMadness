// LineSegment.h

#pragma once

#include "c3ga/c3ga.h"
#include "Container.h"

class Triangle;

class LineSegment
{
public:

	LineSegment( void );
	LineSegment( const c3ga::vectorE3GA& vertex0, const c3ga::vectorE3GA& vertex1 );
	virtual ~LineSegment( void );

	bool TessellateTriangle( const Triangle& triangle, TriangleList& tessellatedTriangleList ) const;
	bool CalculateIntersectionWith( const LineSegment& lineSegment, c3ga::vectorE3GA& intersectionPoint ) const;
	c3ga::vectorE3GA CalculateLineVector( void ) const;
	double CalculateLength( void ) const;
	const c3ga::vectorE3GA& GetVertex( int i ) const { return vertex[ i % 2 ]; }
	double CalculateOrthogonalDistanceToLine( const c3ga::vectorE3GA& point ) const;
	bool PointOnLine( const c3ga::vectorE3GA& point, double eps = 1e-7 ) const;
	bool ContainsPoint( const c3ga::vectorE3GA& point, double eps = 1e-7 ) const;

private:

	static void AddNonDegenerateTriangle( Triangle* newTriangle, TriangleList& triangleList );

	c3ga::vectorE3GA vertex[2];
};

// LineSegment.h
