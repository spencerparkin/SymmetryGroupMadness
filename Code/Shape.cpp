// Shape.cpp

#include "Shape.h"
#include "Triangle.h"
#include <wx/glcanvas.h>
#include <math.h>

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

void Shape::MakePolygon( const c3ga::vectorE3GA& center, double radius, int sides, double tiltAngle /*= 0.0*/ )
{
	DeleteTriangleList( triangleList );
	reflectionAxisList.clear();
	rotationDelta = 2.0 * M_PI / double( sides );
	pivotPoint = center;

	c3ga::vectorE3GA* vertices = new c3ga::vectorE3GA[ sides ];

	for( int i = 0; i < sides; i++ )
	{
		double angle = double(i) / double( sides ) * 2.0 * M_PI + tiltAngle;
		double x = center.get_e1() + radius * cos( angle );
		double y = center.get_e2() + radius * sin( angle );
		vertices[i].set( c3ga::vectorE3GA::coord_e1_e2_e3, x, y, 0.0 );
	}

	for( int i = 1; i < sides - 1; i++ )
	{
		Triangle* triangle = new Triangle();
		triangle->color.set( c3ga::vectorE3GA::coord_e1_e2_e3, 1.0, 1.0, 1.0 );
		triangle->vertex[0].point = vertices[0];
		triangle->vertex[1].point = vertices[i];
		triangle->vertex[2].point = vertices[ i + 1 ];
		triangleList.push_back( triangle );
	}

	delete[] vertices;
}

void MakeStar( const c3ga::vectorE3GA& center, double innerRadius, double outerRadius, int spikes, double tiltAngle /*= 0.0*/ )
{
}

// Shape.cpp