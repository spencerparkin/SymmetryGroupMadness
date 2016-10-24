// Triangle.cpp

#include "Triangle.h"
#include "LineSegment.h"
#include "Application.h"
#include "Random.h"
#include <wx/glcanvas.h>

Triangle::Triangle( void )
{
	for( int i = 0; i < 3; i++ )
	{
		Vertex* vtx = &vertex[i];
		vtx->point.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
	}

	color = wxGetApp().GetRandom()->Vector( 0.1, 1.0 );
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
		const Vertex* vtx = &triangle.vertex[i];
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

void Triangle::Render( int renderMode ) const
{
	glColor3d( color.get_e1(), color.get_e2(), color.get_e3() );

	for( int i = 0; i < 3; i++ )
	{
		const Vertex* vtx = &vertex[i];
		glVertex3d( vtx->point.get_e1(), vtx->point.get_e2(), vtx->point.get_e3() );
	}
}

// Triangle.cpp