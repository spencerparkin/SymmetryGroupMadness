// Canvas.h

#pragma once

#include "Container.h"
#include "Rectangle.h"
#include <wx/glcanvas.h>

class Puzzle;

class Canvas : public wxGLCanvas
{
public:

	static int attributeList[];

	Canvas( wxWindow* parent );
	virtual ~Canvas( void );

	bool AnimateAutoRotations( void );

private:

	void Render( GLenum renderMode, const wxPoint* pickingPoint = nullptr, int* triangleId = nullptr, bool pickShapes = true );

	void OnPaint( wxPaintEvent& event );
	void OnSize( wxSizeEvent& event );
	void OnMouseLeftDown( wxMouseEvent& event );
	void OnMouseRightDown( wxMouseEvent& event );
	void OnMouseLeftUp( wxMouseEvent& event );
	void OnMouseRightUp( wxMouseEvent& event );
	void OnMouseMotion( wxMouseEvent& event );
	void OnMouseCaptureLost( wxMouseCaptureLostEvent& event );

	void BindContext( void );

	bool CalculateMouseLocation( const wxPoint& mousePoint, c3ga::vectorE3GA& mouseLocation );

	wxGLContext* context;
	unsigned int* hitBuffer;
	int hitBufferSize;
	Rectangle_ rectangle;

	struct Grab
	{
		~Grab( void );

		TriangleList grabbedTriangleList;
		TriangleMap originalTriangleMap;
		c3ga::vectorE3GA rotationAxis;
		double rotationAngle;
		double rotationAngleMultiple;
		c3ga::vectorE3GA anchorPoint;
		c3ga::vectorE3GA pivotPoint;
		const Shape* shape;
		enum Type { ROTATION, REFLECTION };
		Type type;

		void ApplyRotation( bool changePermutation = true );
		void GenerateOriginalTriangleMap( void );
		void ResetSortKeys( void );
	};

	void InitiateGrab( const wxPoint& mousePoint, Grab::Type grabType );
	void FinalizeGrab( bool commitRotation = true );
	void ManageGrab( const wxPoint& mousePoint );

	Grab* grab;
	
	bool readyToAdvanceToNextLevel;

	double frameRate;			// Frames per second.
	double lastFrameTime;		// Seconds.
	double animationRate;		// Radians per second.
};

// Canvas.h
