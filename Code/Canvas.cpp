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
	Bind( wxEVT_MOUSE_CAPTURE_LOST, &Canvas::OnMouseCaptureLost, this );
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

void Canvas::Render( GLenum renderMode, const wxPoint* pickingPoint /*= nullptr*/, int* triangleId /*= nullptr*/ )
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

	Puzzle* puzzle = wxGetApp().GetPuzzle();

	GLdouble aspectRatio = GLdouble( viewport[2] ) / GLdouble( viewport[3] );

	Rectangle_ rectangle;
	rectangle.xMin = -1.0;
	rectangle.xMax = 1.0;
	rectangle.yMin = -1.0;
	rectangle.yMax = 1.0;

	if( puzzle )
	{
		rectangle = *puzzle->GetRectangle();
		rectangle.ShrinkToMatchAspectRatio( aspectRatio );
	}

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( rectangle.xMin, rectangle.xMax, rectangle.yMin, rectangle.yMax );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt( 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
	
	if( puzzle )
		puzzle->Render( renderMode );

	glFlush();

	if( renderMode == GL_SELECT )
	{
		int hitCount = glRenderMode( GL_RENDER );

		if( puzzle )
			puzzle->ProcessHitRecords( hitBuffer, hitBufferSize, hitCount, triangleId );

		delete[] hitBuffer;
		hitBuffer = nullptr;
		hitBufferSize = 0;
	}
	else if( renderMode == GL_RENDER )
	{
		SwapBuffers();
	}
}

bool Canvas::CalculateMouseLocation( const wxPoint& mousePoint, c3ga::vectorE3GA& mouseLocation )
{
	Puzzle* puzzle = wxGetApp().GetPuzzle();
	if( !puzzle )
		return false;

	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	Rectangle_ viewportRectangle;
	viewportRectangle.xMin = double( viewport[0] );
	viewportRectangle.yMin = double( viewport[1] );
	viewportRectangle.xMax = double( viewport[2] );
	viewportRectangle.yMax = double( viewport[3] );

	viewportRectangle.ExpandToMatchAspectRatio( puzzle->GetRectangle()->GetAspectRatio() );

	mouseLocation.set_e1( double( mousePoint.x ) );
	mouseLocation.set_e2( double( viewport[3] - mousePoint.y ) );
	mouseLocation.set_e3( 0.0 );

	viewportRectangle.LinearMap( *puzzle->GetRectangle(), mouseLocation );
	
	return true;
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
}

void Canvas::OnMouseLeftUp( wxMouseEvent& event )
{
}

void Canvas::OnMouseMotion( wxMouseEvent& event )
{
}

void Canvas::OnMouseCaptureLost( wxMouseCaptureLostEvent& event )
{
}

// Canvas.cpp