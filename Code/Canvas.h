// Canvas.h

#pragma once

#include <wx/glcanvas.h>
#include "List.h"

class Canvas : public wxGLCanvas
{
public:

	static int attributeList[];

	Canvas( wxWindow* parent );
	virtual ~Canvas( void );

private:

	void Render( GLenum renderMode, const wxPoint* pickingPoint = nullptr, int* triangleId = nullptr );

	void OnPaint( wxPaintEvent& event );
	void OnSize( wxSizeEvent& event );
	void OnMouseLeftDown( wxMouseEvent& event );
	void OnMouseLeftUp( wxMouseEvent& event );
	void OnMouseMotion( wxMouseEvent& event );
	void OnMouseCaptureLost( wxMouseCaptureLostEvent& event );

	bool AcquireGrab( const wxPoint& pickingPoint );
	bool ReleaseGrab( void );

	void BindContext( void );

	wxGLContext* context;
	unsigned int* hitBuffer;
	int hitBufferSize;

	struct Grab
	{
		TriangleList triangleList;

		enum Type { REFLECTION, ROTATION };
		Type type;

		// For rotations, this is always the +Z-axis.
		// For reflections, this is the reflection axis.
		c3ga::vectorE3GA rotationAxis;

		// For rotations, this is obvious.  For reflections,
		// this rotates us about the reflection axis.
		double rotationAngle;

		// For rotations, this is dictated by the rotational symmetry
		// of the grabbed shape.  For reflections, this is always PI.
		double rotationAngleMultiple;
	};

	Grab* grab;
};

// Canvas.h
