// Line.h

#pragma once

#include "c3ga/c3ga.h"
#include "List.h"

class Triangle;

class Line
{
public:

	Line( void );
	Line( const c3ga::vectorE3GA& center, const c3ga::vectorE3GA& normal );
	virtual ~Line( void );

	enum Side
	{
		NEITHER,
		FRONT,
		BACK,
	};

	Side GetSide( const c3ga::vectorE3GA& center, double eps = 1e-5 ) const;

	bool CutTriangle( const Triangle& triangle, TriangleList& cutTriangleList ) const;

private:

	c3ga::vectorE3GA center, normal;
};

// Line.h
