// Canvas.h

#pragma once

#include <wx/glcanvas.h>

class Canvas : public wxGLCanvas
{
public:

	static int attributeList[];

	Canvas( wxWindow* parent );
	virtual ~Canvas( void );

private:

	void Render( GLenum renderMode, wxPoint* pickingPoint = nullptr );

	void OnPaint( wxPaintEvent& event );
	void OnSize( wxSizeEvent& event );
	void OnMouseLeftDown( wxMouseEvent& event );
	void OnMouseLeftUp( wxMouseEvent& event );
	void OnMouseMotion( wxMouseEvent& event );

	void BindContext( void );

	wxGLContext* context;
	unsigned int* hitBuffer;
	int hitBufferSize;
};

// Canvas.h
