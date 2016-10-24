// Frame.h

#pragma once

#include <wx/frame.h>

class Canvas;

class Frame : public wxFrame
{
public:

	Frame( void );
	virtual ~Frame( void );

private:

	enum
	{
		ID_NewGame,
		ID_SaveGame,
		ID_LoadGame,
		ID_Exit,
		ID_About,
	};

	void OnNewGame( wxCommandEvent& event );
	void OnSaveGame( wxCommandEvent& event );
	void OnLoadGame( wxCommandEvent& event );
	void OnExit( wxCommandEvent& event );
	void OnAbout( wxCommandEvent& event );
	void OnUpdateMenuItemUI( wxUpdateUIEvent& event );

	Canvas* canvas;
};

// Frame.h
