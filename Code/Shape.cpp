// Shape.cpp

#include "Shape.h"

Shape::Shape( void )
{
	pivotPoint.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
	rotationDelta = 0.0;
}

/*virtual*/ Shape::~Shape( void )
{
	DeleteTriangleList( triangleList );
}

// Shape.cpp