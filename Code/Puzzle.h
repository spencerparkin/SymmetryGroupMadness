// Puzzle.h

#pragma once

#include "Container.h"

class Shape;
class LineSegment;
class Triangle;
class Rectangle_;
class Texture;

class Puzzle
{
public:

	Puzzle( void );
	virtual ~Puzzle( void );

	bool GrabShape( const Shape& shape, TriangleList& grabbedTriangleList );

	void Render( int renderMode, bool pickShapes = true ) const;

	void ProcessHitRecords( unsigned int* hitBuffer, int hitBufferSize, int hitCount, int* triangleId );
	Shape* GetShapeOwningTriangle( int triangleId );
	Shape* GetShapeContainingPoint( const c3ga::vectorE3GA& point );
	Triangle* GetTriangleById( int triangleId );

	bool Save( void );
	bool Load( void );

	bool SetupLevel( int level );

	bool modified;

	double CalculatePercentageSolved( void ) const;

	int GetLevel( void ) const { return level; }
	int GetTriangleCount( void ) const { return ( int )triangleList->size(); }
	const ShapeList& GetShapeList( void ) { return shapeList; }
	const Rectangle_* GetRectangle( void ) const;

	enum { MAX_LEVELS = 5, MAX_IMAGES = 14 };

	ScrambleList scrambleQueue;

private:

	void EnqueueScrambles( int scrambleCount, int scrambleSeed );
	void ResetTriangles( void );
	void RecalculateAllUVs( void );
	void TessellateTriangles( const LineSegment& lineSegment );
	void CollectTrianglesInTriangle( const Triangle& triangleCover, TriangleList& collectedTriangleList );

	TriangleList* triangleList;
	ShapeList shapeList;
	int level;
	mutable Rectangle_* rectangle;
	Texture* texture;
};

// Puzzle.h
