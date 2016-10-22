// Triangle.h

#pragma once

#include "c3ga/c3ga.h"
#include "List.h"

class Triangle
{
public:

	Triangle( void );
	virtual ~Triangle( void );

	void GetLines( LineList& lineList ) const;

	bool Covers( const Triangle& triangle ) const;

	struct Vertex
	{
		c3ga::vectorE3GA point;
	};

	Vertex vertex[3];
};

// Triangle.h