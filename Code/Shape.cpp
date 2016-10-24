// Shape.cpp

#include "Shape.h"
#include "Triangle.h"
#include <wx/glcanvas.h>

Shape::Shape( void )
{
	pivotPoint.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
	rotationDelta = 0.0;
}

/*virtual*/ Shape::~Shape( void )
{
	DeleteTriangleList( triangleList );
}

void Shape::Render( int renderMode ) const
{
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glLineWidth( 1.5f );
	glBegin( GL_TRIANGLES );

	for( TriangleList::const_iterator iter = triangleList.cbegin(); iter != triangleList.cend(); iter++ )
	{
		const Triangle* triangle = *iter;
		triangle->Render( renderMode );
	}

	glEnd();
}

// Shape.cpp