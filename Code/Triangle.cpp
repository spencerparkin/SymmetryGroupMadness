// Triangle.cpp

#include "Triangle.h"
#include "LineSegment.h"
#include "Application.h"
#include "Random.h"
#include <wx/glcanvas.h>

int Triangle::nextId = 1;

Triangle::Triangle( void )
{
	id = nextId++;

	for( int i = 0; i < 3; i++ )
	{
		Vertex* vtx = &vertex[i];
		vtx->point.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
	}

	color = wxGetApp().GetRandom()->Vector( 0.5, 1.0 );
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

bool Triangle::IsDegenerate( double eps /*= 1e-7*/ ) const
{
	c3ga::bivectorE3GA bivector = ( vertex[1].point - vertex[0].point ) ^ ( vertex[2].point - vertex[0].point );
	if( fabs( bivector.get_e1_e2() / 2.0 ) < eps )
		return true;
	return false;
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

// Note that here we assume that the given point as well as this triangle in the XY-plane.
bool Triangle::ContainsPoint( const c3ga::vectorE3GA& point ) const
{
	for( int i = 0; i < 3; i++ )
	{
		int j = ( i + 1 ) % 3;
		c3ga::bivectorE3GA bivector = c3ga::op( vertex[j].point - vertex[i].point, point - vertex[i].point );
		if( bivector.get_e1_e2() < 0.0 )
			return false;
	}

	return true;
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