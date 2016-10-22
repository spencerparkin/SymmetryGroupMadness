// Puzzle.h

#pragma once

#include "List.h"

class Shape;
class Line;
class Triangle;

class Puzzle
{
public:

	Puzzle( void );
	virtual ~Puzzle( void );

	void GrabShape( const Shape& shape, TriangleList& grabbedTriangleList );

private:

	void CutTriangles( const Line& line );
	void CollectTrianglesInTriangle( const Triangle& triangleCover, TriangleList& collectedTriangleList );

	TriangleList* triangleList;
};

// Puzzle.h
