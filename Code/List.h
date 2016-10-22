// List.h

#pragma once

#include <list>
#include "c3ga/c3ga.h"

class Line;
class Triangle;

typedef std::list< Line* > LineList;
typedef std::list< Triangle* > TriangleList;
typedef std::list< c3ga::vectorE3GA > VectorList;

void DeleteLineList( LineList& lineList );
void DeleteTriangleList( TriangleList& triangleList );

// List.h
