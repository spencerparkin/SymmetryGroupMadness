// List.cpp

#include "List.h"
#include "Triangle.h"
#include "Line.h"

void DeleteLineList( LineList& lineList )
{
	while( lineList.size() > 0 )
	{
		LineList::iterator iter = lineList.begin();
		Line* line = *iter;
		delete line;
		lineList.erase( iter );
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

// List.cpp