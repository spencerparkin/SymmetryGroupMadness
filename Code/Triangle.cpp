// Triangle.cpp

#include "Triangle.h"
#include "Line.h"

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

void Triangle::GetLines( LineList& lineList ) const
{
	for( int i = 0; i < 3; i++ )
	{
		const Vertex* vtx0 = &vertex[i];
		const Vertex* vtx1 = &vertex[ ( i + 1 ) % 3 ];

		c3ga::vectorE3GA normal = c3ga::unit( vtx1->point - vtx0->point );
		normal = normal * c3ga::I2;
		Line* line = new Line( vtx0->point, normal );
		lineList.push_back( line );
	}
}

bool Triangle::Covers( const Triangle& triangle ) const
{
	LineList lineList;
	GetLines( lineList );

	for( LineList::iterator iter = lineList.begin(); iter != lineList.end(); iter++ )
	{
		const Line* line = *iter;

		for( int i = 0; i < 3; i++ )
		{
			const Triangle::Vertex* vtx = &triangle.vertex[i];
			if( line->GetSide( vtx->point ) == Line::FRONT )
				return false;
		}
	}

	DeleteLineList( lineList );

	return true;
}

// Triangle.cpp