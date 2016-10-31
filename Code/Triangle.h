// Triangle.h

#pragma once

#include "c3ga/c3ga.h"
#include "Container.h"
#include <wx/xml/xml.h>

class Triangle
{
public:

	Triangle( void );
	virtual ~Triangle( void );

	void MakeLineSegments( LineSegmentList& lineSegmentList ) const;

	bool Covers( const Triangle& triangle, double eps = 1e-7 ) const;
	bool ContainsPoint( const c3ga::vectorE3GA& point, double eps = 0.0 ) const;
	bool IsDegenerate( double eps = 1e-7 ) const;

	void Render( int renderMode ) const;

	Triangle* Clone( void ) const;

	bool SaveToXml( wxXmlNode* xmlNode ) const;
	bool LoadFromXml( const wxXmlNode* xmlNode );

	Vertex vertex[3];
	c3ga::vectorE3GA color;
	int id;
	int sortKey;

	static int nextId;
};

// Triangle.h