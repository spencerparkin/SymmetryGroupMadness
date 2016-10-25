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
	bool contains0 = triangle.ContainsPoint( vertex[0] );
	bool contains1 = triangle.ContainsPoint( vertex[1] );

	bool clipped = false;

	int intersectionCount = 0;
	c3ga::vectorE3GA intersectionPoint[2];

	for( int i = 0; i < 3; i++ )
	{
		LineSegment edge;
		int j = ( i + 1 ) % 3;
		edge.vertex[0] = triangle.vertex[i].point;
		edge.vertex[1] = triangle.vertex[j].point;
		
		c3ga::vectorE3GA point;
		if( CalculateIntersectionWith( edge, point ) )
		{
			wxASSERT( intersectionCount < 2 );
			intersectionPoint[ intersectionCount++ ] = point;
			clipped = true;
		}
	}

	if( !contains0 && !contains1 && !clipped )
		return false;

	LineSegment clippedLineSegment;

	if( !contains0 && !contains1 )
	{
		wxASSERT( intersectionCount == 2 );
		clippedLineSegment.vertex[0] = intersectionPoint[0];
		clippedLineSegment.vertex[1] = intersectionPoint[1];
	}
	else if( contains0 && !contains1 )
	{
		wxASSERT( intersectionCount >= 1 );
		clippedLineSegment.vertex[0] = vertex[0];
		clippedLineSegment.vertex[1] = intersectionPoint[0];
	}
	else if( contains1 && !contains0 )
	{
		wxASSERT( intersectionCount >= 1 );
		clippedLineSegment.vertex[0] = vertex[1];
		clippedLineSegment.vertex[1] = intersectionPoint[0];
	}
	else
	{
		clippedLineSegment.vertex[0] = vertex[0];
		clippedLineSegment.vertex[1] = vertex[1];
	}

	// Here we treat every case as if both vertices of the clipped line segment
	// are strictly interior to the triangle.  We choose the best tesselation.
	// Then we simply throw out degenerate triangles.

	int j = -1;
	double smallestDistance = 0.0;
	for( int i = 0; i < 3; i++ )
	{
		double distance = CalculateOrthogonalDistanceToLine( vertex[0] );
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
		double distance = c3ga::norm( clippedLineSegment.vertex[i] - vertex[j] );
		if( k == -1 || distance < smallestDistance )
		{
			smallestDistance = distance;
			k = i;
		}
	}

	const Triangle::Vertex* vertexA = &triangle.vertex[j];
	const Triangle::Vertex* vertexB = &triangle.vertex[ ( j + 1 ) % 3 ];
	const Triangle::Vertex* vertexC = &triangle.vertex[ ( j + 2 ) % 3 ];

	c3ga::vectorE3GA* vertexD = &clippedLineSegment.vertex[k];
	c3ga::vectorE3GA* vertexE = &clippedLineSegment.vertex[ ( k + 1 ) % 2 ];

	Triangle* newTriangle = new Triangle();
	newTriangle->vertex[0].point = vertexC->point;
	newTriangle->vertex[1].point = vertexA->point;
	newTriangle->vertex[2].point = *vertexD;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	newTriangle = new Triangle();
	newTriangle->vertex[0].point = vertexA->point;
	newTriangle->vertex[1].point = vertexB->point;
	newTriangle->vertex[2].point = *vertexD;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	newTriangle = new Triangle();
	newTriangle->vertex[0].point = *vertexE;
	newTriangle->vertex[1].point = *vertexD;
	newTriangle->vertex[2].point = vertexB->point;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	newTriangle = new Triangle();
	newTriangle->vertex[0].point = vertexC->point;
	newTriangle->vertex[1].point = *vertexD;
	newTriangle->vertex[2].point = *vertexE;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	newTriangle = new Triangle();
	newTriangle->vertex[0].point = vertexC->point;
	newTriangle->vertex[1].point = *vertexE;
	newTriangle->vertex[2].point = vertexB->point;
	AddNonDegenerateTriangle( newTriangle, tessellatedTriangleList );

	return false;
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

	if( !SatisfiesTriangleInequality( intersectionPoint ) )
		return false;

	if( !lineSegment.SatisfiesTriangleInequality( intersectionPoint ) )
		return false;

	return true;
}

bool LineSegment::SatisfiesTriangleInequality( const c3ga::vectorE3GA& point ) const
{
	if( c3ga::norm( point - vertex[0] ) + c3ga::norm( vertex[1] - point ) <= CalculateLength() )
		return true;
	return false;
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

double LineSegment::CalculateLength( void ) const
{
	return c3ga::norm( vertex[1] - vertex[0] );
}

// LineSegment.cpp