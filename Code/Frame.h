// Frame.h

#pragma once

#include <wx/frame.h>
#include <wx/timer.h>

class Canvas;

class Frame : public wxFrame
{
public:

	Frame( void );
	virtual ~Frame( void );

	wxTimer timer;

private:

	enum
	{
		ID_NewGame = wxID_HIGHEST,
		ID_SaveGame,
		ID_LoadGame,
		ID_Exit,
		ID_About,
		ID_Solve,
		ID_Timer,
	};

	void OnNewGame( wxCommandEvent& event );
	void OnSaveGame( wxCommandEvent& event );
	void OnLoadGame( wxCommandEvent& event );
	void OnExit( wxCommandEvent& event );
	void OnAbout( wxCommandEvent& event );
	void OnSolve( wxCommandEvent& event );
	void OnUpdateMenuItemUI( wxUpdateUIEvent& event );
	void OnTimer( wxTimerEvent& event );

	Canvas* canvas;
};

// Frame.h
