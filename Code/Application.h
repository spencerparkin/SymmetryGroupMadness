// Application.h

#pragma once

#include <wx/app.h>

class Application : public wxApp
{
public:

	Application( void );
	virtual ~Application( void );

	virtual bool OnInit( void ) override;
	virtual int OnExit( void ) override;
};

wxDECLARE_APP( Application );

// Application.h