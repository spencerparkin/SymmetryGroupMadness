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

private:

	void CutTriangles( const LineSegment& lineSegment );
	void CollectTrianglesInTriangle( const Triangle& triangleCover, TriangleList& collectedTriangleList );

	TriangleList* triangleList;
};

// Puzzle.h
