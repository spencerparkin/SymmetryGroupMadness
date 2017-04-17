// Shape.h

#pragma once

#include "Container.h"
#include "Permutation.h"

class Triangle;

class Shape
{
public:

	Shape( void );
	virtual ~Shape( void );

	const TriangleList& GetTriangleList( void ) const { return triangleList; }

	void Render( int renderMode ) const;

	bool OwnsTriangle( int triangleId ) const;
	bool ContainsPoint( const c3ga::vectorE3GA& point ) const;

	void MakePolygon( const c3ga::vectorE3GA& center, double radius, int sides, double tiltAngle = 0.0 );
	void MakeStar( const c3ga::vectorE3GA& center, double innerRadius, double outerRadius, int spikes, double tiltAngle = 0.0 );
	void MakeRectangle( const c3ga::vectorE3GA& center, double width, double height, double tiltAngle = 0.0 );

	const VectorArray& GetReflectionAxisArray( void ) const { return reflectionAxisArray; }
	double GetRotationDelta( void ) const { return rotationDelta; }
	const c3ga::vectorE3GA& GetPivotPoint( void ) const { return pivotPoint; }

	PermutationArray reflectionPermutationArray;
	Permutation ccwRotationPermutation;

private:

	c3ga::vectorE3GA pivotPoint;	// The shape rotates about this point.
	double rotationDelta;	// A rotation of the shape must be a multiple of this delta.
	VectorArray reflectionAxisArray;	// The shape can be reflected about these axes.
	TriangleList triangleList;	// The shape consists of these triangles.
};

// Shape.h
