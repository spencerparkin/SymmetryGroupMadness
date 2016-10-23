// List.h

#pragma once

#include <list>
#include "c3ga/c3ga.h"

class LineSegment;
class Triangle;
class Shape;

typedef std::list< LineSegment* > LineSegmentList;
typedef std::list< Triangle* > TriangleList;
typedef std::list< Shape* > ShapeList;
typedef std::list< c3ga::vectorE3GA > VectorList;

// Can I merge these into one template function?
void DeleteLineSegmentList( LineSegmentList& lineSegmentList );
void DeleteTriangleList( TriangleList& triangleList );
void DeleteShapeList( ShapeList& shapeList );

// List.h
