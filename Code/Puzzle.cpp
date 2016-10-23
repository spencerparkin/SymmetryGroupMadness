// Puzzle.cpp

#include "Puzzle.h"
#include "Shape.h"
#include "Triangle.h"
#include "LineSegment.h"

Puzzle::Puzzle( void )
{
	triangleList = new TriangleList();

	Triangle* triangle = new Triangle();
	triangle->vertex[0].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, -10.0, -10.0, 0.0 );
	triangle->vertex[1].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, 10.0, -10.0, 0.0 );
	triangle->vertex[2].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, 10.0, 10.0, 0.0 );
	triangleList->push_back( triangle );

	triangle = new Triangle();
	triangle->vertex[0].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, -10.0, -10.0, 0.0 );
	triangle->vertex[1].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, 10.0, 10.0, 0.0 );
	triangle->vertex[2].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, -10.0, 10.0, 0.0 );
	triangleList->push_back( triangle );
}

/*virtual*/ Puzzle::~Puzzle( void )
{
	DeleteTriangleList( *triangleList );
	delete triangleList;
}

void Puzzle::GrabShape( const Shape& shape, TriangleList& grabbedTriangleList )
{
	const TriangleList& shapeTriangleList = shape.GetTriangleList();

	LineSegmentList lineSegmentList;

	for( TriangleList::const_iterator iter = shapeTriangleList.begin(); iter != shapeTriangleList.end(); iter++ )
	{
		const Triangle* shapeTriangle = *iter;
		shapeTriangle->MakeLineSegments( lineSegmentList );
	}

	while( lineSegmentList.size() > 0 )
	{
		LineSegmentList::iterator iter = lineSegmentList.begin();
		LineSegment* lineSegment = *iter;

		CutTriangles( *lineSegment );

		lineSegmentList.erase( iter );
		delete lineSegment;
	}

	// At this point we might consider a compression pass.  It's possible that two
	// adjacent triangles can be merged into a single triangle.  This would be O(n^2)
	// unless we kept track of adjacencies using a graph, but that makes our data-structure
	// quite a bit more complicated.  If at all, I would only add this optimization later
	// after everything was working, and only if I thought we could benefit from it.

	for( TriangleList::const_iterator iter = shapeTriangleList.begin(); iter != shapeTriangleList.end(); iter++ )
	{
		const Triangle* shapeTriangle = *iter;
		CollectTrianglesInTriangle( *shapeTriangle, grabbedTriangleList );
	}
}

void Puzzle::CutTriangles( const LineSegment& lineSegment )
{
	TriangleList* newTriangleList = new TriangleList();

	while( triangleList->size() > 0 )
	{
		TriangleList::iterator iter = triangleList->begin();
		Triangle* triangle = *iter;
		triangleList->erase( iter );

		if( lineSegment.CutTriangle( *triangle, *newTriangleList ) )
			delete triangle;
		else
			newTriangleList->push_back( triangle );
	}

	delete triangleList;
	triangleList = newTriangleList;
}

void Puzzle::CollectTrianglesInTriangle( const Triangle& triangleCover, TriangleList& collectedTriangleList )
{
	for( TriangleList::iterator iter = triangleList->begin(); iter != triangleList->end(); iter++ )
	{
		Triangle* triangle = *iter;
		if( triangleCover.Covers( *triangle ) )
			collectedTriangleList.push_back( triangle );
	}
}

// Puzzle.cpp