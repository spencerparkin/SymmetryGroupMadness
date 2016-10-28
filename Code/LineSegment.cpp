// LineSegment.cpp

#include "LineSegment.h"
#include "Triangle.h"
#include <wx/debug.h>

LineSegment::LineSegment( void )
{
	vertex[0].set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
	vertex[1].set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
}

LineSegment::LineSegment( const c3ga::vectorE3GA& vertex0, const c3ga::vectorE3GA& vertex1 )
{
	vertex[0] = vertex0;
	vertex[1] = vertex1;
}

/*virtual*/ LineSegment::~LineSegment( void )
{
}

bool LineSegment::TessellateTriangle( const Triangle& triangle, TriangleList& tessellatedTriangleList ) const
{
	return false;
}

double LineSegment::CalculateOrthogonalDistanceToLine( const c3ga::vectorE3GA& point ) const
{
	c3ga::vectorE3GA normal = c3ga::unit( vertex[1] - vertex[0] );
	c3ga::vectorE3GA vector = point - vertex[0];
	double distance = c3ga::norm( c3ga::lc( normal, c3ga::op( vector, normal ) ) );
	return distance;
}

bool LineSegment::CalculateIntersectionWith( const LineSegment& lineSegment, c3ga::vectorE3GA& intersectionPoint ) const
{
	c3ga::bivectorE3GA bivector = CalculateLineVector() ^ lineSegment.CalculateLineVector();
	if( bivector.get_e1_e2() == 0.0 )
		return false;		// The line segments are parallel.

	c3ga::vectorE3GA vector = bivector * c3ga::I3;
	intersectionPoint.set_e1( vector.get_e1() / vector.get_e3() );
	intersectionPoint.set_e2( vector.get_e2() / vector.get_e3() );
	intersectionPoint.set_e3( 0.0 );

	if( !ContainsPoint( intersectionPoint ) )
		return false;

	if( !lineSegment.ContainsPoint( intersectionPoint ) )
		return false;

	return true;
}

c3ga::vectorE3GA LineSegment::CalculateLineVector( void ) const
{
	c3ga::vectorE3GA vector = vertex[1] - vertex[0];
	c3ga::vectorE3GA normal( c3ga::vectorE3GA::coord_e1_e2_e3, -vector.get_e2(), vector.get_e1(), 0.0 );
	normal = c3ga::unit( normal );
	double dot = c3ga::lc( vertex[0], normal );
	vector = normal - c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, dot );
	return vector;
}

bool LineSegment::ContainsPoint( const c3ga::vectorE3GA& point, double eps /*= 1e-7*/ ) const
{
	double totalLength = c3ga::norm( point - vertex[0] ) + c3ga::norm( vertex[1] - point );
	double length = CalculateLength();
	if( fabs( totalLength - length ) < eps )
		return true;
	return false;
}

bool LineSegment::PointOnLine( const c3ga::vectorE3GA& point, double eps /*= 1e-7*/ ) const
{
	c3ga::vectorE3GA vector = CalculateLineVector();
	c3ga::vectorE3GA homogenizedPoint = point;
	homogenizedPoint.set_e3( 1.0 );
	double dot = c3ga::lc( homogenizedPoint, vector );
	if( fabs( dot ) < eps )
		return true;
	return false;
}

double LineSegment::CalculateLength( void ) const
{
	return c3ga::norm( vertex[1] - vertex[0] );
}

// LineSegment.cpp