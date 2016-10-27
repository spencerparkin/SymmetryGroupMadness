// Container.h

#pragma once

#include <list>
#include <map>
#include <vector>
#include "c3ga/c3ga.h"

class LineSegment;
class Triangle;
class Shape;

typedef std::list< LineSegment* > LineSegmentList;
typedef std::list< Triangle* > TriangleList;
typedef std::list< Shape* > ShapeList;
typedef std::list< c3ga::vectorE3GA > VectorList;
typedef std::vector< c3ga::vectorE3GA > VectorArray;
typedef std::map< int, Triangle* > TriangleMap;

// Can I merge these into one template function?
void DeleteLineSegmentList( LineSegmentList& lineSegmentList );
void DeleteTriangleList( TriangleList& triangleList );
void DeleteShapeList( ShapeList& shapeList );
void DeleteTriangleMap( TriangleMap& triangleMap );

// Container.h