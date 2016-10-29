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
	VectorArray edgeHitArray;

	for( int i = 0; i < 3; i++ )
	{
		int j = ( i + 1 ) % 3;
		LineSegment edge;
		edge.vertex[0] = triangle.vertex[i].point;
		edge.vertex[1] = triangle.vertex[j].point;

		c3ga::vectorE3GA intersectionPoint;
		if( CalculateIntersectionWith( edge, intersectionPoint, false, true ) )
			edgeHitArray.push_back( intersectionPoint );
	}

	// 0 hits -- we don't cut the triangle.
	// 1 hit -- we're tangent and so don't cut.
	// 2 hits -- we may cut the triangle.
	// 3 hits -- we're tangential here too.
	if( edgeHitArray.size() != 2 )
		return false;

	LineSegment chord;
	chord.vertex[0] = *edgeHitArray.begin();
	chord.vertex[1] = edgeHitArray.back();

	if( !( chord.ContainsPoint( vertex[0] ) || chord.ContainsPoint( vertex[1] ) ||
		ContainsPoint( chord.vertex[0] ) || ContainsPoint( chord.vertex[1] ) ) )
	{
		return false;
	}

	// Get vertex list in CCW order.
	VectorArray vertexArray;	// TODO: May want to replace this with std::list< Triangle::Vertex >.

	for( int i = 0; i < 3; i++ )
	{
		int j = ( i + 1 ) % 3;
		LineSegment edge;
		edge.vertex[0] = triangle.vertex[i].point;
		edge.vertex[1] = triangle.vertex[j].point;

		vertexArray.push_back( edge.vertex[0] );

		// There may be duplicate vertices put on the list, but that's okay.
		for( int k = 0; k < 2; k++ )
			if( edge.ContainsPoint( chord.vertex[k] ) )
				vertexArray.push_back( chord.vertex[k] );	// TODO: New UVs may be as easy as lerps along edges.
	}

	wxASSERT( vertexArray.size() >= 5 );

	c3ga::vectorE3GA center( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
	for( int i = 0; i < vertexArray.size(); i++ )
		center += vertexArray[i];

	center = center * ( 1.0 / double( vertexArray.size() ) );

	double smallestDistance = 0.0;
	int bestVertex = -1;
	for( int i = 0; i < vertexArray.size(); i++ )
	{
		double distance = c3ga::norm( center - vertexArray[i] );
		if( bestVertex == -1 || distance < smallestDistance )
		{
			smallestDistance = distance;
			bestVertex = i;
		}
	}

	// This is not necessarily the best tessellation, but it should work.
	// I can conceive a recursive way of doing this, but I'm not sure what that gains us.
	for( int i = 0; i < vertexArray.size() - 2; i++ )
	{
		Triangle* triangle = new Triangle();
		triangle->vertex[0].point = vertexArray[ bestVertex ];
		triangle->vertex[1].point = vertexArray[ ( bestVertex + i + 1 ) % vertexArray.size() ];
		triangle->vertex[2].point = vertexArray[ ( bestVertex + i + 2 ) % vertexArray.size() ];
		if( triangle->IsDegenerate() )
			delete triangle;
		else
			tessellatedTriangleList.push_back( triangle );
	}

	return true;
}

double LineSegment::CalculateOrthogonalDistanceToLine( const c3ga::vectorE3GA& point ) const
{
	c3ga::vectorE3GA normal = c3ga::unit( vertex[1] - vertex[0] );
	c3ga::vectorE3GA vector = point - vertex[0];
	double distance = c3ga::norm( c3ga::lc( normal, c3ga::op( vector, normal ) ) );
	return distance;
}

bool LineSegment::CalculateIntersectionWith( const LineSegment& lineSegment, c3ga::vectorE3GA& intersectionPoint, bool mustHitThis, bool mustHitGiven ) const
{
	c3ga::bivectorE3GA bivector = CalculateLineVector() ^ lineSegment.CalculateLineVector();
	if( bivector.get_e1_e2() == 0.0 )
		return false;		// The line segments are parallel.  They either intersect not at all, in a single point, or an infinite number of points; we don't care?

	c3ga::vectorE3GA vector = bivector * c3ga::I3;
	intersectionPoint.set_e1( vector.get_e1() / vector.get_e3() );
	intersectionPoint.set_e2( vector.get_e2() / vector.get_e3() );
	intersectionPoint.set_e3( 0.0 );

	if( mustHitThis && !ContainsPoint( intersectionPoint ) )
		return false;

	if( mustHitGiven && !lineSegment.ContainsPoint( intersectionPoint ) )
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