// Puzzle.cpp

#include "Puzzle.h"
#include "Shape.h"
#include "Triangle.h"
#include "Line.h"

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

	LineList lineList;

	for( TriangleList::const_iterator iter = shapeTriangleList.begin(); iter != shapeTriangleList.end(); iter++ )
	{
		const Triangle* shapeTriangle = *iter;
		shapeTriangle->GetLines( lineList );
	}

	while( lineList.size() > 0 )
	{
		LineList::iterator iter = lineList.begin();
		Line* line = *iter;

		CutTriangles( *line );

		lineList.erase( iter );
		delete line;
	}

	for( TriangleList::const_iterator iter = shapeTriangleList.begin(); iter != shapeTriangleList.end(); iter++ )
	{
		const Triangle* shapeTriangle = *iter;
		CollectTrianglesInTriangle( *shapeTriangle, grabbedTriangleList );
	}
}

void Puzzle::CutTriangles( const Line& line )
{
	TriangleList* newTriangleList = new TriangleList();

	while( triangleList->size() > 0 )
	{
		TriangleList::iterator iter = triangleList->begin();
		Triangle* triangle = *iter;
		triangleList->erase( iter );

		if( line.CutTriangle( *triangle, *newTriangleList ) )
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