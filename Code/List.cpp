// List.cpp

#include "List.h"
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

// List.cpp