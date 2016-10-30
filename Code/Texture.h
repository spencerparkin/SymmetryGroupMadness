// Texture.h

#pragma once

#include <wx/glcanvas.h>
#include <wx/image.h>

class Texture
{
public:

	Texture( void );
	virtual ~Texture( void );

	bool Load( const wxString& texFile );
	bool Load( const wxArrayString& texFileArray );
	bool Unload( void );

	bool Bind( void );

	const wxImage* GetImage( void ) const { return image; }

private:

	GLuint texName;
	wxImage* image;
	wxString texFile;
};

// Texture.h
