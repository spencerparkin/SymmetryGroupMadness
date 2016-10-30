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

void Rectangle_::LinearMap( const Rectangle_& targetRectangle, const c3ga::vectorE3GA& pointIn, c3ga::vectorE3GA& pointOut ) const
{
	double xLerp = ( pointIn.get_e1() - xMin ) / GetWidth();
	double yLerp = ( pointIn.get_e2() - yMin ) / GetHeight();

	pointOut.set_e1( targetRectangle.xMin + xLerp * targetRectangle.GetWidth() );
	pointOut.set_e2( targetRectangle.yMin + yLerp * targetRectangle.GetHeight() );
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

void Rectangle_::CalculateUVs( const c3ga::vectorE3GA& point, double& u, double& v ) const
{
	Rectangle_ textureSpace;

	textureSpace.xMin = 0.0;
	textureSpace.xMax = 1.0;
	textureSpace.yMin = 0.0;
	textureSpace.yMax = 1.0;

	c3ga::vectorE3GA textureSpacePoint;
	LinearMap( textureSpace, point, textureSpacePoint );

	u = textureSpacePoint.get_e1();
	v = 1.0 - textureSpacePoint.get_e2();
}

// Rectangle.cpp