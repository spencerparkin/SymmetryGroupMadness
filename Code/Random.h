// Random.h

#pragma once

#include "c3ga/c3ga.h"

class Random
{
public:

	Random( void );
	virtual ~Random( void );

	double Interpolator( void );
	double Number( double min, double max );
	c3ga::vectorE3GA Vector( double min, double max );
};

// Random.h