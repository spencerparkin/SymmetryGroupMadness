// Container.cpp

#include "Container.h"
#include "Triangle.h"
#include "LineSegment.h"
#include "Shape.h"

void DeleteLineSegmentList( LineSegmentList& lineSegmentList )
{
	while( lineSegmentList.size() > 0 )
	{
		LineSegmentList::iterator iter = lineSegmentList.begin();
		LineSegment* lineSegment = *iter;
		delete lineSegment;
		lineSegmentList.erase( iter );
	}
}

void DeleteTriangleList( TriangleList& triangleList )
{
	while( triangleList.size() > 0 )
	{
		TriangleList::iterator iter = triangleList.begin();
		Triangle* triangle = *iter;
		delete triangle;
		triangleList.erase( iter );
	}
}

void DeleteShapeList( ShapeList& shapeList )
{
	while( shapeList.size() > 0 )
	{
		ShapeList::iterator iter = shapeList.begin();
		Shape* shape = *iter;
		delete shape;
		shapeList.erase( iter );
	}
}

void DeleteTriangleMap( TriangleMap& triangleMap )
{
	while( triangleMap.size() > 0 )
	{
		TriangleMap::iterator iter = triangleMap.begin();
		Triangle* triangle = iter->second;
		delete triangle;
		triangleMap.erase( iter );
	}
}

bool ArrayContains( const VectorArray& pointArray, const c3ga::vectorE3GA& point, double eps /*= 1e-4*/ )
{
	int offset = FindArrayOffset( pointArray, point, eps );
	return( offset >= 0 ? true : false );
}

int FindArrayOffset( const VectorArray& pointArray, const c3ga::vectorE3GA& point, double eps /*= 1e-4*/ )
{
	for( int i = 0; i < pointArray.size(); i++ )
	{
		double len = c3ga::norm( pointArray[i] - point );
		if( len < eps )
			return i;
	}

	return -1;
}

// Container.cpp