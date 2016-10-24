// Application.cpp

#include "Application.h"
#include "Frame.h"
#include "Puzzle.h"
#include <wx/msgdlg.h>

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

	frame = new Frame();
	frame->Show();

	return true;
}

/*virtual*/ int Application::OnExit( void )
{
	return wxApp::OnExit();
}

bool Application::SetPuzzle( Puzzle* puzzle )
{
	if( this->puzzle )
	{
		if( this->puzzle->modified )
		{
			int answer = wxMessageBox( "Save current game?", "Save?", wxYES_NO | wxCANCEL | wxCENTRE, frame );
			if( answer == wxCANCEL )
				return false;
			if( answer == wxYES )
				if( !this->puzzle->Save() )
					return false;
		}

		delete this->puzzle;
	}

	this->puzzle = puzzle;

	return true;
}

Puzzle* Application::GetPuzzle( void )
{
	return puzzle;
}

// Application.cpp