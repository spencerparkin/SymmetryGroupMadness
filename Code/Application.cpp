// Application.cpp

#include "Application.h"

wxIMPLEMENT_APP( Application );

Application::Application( void )
{
}

/*virtual*/ Application::~Application( void )
{
}

/*virtual*/ bool Application::OnInit( void )
{
	if( !wxApp::OnInit() )
		return false;

	return true;
}

/*virtual*/ int Application::OnExit( void )
{
	return wxApp::OnExit();
}

// Application.cpp