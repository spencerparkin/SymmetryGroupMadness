// Application.cpp

#include "Application.h"
#include "Frame.h"
#include "Puzzle.h"
#include "Random.h"
#include <wx/msgdlg.h>
#include <wx/image.h>

wxIMPLEMENT_APP( Application );

Application::Application( void )
{
	frame = nullptr;
	puzzle = nullptr;
	random = new Random();
}

/*virtual*/ Application::~Application( void )
{
	delete puzzle;
	delete random;
}

/*virtual*/ bool Application::OnInit( void )
{
	if( !wxApp::OnInit() )
		return false;

	wxInitAllImageHandlers();

	frame = new Frame();
	frame->SetSize( 50, 50, 700, 700 );
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

	if( puzzle )
		frame->SetTitle( wxString::Format( "Symmetry Group Maddness -- Level %d", puzzle->GetLevel() ) );
	else
		frame->SetTitle( "Symmetry Group Madness" );

	return true;
}

Puzzle* Application::GetPuzzle( void )
{
	return puzzle;
}

// Application.cpp