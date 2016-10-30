// Application.h

#pragma once

#include <wx/app.h>

class Frame;
class Puzzle;
class Random;

class Application : public wxApp
{
public:

	Application( void );
	virtual ~Application( void );

	virtual bool OnInit( void ) override;
	virtual int OnExit( void ) override;

	bool SetPuzzle( Puzzle* puzzle );
	Puzzle* GetPuzzle( void );

	Frame* GetFrame( void ) { return frame; }

	Random* GetRandom( void ) { return random; }

	void UpdateFrameTitle( void );

private:

	Frame* frame;
	Puzzle* puzzle;
	Random* random;
};

wxDECLARE_APP( Application );

// Application.h