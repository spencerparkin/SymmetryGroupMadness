// Canvas.cpp

#include "Canvas.h"
#include "Application.h"
#include "Puzzle.h"
#include "Triangle.h"
#include "Frame.h"
#include "Shape.h"
#include <gl/GLU.h>
#include <wx/scopedptr.h>
#include <wx/msgdlg.h>
#include <math.h>

int Canvas::attributeList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };

Canvas::Canvas( wxWindow* parent ) : wxGLCanvas( parent, wxID_ANY, attributeList )
{
	context = nullptr;

	grab = nullptr;

	hitBuffer = nullptr;
	hitBufferSize = 0;

	Bind( wxEVT_PAINT, &Canvas::OnPaint, this );
	Bind( wxEVT_SIZE, &Canvas::OnSize, this );
	Bind( wxEVT_LEFT_DOWN, &Canvas::OnMouseLeftDown, this );
	Bind( wxEVT_RIGHT_DOWN, &Canvas::OnMouseRightDown, this );
	Bind( wxEVT_LEFT_UP, &Canvas::OnMouseLeftUp, this );
	Bind( wxEVT_RIGHT_UP, &Canvas::OnMouseRightUp, this );
	Bind( wxEVT_MOTION, &Canvas::OnMouseMotion, this );
	Bind( wxEVT_MOUSE_CAPTURE_LOST, &Canvas::OnMouseCaptureLost, this );
}

/*virtual*/ Canvas::~Canvas( void )
{
	delete context;
	delete grab;
}

void Canvas::BindContext( void )
{
	if( !context )
		context = new wxGLContext( this );

	SetCurrent( *context );
}

void Canvas::Render( GLenum renderMode, const wxPoint* pickingPoint /*= nullptr*/, int* triangleId /*= nullptr*/, bool pickShapes /*= true*/ )
{
	Puzzle* puzzle = wxGetApp().GetPuzzle();

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

	if( renderMode == GL_SELECT )
	{
		GLdouble x = pickingPoint->x;
		GLdouble y = GLdouble( viewport[3] ) - GLdouble( pickingPoint->y );
		GLdouble w = 2.0;
		GLdouble h = 2.0;
		gluPickMatrix( x, y, w, h, viewport );
	}

	gluOrtho2D( rectangle.xMin, rectangle.xMax, rectangle.yMin, rectangle.yMax );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt( 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
	
	if( puzzle )
		puzzle->Render( renderMode, pickShapes );

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

void Canvas::InitiateGrab( const wxPoint& mousePoint, Grab::Type grabType )
{
	if( grab )
		return;

	Puzzle* puzzle = wxGetApp().GetPuzzle();
	if( !puzzle )
		return;

	wxScopedPtr< Grab > newGrab( new Grab() );

	newGrab->type = grabType;
	newGrab->rotationAngle = 0.0;
	newGrab->rotationAxis.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 1.0 );
	newGrab->rotationAngleMultiple = M_PI;
	
	if( !CalculateMouseLocation( mousePoint, newGrab->anchorPoint ) )
		return;

	newGrab->shape = puzzle->GetShapeContainingPoint( newGrab->anchorPoint );
	if( !newGrab->shape )
		return;

	newGrab->pivotPoint = newGrab->shape->GetPivotPoint();

	if( grabType == Grab::ROTATION )
		newGrab->rotationAngleMultiple = newGrab->shape->GetRotationDelta();

	if( !puzzle->GrabShape( *newGrab->shape, newGrab->grabbedTriangleList ) )
		return;

	for( TriangleList::iterator iter = newGrab->grabbedTriangleList.begin(); iter != newGrab->grabbedTriangleList.end(); iter++ )
	{
		Triangle* triangle = *iter;
		newGrab->originalTriangleMap.insert( std::pair< int, Triangle* >( triangle->id, triangle->Clone() ) );
		triangle->sortKey = 1;
	}

	this->grab = newGrab.release();

	CaptureMouse();
	Refresh();
}

void Canvas::FinalizeGrab( bool commitRotation /*= true*/ )
{
	if( HasCapture() )
		ReleaseCapture();

	if( !grab )
		return;

	if( !commitRotation )
		grab->rotationAngle = 0.0;
	else
	{
		double rotationAngleRemainder = remainder( grab->rotationAngle, grab->rotationAngleMultiple );
		grab->rotationAngle -= rotationAngleRemainder;
	}

	grab->ApplyRotation();
	Refresh();

	for( TriangleList::iterator iter = grab->grabbedTriangleList.begin(); iter != grab->grabbedTriangleList.end(); iter++ )
	{
		Triangle* triangle = *iter;
		triangle->sortKey = 0;
	}

	delete grab;
	grab = nullptr;

	Puzzle* puzzle = wxGetApp().GetPuzzle();
	if( puzzle )
		wxGetApp().GetFrame()->GetStatusBar()->SetLabelText( wxString::Format( "Triangles: %d", puzzle->GetTriangleCount() ) );
}

void Canvas::ManageGrab( const wxPoint& mousePoint )
{
	if( !grab )
		return;

	c3ga::vectorE3GA mouseLocation;
	if( !CalculateMouseLocation( mousePoint, mouseLocation ) )
		return;

	c3ga::vectorE3GA dragVector = mouseLocation - grab->anchorPoint;
	double dragMagnitude = c3ga::norm( dragVector );
	dragVector = dragVector * ( 1.0 / dragMagnitude );

	if( grab->type == Grab::REFLECTION )
	{
		const c3ga::vectorE3GA* bestReflectionAxis = nullptr;
		double smallestDot = 0.0;
		const VectorArray& reflectionAxisArray = grab->shape->GetReflectionAxisArray();
		for( int i = 0; i < ( signed )reflectionAxisArray.size(); i++ )
		{
			const c3ga::vectorE3GA& reflectionAxis = reflectionAxisArray[i];
			double dot = fabs( c3ga::lc( reflectionAxis, dragVector ) );
			if( dot < smallestDot || !bestReflectionAxis )
			{
				bestReflectionAxis = &reflectionAxis;
				smallestDot = dot;
			}
		}

		if( !bestReflectionAxis )
			return;

		grab->rotationAxis = *bestReflectionAxis;

		c3ga::vectorE3GA vector = grab->pivotPoint - grab->anchorPoint;
		double ratio = c3ga::lc( c3ga::unit( vector ), dragVector * dragMagnitude ) / c3ga::norm( vector );
		grab->rotationAngle = ratio / 2.0 * M_PI;		// TODO: Determine sign.
	}
	else if( grab->type == Grab::ROTATION )
	{
		c3ga::vectorE3GA anchorVector = c3ga::unit( grab->anchorPoint - grab->pivotPoint );
		c3ga::vectorE3GA mouseVector = c3ga::unit( mouseLocation - grab->pivotPoint );
		
		double dot = c3ga::lc( anchorVector, mouseVector );
		grab->rotationAngle = acos( dot );

		c3ga::bivectorE3GA bivector = anchorVector ^ mouseVector;
		if( bivector.get_e1_e2() < 0.0 )
			grab->rotationAngle = 2.0 * M_PI - grab->rotationAngle;
	}
	else
		return;

	grab->ApplyRotation();
	Refresh();
}

void Canvas::OnMouseLeftDown( wxMouseEvent& event )
{
	if( event.ControlDown() )
	{
		wxPoint pickingPoint = event.GetPosition();
		int triangleId = 0;
		Render( GL_SELECT, &pickingPoint, &triangleId, false );

		wxMessageBox( wxString::Format( "tri-id: %d", triangleId ), "ID", wxICON_INFORMATION | wxCENTRE );
		
		Triangle* triangle = wxGetApp().GetPuzzle()->GetTriangleById( triangleId );
		if( triangle )
		{
			wxString data = wxString::Format( "(%1.2f,%1.2f)-(%1.2f,%1.2f)-(%1.2f,%1.2f)",
				triangle->vertex[0].point.get_e1(), triangle->vertex[0].point.get_e2(),
				triangle->vertex[1].point.get_e1(), triangle->vertex[1].point.get_e2(),
				triangle->vertex[2].point.get_e1(), triangle->vertex[2].point.get_e2() );
			wxMessageBox( data, "data" );

			triangle->sortKey = 1;
			triangle->color.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 );
			Refresh();
		}

		return;
	}

	InitiateGrab( event.GetPosition(), Grab::ROTATION );
}

void Canvas::OnMouseRightDown( wxMouseEvent& event )
{
	InitiateGrab( event.GetPosition(), Grab::REFLECTION );
}

void Canvas::OnMouseLeftUp( wxMouseEvent& event )
{
	FinalizeGrab();
}

void Canvas::OnMouseRightUp( wxMouseEvent& event )
{
	FinalizeGrab();
}

void Canvas::OnMouseMotion( wxMouseEvent& event )
{
	ManageGrab( event.GetPosition() );
}

void Canvas::OnMouseCaptureLost( wxMouseCaptureLostEvent& event )
{
	FinalizeGrab();
}

Canvas::Grab::~Grab( void )
{
	DeleteTriangleMap( originalTriangleMap );
}

void Canvas::Grab::ApplyRotation( void )
{
	for( TriangleList::iterator iter = grabbedTriangleList.begin(); iter != grabbedTriangleList.end(); iter++ )
	{
		Triangle* triangle = *iter;

		TriangleMap::iterator mapIter = originalTriangleMap.find( triangle->id );
		if( mapIter == originalTriangleMap.end() )
			continue;

		Triangle* originalTriangle = mapIter->second;

		c3ga::rotorE3GA rotor = c3ga::exp( rotationAxis * c3ga::I3 * ( -rotationAngle / 2.0 ) );

		for( int i = 0; i < 3; i++ )
			triangle->vertex[i].point = pivotPoint + c3ga::applyUnitVersor( rotor, originalTriangle->vertex[i].point - pivotPoint );
	}
}

// Canvas.cpp