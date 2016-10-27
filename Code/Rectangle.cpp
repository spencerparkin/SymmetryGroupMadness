// Rectangle.cpp

#include "Rectangle.h"

Rectangle_::Rectangle_( void )
{
	xMin = 0.0;
	xMax = 0.0;
	yMin = 0.0;
	yMax = 0.0;
}

/*virtual*/ Rectangle_::~Rectangle_( void )
{
}

void Rectangle_::ShrinkToMatchAspectRatio( double aspectRatio )
{
	double thisAspectRatio = GetAspectRatio();

	if( thisAspectRatio > aspectRatio )
	{
		double xDelta = ( GetWidth() - GetHeight() * aspectRatio ) / 2.0;
		xMin += xDelta;
		xMax -= xDelta;
	}
	else if( thisAspectRatio < aspectRatio )
	{
		double yDelta = ( GetHeight() - GetWidth() / aspectRatio ) / 2.0;
		yMin += yDelta;
		yMax -= yDelta;
	}
}

void Rectangle_::ExpandToMatchAspectRatio( double aspectRatio )
{
	double thisAspectRatio = GetAspectRatio();

	if( thisAspectRatio > aspectRatio )
	{
		double yDelta = ( GetWidth() / aspectRatio - GetHeight() ) / 2.0;
		yMin -= yDelta;
		yMax += yDelta;
	}
	else if( thisAspectRatio < aspectRatio )
	{
		double xDelta = ( GetHeight() / aspectRatio - GetWidth() ) / 2.0;
		xMin -= xDelta;
		xMax += xDelta;
	}
}

void Rectangle_::LinearMap( const Rectangle_& targetRectangle, c3ga::vectorE3GA& point ) const
{
	double xLerp = ( point.get_e1() - xMin ) / GetWidth();
	double yLerp = ( point.get_e2() - yMin ) / GetHeight();

	point.set_e1( targetRectangle.xMin + xLerp * targetRectangle.GetWidth() );
	point.set_e2( targetRectangle.yMin + yLerp * targetRectangle.GetHeight() );
}

double Rectangle_::GetAspectRatio( void ) const
{
	return GetWidth() / GetHeight();
}

double Rectangle_::GetWidth( void ) const
{
	return xMax - xMin;
}

double Rectangle_::GetHeight( void ) const
{
	return yMax - yMin;
}

// Rectangle.cpp