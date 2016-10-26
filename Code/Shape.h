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

	bool OwnsTriangle( int triangleId ) const;

	void MakePolygon( const c3ga::vectorE3GA& center, double radius, int sides, double tiltAngle = 0.0 );
	void MakeStar( const c3ga::vectorE3GA& center, double innerRadius, double outerRadius, int spikes, double tiltAngle = 0.0 );

private:

	c3ga::vectorE3GA pivotPoint;	// The shape rotates about this point.
	double rotationDelta;	// A rotation of the shape must be a multiple of this delta.
	VectorList reflectionAxisList;	// The shape can be reflected about these axes.
	TriangleList triangleList;	// The shape consists of these triangles.
};

// Shape.h
