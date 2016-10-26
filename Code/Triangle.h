// Triangle.h

#pragma once

#include "c3ga/c3ga.h"
#include "List.h"

class Triangle
{
public:

	Triangle( void );
	virtual ~Triangle( void );

	void MakeLineSegments( LineSegmentList& lineSegmentList ) const;

	bool Covers( const Triangle& triangle ) const;
	bool ContainsPoint( const c3ga::vectorE3GA& point ) const;
	bool IsDegenerate( double eps = 1e-7 ) const;

	void Render( int renderMode ) const;

	struct Vertex
	{
		c3ga::vectorE3GA point;
	};

	Vertex vertex[3];
	c3ga::vectorE3GA color;
	int id;

	static int nextId;
};

// Triangle.h