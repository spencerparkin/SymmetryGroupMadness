// Texture.cpp

#include "Texture.h"

Texture::Texture( void )
{
	image = nullptr;
	texName = GL_INVALID_VALUE;
}

/*virtual*/ Texture::~Texture( void )
{
	( void )Unload();
}

bool Texture::Load( const wxArrayString& texFileArray )
{
	for( int i = 0; i < texFileArray.size(); i++ )
		if( Load( texFileArray[i] ) )
			return true;

	return false;
}

bool Texture::Load( const wxString& texFile )
{
	bool success = false;

	do
	{
		if( image )
			break;

		image = new wxImage();

		this->texFile = texFile;

		if( !image->LoadFile( texFile, wxBITMAP_TYPE_ANY ) )
			break;

		glGenTextures( 1, &texName );
		if( texName == GL_INVALID_VALUE )
			break;

		glBindTexture( GL_TEXTURE_2D, texName );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		const unsigned char* imageData = image->GetData();
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image->GetWidth(), image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imageData );

		success = true;
	}
	while( false );

	if( !success )
		Unload();

	return success;
}

bool Texture::Unload( void )
{
	if( image )
	{
		delete image;
		image = nullptr;
	}
	
	if( texName != GL_INVALID_VALUE )
	{
		glDeleteTextures( 1, &texName );
		texName = GL_INVALID_VALUE;
	}

	return true;
}

// Texture.cpp