// Triangle.cpp

#include "Triangle.h"
#include "LineSegment.h"
#include "Application.h"
#include "Random.h"
#include <wx/glcanvas.h>

int Triangle::nextId = 1;

Triangle::Triangle( void )
{
	id = nextId++;
	sortKey = 0;

	for( int i = 0; i < 3; i++ )
	{
		Vertex* vtx = &vertex[i];
		vtx->point.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
		vtx->u = 0.0;
		vtx->v = 0.0;
	}

	color = wxGetApp().GetRandom()->Vector( 0.5, 1.0 );
}

/*virtual*/ Triangle::~Triangle( void )
{
}

Triangle* Triangle::Clone( void ) const
{
	Triangle* triangle = new Triangle();

	for( int i = 0; i < 3; i++ )
		triangle->vertex[i] = vertex[i];

	triangle->color = color;

	return triangle;
}

void Triangle::MakeLineSegments( LineSegmentList& lineSegmentList ) const
{
	for( int i = 0; i < 3; i++ )
	{
		const Vertex* vtx0 = &vertex[i];
		const Vertex* vtx1 = &vertex[ ( i + 1 ) % 3 ];

		for( LineSegmentList::iterator iter = lineSegmentList.begin(); iter != lineSegmentList.end(); iter++ )
		{
			LineSegment* lineSegment = *iter;
			if( c3ga::norm( lineSegment->GetVertex(0) - vtx0->point ) == 0.0 &&
				c3ga::norm( lineSegment->GetVertex(1) - vtx1->point ) == 0.0 )
			{
				return;
			}
		}

		LineSegment* lineSegment = new LineSegment( vtx0->point, vtx1->point );
		lineSegmentList.push_back( lineSegment );
	}
}

bool Triangle::IsDegenerate( double eps /*= 1e-7*/ ) const
{
	c3ga::bivectorE3GA bivector = ( vertex[1].point - vertex[0].point ) ^ ( vertex[2].point - vertex[0].point );
	if( fabs( bivector.get_e1_e2() / 2.0 ) < eps )
		return true;
	return false;
}

bool Triangle::Covers( const Triangle& triangle, double eps /*= 1e-7*/ ) const
{
	for( int i = 0; i < 3; i++ )
	{
		const Vertex* vtx = &triangle.vertex[i];
		if( !ContainsPoint( vtx->point, eps ) )
			return false;
	}

	return true;
}

// Note that here we assume that the given point as well as this triangle is in the XY-plane.
bool Triangle::ContainsPoint( const c3ga::vectorE3GA& point, double eps /*= 0.0*/ ) const
{
	for( int i = 0; i < 3; i++ )
	{
		int j = ( i + 1 ) % 3;
		c3ga::bivectorE3GA bivector = c3ga::op( vertex[j].point - vertex[i].point, point - vertex[i].point );
		if( bivector.get_e1_e2() < -eps )
			return false;
	}

	return true;
}

void Triangle::Render( int renderMode ) const
{
	glColor3d( color.get_e1(), color.get_e2(), color.get_e3() );

	for( int i = 0; i < 3; i++ )
	{
		const Vertex* vtx = &vertex[i];
		glTexCoord2d( vtx->u, vtx->v );
		glVertex3d( vtx->point.get_e1(), vtx->point.get_e2(), vtx->point.get_e3() );
	}
}

bool Triangle::SaveToXml( wxXmlNode* xmlNode ) const
{
	for( int i = 0; i < 3; i++ )
	{
		const Vertex* vtx = &vertex[i];

		wxXmlNode* xmlVertexNode = new wxXmlNode( xmlNode, wxXML_ELEMENT_NODE, "Vertex" );
		xmlVertexNode->AddAttribute( new wxXmlAttribute( "order", wxString::Format( "%d", i ) ) );
		
		new wxXmlNode( new wxXmlNode( xmlVertexNode, wxXML_ELEMENT_NODE, "X" ), wxXML_TEXT_NODE, "", wxString::Format( "%lf", vtx->point.get_e1() ) );
		new wxXmlNode( new wxXmlNode( xmlVertexNode, wxXML_ELEMENT_NODE, "Y" ), wxXML_TEXT_NODE, "", wxString::Format( "%lf", vtx->point.get_e2() ) );
		new wxXmlNode( new wxXmlNode( xmlVertexNode, wxXML_ELEMENT_NODE, "Z" ), wxXML_TEXT_NODE, "", wxString::Format( "%lf", vtx->point.get_e3() ) );
		new wxXmlNode( new wxXmlNode( xmlVertexNode, wxXML_ELEMENT_NODE, "U" ), wxXML_TEXT_NODE, "", wxString::Format( "%lf", vtx->u ) );
		new wxXmlNode( new wxXmlNode( xmlVertexNode, wxXML_ELEMENT_NODE, "V" ), wxXML_TEXT_NODE, "", wxString::Format( "%lf", vtx->v ) );
	}

	return true;
}

bool Triangle::LoadFromXml( const wxXmlNode* xmlNode )
{
	for( int i = 0; i < 3; i++ )
	{
		Vertex* vtx = &vertex[i];

		wxXmlNode* xmlVertexNode = xmlNode->GetChildren();
		while( xmlVertexNode && xmlVertexNode->GetAttribute( "order" ) != wxString::Format( "%d", i ) )
			xmlVertexNode = xmlVertexNode->GetNext();

		if( !xmlVertexNode )
			return false;

		wxXmlNode* xmlComponentNode = xmlVertexNode->GetChildren();
		while( xmlComponentNode )
		{
			if( !xmlComponentNode->GetChildren() )
				return false;

			double component = 0.0;
			wxString content = xmlComponentNode->GetChildren()->GetContent();
			if( !content.ToDouble( &component ) )
				return false;

			if( xmlComponentNode->GetName() == "X" )
				vtx->point.set_e1( component );
			else if( xmlComponentNode->GetName() == "Y" )
				vtx->point.set_e2( component );
			else if( xmlComponentNode->GetName() == "Z" )
				vtx->point.set_e3( component );
			else if( xmlComponentNode->GetName() == "U" )
				vtx->u = component;
			else if( xmlComponentNode->GetName() == "V" )
				vtx->v = component;
			else
				return false;

			xmlComponentNode = xmlComponentNode->GetNext();
		}
	}

	return true;
}

// Triangle.cpp