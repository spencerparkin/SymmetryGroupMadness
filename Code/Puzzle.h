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

	void ProcessHitRecords( unsigned int* hitBuffer, int hitBufferSize, int hitCount );

	bool Save( void );
	bool Load( void );

	bool SetupLevel( int level );

	bool modified;

private:

	void CutTriangles( const LineSegment& lineSegment );
	void CollectTrianglesInTriangle( const Triangle& triangleCover, TriangleList& collectedTriangleList );

	TriangleList* triangleList;
	ShapeList shapeList;
	int level;
};

// Puzzle.h
