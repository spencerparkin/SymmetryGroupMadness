// List.h

#pragma once

#include <list>
#include "c3ga/c3ga.h"

class LineSegment;
class Triangle;

typedef std::list< LineSegment* > LineSegmentList;
typedef std::list< Triangle* > TriangleList;
typedef std::list< c3ga::vectorE3GA > VectorList;

void DeleteLineSegmentList( LineSegmentList& lineSegmentList );
void DeleteTriangleList( TriangleList& triangleList );

// List.h
