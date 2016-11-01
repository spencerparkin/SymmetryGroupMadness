// Frame.cpp

#include "Frame.h"
#include "Application.h"
#include "Puzzle.h"
#include "Canvas.h"
#include <wx/menu.h>
#include <wx/aboutdlg.h>
#include <wx/sizer.h>

Frame::Frame( void ) : wxFrame( 0, wxID_ANY, "Symmetry Group Madness" ), timer( this, ID_Timer )
{
	wxMenu* gameMenu = new wxMenu();
	wxMenuItem* newGameMenuItem = new wxMenuItem( gameMenu, ID_NewGame, "New Game", "Start a new game at level 1." );
	wxMenuItem* saveGameMenuItem = new wxMenuItem( gameMenu, ID_SaveGame, "Save Game", "Save your current game to disk." );
	wxMenuItem* loadGameMenuItem = new wxMenuItem( gameMenu, ID_LoadGame, "Load Game", "Load a previously saved game from disk." );
	wxMenuItem* exitMenuItem = new wxMenuItem( gameMenu, ID_Exit, "Exit", "Exit this program." );
	gameMenu->Append( newGameMenuItem );
	gameMenu->AppendSeparator();
	gameMenu->Append( saveGameMenuItem );
	gameMenu->Append( loadGameMenuItem );
	gameMenu->AppendSeparator();
	gameMenu->Append( exitMenuItem );

	wxMenu* helpMenu = new wxMenu();
	wxMenuItem* aboutMenuItem = new wxMenuItem( helpMenu, ID_About, "About", "Show the about-box." );
	helpMenu->Append( aboutMenuItem );

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append( gameMenu, "Game" );
	menuBar->Append( helpMenu, "Help" );
	SetMenuBar( menuBar );

	wxStatusBar* statusBar = new wxStatusBar( this );
	SetStatusBar( statusBar );

	Bind( wxEVT_MENU, &Frame::OnNewGame, this, ID_NewGame );
	Bind( wxEVT_MENU, &Frame::OnSaveGame, this, ID_SaveGame );
	Bind( wxEVT_MENU, &Frame::OnLoadGame, this, ID_LoadGame );
	Bind( wxEVT_MENU, &Frame::OnExit, this, ID_Exit );
	Bind( wxEVT_MENU, &Frame::OnAbout, this, ID_About );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateMenuItemUI, this, ID_NewGame );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateMenuItemUI, this, ID_SaveGame );
	Bind( wxEVT_UPDATE_UI, &Frame::OnUpdateMenuItemUI, this, ID_LoadGame );
	Bind( wxEVT_TIMER, &Frame::OnTimer, this, ID_Timer );

	canvas = new Canvas( this );

	wxBoxSizer* boxSizer = new wxBoxSizer( wxVERTICAL );
	boxSizer->Add( canvas, 1, wxGROW );
	SetSizer( boxSizer );
}

/*virtual*/ Frame::~Frame( void )
{
}

void Frame::OnExit( wxCommandEvent& event )
{
	wxGetApp().SetPuzzle( nullptr );

	Close( true );
}

void Frame::OnAbout( wxCommandEvent& event )
{
	wxAboutDialogInfo aboutDialogInfo;

	aboutDialogInfo.SetName( "Symmetry Group Madness" );
	aboutDialogInfo.SetVersion( "1.0" );
	aboutDialogInfo.SetDescription( "This program is free software and distributed under the MIT license." );
	aboutDialogInfo.SetCopyright( "Copyright (C) 2016 Spencer T. Parkin <spencertparkin@gmail.com>" );
	//aboutDialogInfo.SetWebSite( "http://spencerparkin.github.io/SymmetryGroupMadness" );

	wxAboutBox( aboutDialogInfo );
}

void Frame::OnTimer( wxTimerEvent& event )
{
	if( !canvas->AnimateScrambles() )
	{
		event.GetTimer().Stop();
	}
}

void Frame::OnNewGame( wxCommandEvent& event )
{
	if( wxGetApp().SetPuzzle( nullptr ) )
	{
		Puzzle* puzzle = new Puzzle();
		puzzle->SetupLevel(1);
		wxGetApp().SetPuzzle( puzzle );
		canvas->Refresh();
	}
}

void Frame::OnSaveGame( wxCommandEvent& event )
{
	Puzzle* puzzle = wxGetApp().GetPuzzle();
	if( puzzle )
		puzzle->Save();
}

void Frame::OnLoadGame( wxCommandEvent& event )
{
	wxGetApp().SetPuzzle( nullptr );

	Puzzle* puzzle = new Puzzle();
	if( !puzzle->Load() )
		delete puzzle;
	else
		wxGetApp().SetPuzzle( puzzle );
	canvas->Refresh();
}

void Frame::OnUpdateMenuItemUI( wxUpdateUIEvent& event )
{
	switch( event.GetId() )
	{
		case ID_NewGame:
		{
			event.Enable( true );
			break;
		}
		case ID_SaveGame:
		{
			Puzzle* puzzle = wxGetApp().GetPuzzle();
			event.Enable( ( puzzle && puzzle->modified ) ? true : false );
			break;
		}
		case ID_LoadGame:
		{
			event.Enable( true );
			break;
		}
	}
}

// Frame.cpp