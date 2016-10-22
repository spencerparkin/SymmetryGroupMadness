// Line.cpp

#include "Line.h"

Line::Line( void )
{
	center.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
	normal.set( c3ga::vectorE3GA::coord_e1_e2_e3, 1.0, 0.0, 0.0 );
}

Line::Line( const c3ga::vectorE3GA& center, const c3ga::vectorE3GA& normal )
{
	this->center = center;
	this->normal = normal;
}

/*virtual*/ Line::~Line( void )
{
}

Line::Side Line::GetSide( const c3ga::vectorE3GA& point, double eps /*= 1e-5*/ ) const
{
	double dot = c3ga::lc( point - center, normal );
	if( dot >= eps )
		return FRONT;
	if( dot <= eps )
		return BACK;
	return NEITHER;
}

bool Line::CutTriangle( const Triangle& triangle, TriangleList& cutTriangleList ) const
{
	//...

	return false;
}

// Line.cpp