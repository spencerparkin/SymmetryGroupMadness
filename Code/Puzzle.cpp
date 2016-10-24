// Puzzle.cpp

#include "Puzzle.h"
#include "Shape.h"
#include "Triangle.h"
#include "LineSegment.h"
#include <wx/glcanvas.h>

Puzzle::Puzzle( void )
{
	modified = false;

	triangleList = new TriangleList();
}

/*virtual*/ Puzzle::~Puzzle( void )
{
	DeleteTriangleList( *triangleList );
	delete triangleList;

	DeleteShapeList( shapeList );
}

void Puzzle::ResetTriangles( void )
{
	DeleteTriangleList( *triangleList );

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

void Puzzle::GrabShape( const Shape& shape, TriangleList& grabbedTriangleList )
{
	modified = true;

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

void Puzzle::Render( int renderMode ) const
{
	if( renderMode == GL_RENDER )
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glBegin( GL_TRIANGLES );

		for( TriangleList::const_iterator iter = triangleList->cbegin(); iter != triangleList->cend(); iter++ )
		{
			const Triangle* triangle = *iter;
			triangle->Render( renderMode );
		}

		glEnd();
	}

	for( ShapeList::const_iterator iter = shapeList.cbegin(); iter != shapeList.cend(); iter++ )
	{
		const Shape* shape = *iter;
		shape->Render( renderMode );
	}
}

void Puzzle::ProcessHitRecords( unsigned int* hitBuffer, int hitBufferSize, int hitCount )
{
}

bool Puzzle::Save( void )
{
	return false;
}

bool Puzzle::Load( void )
{
	return false;
}

bool Puzzle::SetupLevel( int level )
{
	this->level = level;

	ResetTriangles();
	DeleteShapeList( shapeList );

	switch( level )
	{
		case 1:
		{
			// Level 1 is just the dihedral group D_4.
			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 ), 8.0, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			return true;
		}
		case 2:
		{
			break;
		}
	}

	return false;
}

// Puzzle.cpp