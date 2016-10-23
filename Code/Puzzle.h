// Puzzle.h

#pragma once

#include "List.h"

class Shape;
class LineSegment;
class Triangle;

class Puzzle
{
public:

	Puzzle( void );
	virtual ~Puzzle( void );

	void GrabShape( const Shape& shape, TriangleList& grabbedTriangleList );

	void Render( int mode );

	// We want to know which shape and which triangle of the shape is selected.
	//void ProcessHitRecords

private:

	void CutTriangles( const LineSegment& lineSegment );
	void CollectTrianglesInTriangle( const Triangle& triangleCover, TriangleList& collectedTriangleList );

	TriangleList* triangleList;

	ShapeList shapeList;
};

// Puzzle.h
