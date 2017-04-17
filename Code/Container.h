// Container.h

#pragma once

#include <list>
#include <map>
#include <vector>
#include "c3ga/c3ga.h"
#include "Permutation.h"

class LineSegment;
class Triangle;
class Shape;

struct Vertex
{
	c3ga::vectorE3GA point;
	double u, v;
};

struct Scramble
{
	c3ga::vectorE3GA rotationAxis;
	double rotationAngle;
	double animationAngle;
	Shape* shape;
	Permutation actionPerm;
};

typedef std::list< LineSegment* > LineSegmentList;
typedef std::list< Triangle* > TriangleList;
typedef std::list< Shape* > ShapeList;
typedef std::list< c3ga::vectorE3GA > VectorList;
typedef std::vector< c3ga::vectorE3GA > VectorArray;
typedef std::map< int, Triangle* > TriangleMap;
typedef std::list< Vertex > VertexList;
typedef std::vector< Vertex > VertexArray;
typedef std::list< Scramble > ScrambleList;

// Can I merge these into one template function?
void DeleteLineSegmentList( LineSegmentList& lineSegmentList );
void DeleteTriangleList( TriangleList& triangleList );
void DeleteShapeList( ShapeList& shapeList );
void DeleteTriangleMap( TriangleMap& triangleMap );

// Container.h
