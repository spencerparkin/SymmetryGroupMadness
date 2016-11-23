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
	double eps = 1e-7;

	for( int i = 0; i < 3; i++ )
	{
		int j = ( i + 1 ) % 3;
		LineSegment edge;
		edge.vertex[0] = triangle.vertex[i].point;
		edge.vertex[1] = triangle.vertex[j].point;

		c3ga::vectorE3GA intersectionPoint;
		if( CalculateIntersectionWith( edge, intersectionPoint, false, true ) )
		{
			int k;
			for( k = 0; k < ( int )edgeHitArray.size(); k++ )
				if( c3ga::norm( edgeHitArray[k] - intersectionPoint ) < eps )
					break;

			if( k == edgeHitArray.size() )
				edgeHitArray.push_back( intersectionPoint );
		}
	}

	// 0 hits -- we don't cut the triangle.
	// 1 hit -- we're tangent and so don't cut.
	// 2 distinct hits -- we may cut the triangle.
	// 3 distinct hits -- we're tangential here too.
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
	VertexArray vertexArray;

	int sharedVertex = -1;

	for( int i = 0; i < 3; i++ )
	{
		int j = ( i + 1 ) % 3;
		LineSegment edge;
		edge.vertex[0] = triangle.vertex[i].point;
		edge.vertex[1] = triangle.vertex[j].point;

		vertexArray.push_back( triangle.vertex[i] );

		// There may be duplicate vertices put on the list, but that's okay.
		for( int k = 0; k < 2; k++ )
		{
			if( edge.ContainsPoint( chord.vertex[k] ) )
			{
				// The shared vertex must be one of the two chord points.  Choose one arbitrarily.
				if( sharedVertex == -1 )
					sharedVertex = ( signed )vertexArray.size();

				Vertex vertex;
				vertex.point = chord.vertex[k];

				double lerp = c3ga::norm( vertex.point - edge.vertex[0] ) / edge.CalculateLength();
				vertex.u = triangle.vertex[i].u + lerp * ( triangle.vertex[j].u - triangle.vertex[i].u );
				vertex.v = triangle.vertex[i].v + lerp * ( triangle.vertex[j].v - triangle.vertex[i].v );

				vertexArray.push_back( vertex );
			}
		}
	}

	wxASSERT( vertexArray.size() >= 5 );
	wxASSERT( sharedVertex >= 0 );
	
	for( int i = 0; i < ( int )vertexArray.size() - 2; i++ )
	{
		Triangle* triangle = new Triangle();
		triangle->vertex[0] = vertexArray[ sharedVertex ];
		triangle->vertex[1] = vertexArray[ ( sharedVertex + i + 1 ) % vertexArray.size() ];
		triangle->vertex[2] = vertexArray[ ( sharedVertex + i + 2 ) % vertexArray.size() ];
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