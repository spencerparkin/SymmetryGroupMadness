// Canvas.cpp

#include "Canvas.h"
#include "Application.h"
#include "Puzzle.h"
#include <gl/GLU.h>

int Canvas::attributeList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };

Canvas::Canvas( wxWindow* parent ) : wxGLCanvas( parent, wxID_ANY, attributeList )
{
	context = nullptr;

	hitBuffer = nullptr;
	hitBufferSize = 0;

	Bind( wxEVT_PAINT, &Canvas::OnPaint, this );
	Bind( wxEVT_SIZE, &Canvas::OnSize, this );
	Bind( wxEVT_LEFT_DOWN, &Canvas::OnMouseLeftDown, this );
	Bind( wxEVT_LEFT_UP, &Canvas::OnMouseLeftUp, this );
	Bind( wxEVT_MOTION, &Canvas::OnMouseMotion, this );
}

/*virtual*/ Canvas::~Canvas( void )
{
	delete context;
}

void Canvas::BindContext( void )
{
	if( !context )
		context = new wxGLContext( this );

	SetCurrent( *context );
}

void Canvas::Render( GLenum renderMode, wxPoint* pickingPoint /*= nullptr*/ )
{
	BindContext();

	glClearColor( 0.f, 0.f, 0.f, 1.f );

	if( renderMode == GL_SELECT )
	{
		hitBufferSize = 512;
		hitBuffer = new unsigned int[ hitBufferSize ];
		glSelectBuffer( hitBufferSize, hitBuffer );
		glRenderMode( GL_SELECT );
		glInitNames();
	}

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	if( renderMode == GL_SELECT )
	{
		GLdouble x = pickingPoint->x;
		GLdouble y = GLdouble( viewport[3] ) - GLdouble( pickingPoint->y );
		GLdouble w = 2.0;
		GLdouble h = 2.0;
		gluPickMatrix( x, y, w, h, viewport );
	}

	GLdouble foviAngle = 60.0;
	GLdouble aspectRatio = GLdouble( viewport[2] ) / GLdouble( viewport[3] );
	GLdouble nearPlane = 1.0;
	GLdouble farPlane = 100.0;
	gluPerspective( foviAngle, aspectRatio, nearPlane, farPlane );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt( 0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

	Puzzle* puzzle = wxGetApp().GetPuzzle();
	if( puzzle )
		puzzle->Render( renderMode );

	glFlush();

	if( renderMode == GL_SELECT )
	{
		int hitCount = glRenderMode( GL_RENDER );

		if( puzzle )
			puzzle->ProcessHitRecords( hitBuffer, hitBufferSize, hitCount );

		delete[] hitBuffer;
		hitBuffer = nullptr;
		hitBufferSize = 0;
	}
	else if( renderMode == GL_RENDER )
	{
		SwapBuffers();
	}
}

void Canvas::OnPaint( wxPaintEvent& event )
{
	Render( GL_RENDER );
}

void Canvas::OnSize( wxSizeEvent& event )
{
	wxSize size = event.GetSize();
	glViewport( 0, 0, size.GetWidth(), size.GetHeight() );
	Refresh();
}

void Canvas::OnMouseLeftDown( wxMouseEvent& event )
{
	Puzzle* puzzle = wxGetApp().GetPuzzle();
	if( !puzzle )
		return;

	const ShapeList& shapeList = puzzle->GetShapeList();
	ShapeList::const_iterator iter = shapeList.begin();
	const Shape* shape = *iter;

	TriangleList grabbedTriangleList;
	puzzle->GrabShape( *shape, grabbedTriangleList );

	Refresh();
}

void Canvas::OnMouseLeftUp( wxMouseEvent& event )
{
}

void Canvas::OnMouseMotion( wxMouseEvent& event )
{
}

// Canvas.cpp