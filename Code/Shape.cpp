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

void Shape::MakePolygon( const c3ga::vectorE3GA& center, double radius, int sides, double tiltAngle /*= 0.0*/, c3ga::vectorE3GA* edgePoint /*= nullptr*/ )
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

	if( edgePoint )
	{
		double height = radius * sqrt( 0.5 + 0.25 * cos( rotationDelta ) );
		*edgePoint = center;
		edgePoint->m_e1 += height * cos( rotationDelta / 2.0 + tiltAngle ) * 0.95;
		edgePoint->m_e2 += height * sin( rotationDelta / 2.0 + tiltAngle ) * 0.95;
	}
}

void Shape::MakeStar( const c3ga::vectorE3GA& center, double innerRadius, double outerRadius, int spikes, double tiltAngle /*= 0.0*/ )
{
}

void Shape::MakeRectangle( const c3ga::vectorE3GA& center, double width, double height, double tiltAngle /*= 0.0*/ )
{
	wxASSERT( width != height );

	DeleteTriangleList( triangleList );
	reflectionAxisArray.clear();
	rotationDelta = M_PI;
	pivotPoint = center;

	c3ga::vectorE3GA reflectionAxis;

	reflectionAxis.set( c3ga::vectorE3GA::coord_e1_e2_e3, cos( tiltAngle ), sin( tiltAngle ), 0.0 );
	reflectionAxisArray.push_back( reflectionAxis );

	reflectionAxis.set( c3ga::vectorE3GA::coord_e1_e2_e3, cos( tiltAngle + M_PI / 2.0 ), sin( tiltAngle + M_PI / 2.0 ), 0.0 );
	reflectionAxisArray.push_back( reflectionAxis );

	c3ga::vectorE3GA* vertices = new c3ga::vectorE3GA[4];

	vertices[0].set( c3ga::vectorE3GA::coord_e1_e2_e3, -width / 2.0, -height / 2.0, 0.0 );
	vertices[1].set( c3ga::vectorE3GA::coord_e1_e2_e3, width / 2.0, -height / 2.0, 0.0 );
	vertices[2].set( c3ga::vectorE3GA::coord_e1_e2_e3, width / 2.0, height / 2.0, 0.0 );
	vertices[3].set( c3ga::vectorE3GA::coord_e1_e2_e3, -width / 2.0, height / 2.0, 0.0 );

	c3ga::vectorE3GA axis( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 1.0 );
	c3ga::rotorE3GA rotor;
	rotor = c3ga::exp( axis * c3ga::I3 * ( -tiltAngle / 2.0 ) );

	for( int i = 0; i < 4; i++ )
		vertices[i] = c3ga::applyUnitVersor( rotor, vertices[i] ) + center;

	Triangle* triangle = new Triangle();
	triangle->color.set( c3ga::vectorE3GA::coord_e1_e2_e3, 1.0, 1.0, 1.0 );
	triangle->vertex[0].point = vertices[0];
	triangle->vertex[1].point = vertices[1];
	triangle->vertex[2].point = vertices[2];
	triangleList.push_back( triangle );

	triangle = new Triangle();
	triangle->color.set( c3ga::vectorE3GA::coord_e1_e2_e3, 1.0, 1.0, 1.0 );
	triangle->vertex[0].point = vertices[0];
	triangle->vertex[1].point = vertices[2];
	triangle->vertex[2].point = vertices[3];
	triangleList.push_back( triangle );

	delete[] vertices;
}

// This routine or some of its logic probably should have been re-used by the Grab::ApplyRotation function, but oh well.
bool Shape::TransformPoint( const c3ga::vectorE3GA& inPoint, c3ga::vectorE3GA& outPoint, int transform ) const
{
	if( !ContainsPoint( inPoint ) )
		return false;

	c3ga::vectorE3GA rotationAxis;
	double rotationAngle;

	if( transform < 0 )
	{
		rotationAxis.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 1.0 );
		rotationAngle = rotationDelta;
	}
	else
	{
		rotationAxis = reflectionAxisArray[ transform ];
		rotationAngle = M_PI;
	}

	c3ga::rotorE3GA rotor = c3ga::exp( rotationAxis * c3ga::I3 * ( -rotationAngle / 2.0 ) );

	// There is a way to compute a versor (motor * rotor) in CGA to do this, but whatever.
	outPoint = pivotPoint + c3ga::applyUnitVersor( rotor, inPoint - pivotPoint );

	return true;
}

// Shape.cpp