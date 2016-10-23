// LineSegment.cpp

#include "LineSegment.h"

LineSegment::LineSegment( void )
{
	vertex[0].set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
	vertex[1].set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
}

LineSegment::LineSegment( const c3ga::vectorE3GA& vertex0, const c3ga::vectorE3GA& vertex1 )
{
	vertex[0] = vertex0;
	vertex[1] = vertex1;
}

/*virtual*/ LineSegment::~LineSegment( void )
{
}

bool LineSegment::CutTriangle( const Triangle& triangle, TriangleList& cutTriangleList ) const
{
	//...

	return false;
}

// LineSegment.cpp