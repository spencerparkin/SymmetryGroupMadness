// Random.cpp

#include "Random.h"
#include <time.h>
#include <stdlib.h>

Random::Random( void )
{
	//unsigned int seed = ( unsigned )time( nullptr );
	unsigned int seed = 0;		// For debugging/reproducability purposes.
	srand( seed );
}

/*virtual*/ Random::~Random( void )
{
}

double Random::Interpolator( void )
{
	double r = rand();
	double r_max = ( double )RAND_MAX;
	double t = r / r_max;
	return t;
}

double Random::Number( double min, double max )
{
	return min + ( max - min ) * Interpolator();
}

c3ga::vectorE3GA Random::Vector( double min, double max )
{
	c3ga::vectorE3GA vector;
	vector.set_e1( Number( min, max ) );
	vector.set_e2( Number( min, max ) );
	vector.set_e3( Number( min, max ) );
	return vector;
}

// Random.cpp