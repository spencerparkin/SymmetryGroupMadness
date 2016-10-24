// Shape.h

#pragma once

#include "List.h"

class Triangle;

class Shape
{
public:

	Shape( void );
	virtual ~Shape( void );

	const TriangleList& GetTriangleList( void ) const { return triangleList; }

	void Render( int renderMode ) const;

private:

	c3ga::vectorE3GA pivotPoint;
	double rotationDelta;
	VectorList reflectionAxisList;

	TriangleList triangleList;
};

// Shape.h
