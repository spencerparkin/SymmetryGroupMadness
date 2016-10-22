// Application.cpp

#include "Application.h"
#include "Frame.h"
#include "Puzzle.h"

wxIMPLEMENT_APP( Application );

Application::Application( void )
{
	frame = nullptr;
	puzzle = nullptr;
}

/*virtual*/ Application::~Application( void )
{
	delete puzzle;
}

/*virtual*/ bool Application::OnInit( void )
{
	if( !wxApp::OnInit() )
		return false;

	puzzle = new Puzzle();

	frame = new Frame();
	frame->Show();

	return true;
}

/*virtual*/ int Application::OnExit( void )
{
	return wxApp::OnExit();
}

// Application.cpp