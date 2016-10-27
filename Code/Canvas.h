// Canvas.h

#pragma once

#include <wx/glcanvas.h>
#include "Container.h"
#include "Rectangle.h"

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

	void BindContext( void );

	bool CalculateMouseLocation( const wxPoint& mousePoint, c3ga::vectorE3GA& mouseLocation );

	wxGLContext* context;
	unsigned int* hitBuffer;
	int hitBufferSize;
	Rectangle_ rectangle;
};

// Canvas.h
