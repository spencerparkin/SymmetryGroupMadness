// Application.h

#pragma once

#include <wx/app.h>

class Frame;
class Puzzle;

class Application : public wxApp
{
public:

	Application( void );
	virtual ~Application( void );

	virtual bool OnInit( void ) override;
	virtual int OnExit( void ) override;

	Frame* frame;
	Puzzle* puzzle;
};

wxDECLARE_APP( Application );

// Application.h