// Puzzle.h

#pragma once

#include "Container.h"

class Shape;
class LineSegment;
class Triangle;

class Puzzle
{
public:

	Puzzle( void );
	virtual ~Puzzle( void );

	void GrabShape( const Shape& shape, TriangleList& grabbedTriangleList );

	void Render( int renderMode ) const;

	void ProcessHitRecords( unsigned int* hitBuffer, int hitBufferSize, int hitCount, int* triangleId );
	Shape* GetShapeOwningTriangle( int triangleId );

	bool Save( void );
	bool Load( void );

	bool SetupLevel( int level );

	bool modified;

	// TODO: A quick way to know if we're solved might be to gather all vertices from all triangles
	//       that coincide at a single point in space and make sure they all share the same UVs.

	int GetLevel( void ) const { return level; }

	const ShapeList& GetShapeList( void ) { return shapeList; }

private:

	void ResetTriangles( void );
	void TessellateTriangles( const LineSegment& lineSegment );
	void CollectTrianglesInTriangle( const Triangle& triangleCover, TriangleList& collectedTriangleList );

	TriangleList* triangleList;
	ShapeList shapeList;
	int level;
};

// Puzzle.h
