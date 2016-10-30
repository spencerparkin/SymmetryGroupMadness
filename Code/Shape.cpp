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
	if( renderMode == GL_RENDER )
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glLineWidth( 1.5f );
	}
	else if( renderMode == GL_SELECT )
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	for( TriangleList::const_iterator iter = triangleList.cbegin(); iter != triangleList.cend(); iter++ )
	{
		const Triangle* triangle = *iter;
		if( renderMode == GL_SELECT )
			glLoadName( triangle->id );
		glBegin( GL_TRIANGLES );
		triangle->Render( renderMode );
		glEnd();
	}
}

bool Shape::OwnsTriangle( int triangleId ) const
{
	for( TriangleList::const_iterator iter = triangleList.cbegin(); iter != triangleList.cend(); iter++ )
	{
		const Triangle* triangle = *iter;
		if( triangle->id == triangleId )
			return true;
	}

	return false;
}

bool Shape::ContainsPoint( const c3ga::vectorE3GA& point ) const
{
	for( TriangleList::const_iterator iter = triangleList.cbegin(); iter != triangleList.cend(); iter++ )
	{
		const Triangle* triangle = *iter;
		if( triangle->ContainsPoint( point ) )
			return true;
	}

	return false;
}

void Shape::MakePolygon( const c3ga::vectorE3GA& center, double radius, int sides, double tiltAngle /*= 0.0*/ )
{
	DeleteTriangleList( triangleList );
	reflectionAxisArray.clear();
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

	if( sides % 2 == 1 )
	{
		for( int i = 0; i < sides; i++ )
		{
			c3ga::vectorE3GA axis = c3ga::unit( vertices[i] - pivotPoint );
			reflectionAxisArray.push_back( axis );
		}
	}
	else
	{
		for( int i = 0; i < sides / 2; i++ )
		{
			c3ga::vectorE3GA axis = c3ga::unit( vertices[i] - pivotPoint );
			reflectionAxisArray.push_back( axis );

			axis = c3ga::unit( vertices[i] + vertices[ i + 1 ] - pivotPoint * 2.0 );
			reflectionAxisArray.push_back( axis );
		}
	}

	delete[] vertices;
}

void MakeStar( const c3ga::vectorE3GA& center, double innerRadius, double outerRadius, int spikes, double tiltAngle /*= 0.0*/ )
{
}

// Shape.cpp