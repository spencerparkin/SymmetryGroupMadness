// Triangle.cpp

#include "Triangle.h"
#include "LineSegment.h"

Triangle::Triangle( void )
{
	for( int i = 0; i < 3; i++ )
	{
		Vertex* vtx = &vertex[i];
		vtx->point.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
	}
}

/*virtual*/ Triangle::~Triangle( void )
{
}

void Triangle::MakeLineSegments( LineSegmentList& lineSegmentList ) const
{
	for( int i = 0; i < 3; i++ )
	{
		const Vertex* vtx0 = &vertex[i];
		const Vertex* vtx1 = &vertex[ ( i + 1 ) % 3 ];

		for( LineSegmentList::iterator iter = lineSegmentList.begin(); iter != lineSegmentList.end(); iter++ )
		{
			LineSegment* lineSegment = *iter;
			if( c3ga::norm( lineSegment->GetVertex(0) - vtx0->point ) == 0.0 &&
				c3ga::norm( lineSegment->GetVertex(1) - vtx1->point ) == 0.0 )
			{
				return;
			}
		}

		LineSegment* lineSegment = new LineSegment( vtx0->point, vtx1->point );
		lineSegmentList.push_back( lineSegment );
	}
}

bool Triangle::Covers( const Triangle& triangle ) const
{
	for( int i = 0; i < 3; i++ )
	{
		const Triangle::Vertex* vtx = &triangle.vertex[i];
		if( !ContainsPoint( vtx->point ) )
			return false;
	}

	return true;
}

bool Triangle::ContainsPoint( const c3ga::vectorE3GA& point ) const
{
	// ...check sign of 3 determinants.  if any one of them is negative, the answer is no.

	return false;
}

// Triangle.cpp