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
	c3ga::vectorE3GA anchorPoint = vertex[0];

	VectorList vectorList;
	vectorList.push_back( vertex[0] );
	vectorList.push_back( vertex[1] );

	for( int i = 0; i < 3; i++ )
	{
		LineSegment edge;
		int j = ( i + 1 ) % 3;
		edge.vertex[0] = triangle.vertex[i].point;
		edge.vertex[1] = triangle.vertex[j].point;

		c3ga::vectorE3GA point;
		if( CalculateIntersectionWith( edge, point ) )
			vectorList.push_back( point );
	}

	struct CompareFunctor
	{
		CompareFunctor( const c3ga::vectorE3GA* anchorPoint )
		{
			this->anchorPoint = anchorPoint;
		}

		bool operator()( const c3ga::vectorE3GA& pointA, const c3ga::vectorE3GA& pointB )
		{
			double distanceA = c3ga::norm( pointA - *anchorPoint );
			double distanceB = c3ga::norm( pointB - *anchorPoint );
			return distanceA < distanceB ? true : false;
		}

		const c3ga::vectorE3GA* anchorPoint;
	};

	vectorList.sort( CompareFunctor( &anchorPoint ) );

	while( vectorList.size() > 0 )
	{
		VectorList::iterator iter = vectorList.begin();
		const c3ga::vectorE3GA& point = *iter;
		if( triangle.ContainsPoint( point ) )
			break;
		else
			vectorList.erase( iter );
	}

	while( vectorList.size() > 0 )
	{
		VectorList::iterator iter = vectorList.end();
		iter--;
		const c3ga::vectorE3GA& point = *iter;
		if( triangle.ContainsPoint( point ) )
			break;
		else
			vectorList.erase( iter );
	}

	if( vectorList.size() == 0 )
		return false;

	LineSegment clippedLineSegment;
	clippedLineSegment.vertex[0] = *vectorList.begin();
	clippedLineSegment.vertex[1] = vectorList.back();

	for( int i = 0; i < 3; i++ )
	{
		LineSegment edge;
		int j = ( i + 1 ) % 3;
		edge.vertex[0] = triangle.vertex[i].point;
		edge.vertex[1] = triangle.vertex[j].point;

		if( edge.ContainsPoint( clippedLineSegment.vertex[0] ) && edge.ContainsPoint( clippedLineSegment.vertex[1] ) )
			return false;
	}

	// Here we treat every case as if both vertices of the clipped line segment
	// are strictly interior to the triangle.  We choose the best tesselation.
	// Then we simply throw out degenerate triangles.

	int j = -1;
	double smallestDistance = 0.0;
	for( int i = 0; i < 3; i++ )
	{
		double distance = CalculateOrthogonalDistanceToLine( triangle.vertex[i].point );
		if( j == -1 || distance < smallestDistance )
		{
			smallestDistance = distance;
			j = i;
		}
	}

	int k = -1;
	smallestDistance = 0.0;
	for( int i = 0; i < 2; i++ )
	{
		double distance = c3ga::norm( clippedLineSegment.vertex[i] - triangle.vertex[j].point );
		if( k == -1 || distance < smallestDistance )
		{
			smallestDistance = distance;
			k = i;
		}
	}

	const c3ga::vectorE3GA* vertexA = &triangle.vertex[j].point;
	const c3ga::vectorE3GA* vertexB = &triangle.vertex[ ( j + 1 ) % 3 ].point;
	const c3ga::vectorE3GA* vertexC = &triangle.vertex[ ( j + 2 ) % 3 ].point;
	const c3ga::vectorE3GA* vertexD = &clippedLineSegment.vertex[k];
	const c3ga::vectorE3GA* vertexE = &clippedLineSegment.vertex[ ( k + 1 ) % 2 ];

	Triangle* newTriangle = new Triangle();
	newTriangle->vertex[0].point = *vertexC;
	newTriangle->vertex[1].point = *vertexA;
	newTriangle->vertex[2].point = *vertexD;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	newTriangle = new Triangle();
	newTriangle->vertex[0].point = *vertexA;
	newTriangle->vertex[1].point = *vertexB;
	newTriangle->vertex[2].point = *vertexD;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	newTriangle = new Triangle();
	newTriangle->vertex[0].point = *vertexE;
	newTriangle->vertex[1].point = *vertexD;
	newTriangle->vertex[2].point = *vertexB;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	newTriangle = new Triangle();
	newTriangle->vertex[0].point = *vertexC;
	newTriangle->vertex[1].point = *vertexD;
	newTriangle->vertex[2].point = *vertexE;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	newTriangle = new Triangle();
	newTriangle->vertex[0].point = *vertexC;
	newTriangle->vertex[1].point = *vertexE;
	newTriangle->vertex[2].point = *vertexB;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	return true;
}

/*static*/ void LineSegment::AddNonDegenerateTriangle( Triangle* newTriangle, TriangleList& triangleList )
{
	if( newTriangle->IsDegenerate() )
	{
		delete newTriangle;
		return;
	}

	triangleList.push_back( newTriangle );
	//newTriangle->CalculateUVs();
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