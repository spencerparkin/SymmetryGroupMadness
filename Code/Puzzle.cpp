// Puzzle.cpp

#include "Puzzle.h"
#include "Shape.h"
#include "Triangle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Texture.h"
#include "BoxTree.h"
#include "Application.h"
#include "Random.h"
#include "Frame.h"
#include <wx/glcanvas.h>
#include <wx/msgdlg.h>

Puzzle::Puzzle( void )
{
	modified = false;
	level = 0;
	triangleList = new TriangleList();
	rectangle = nullptr;
	texture = nullptr;
}

/*virtual*/ Puzzle::~Puzzle( void )
{
	DeleteTriangleList( *triangleList );
	delete triangleList;

	DeleteShapeList( shapeList );

	delete rectangle;
	delete texture;
}

void Puzzle::ResetTriangles( void )
{
	DeleteTriangleList( *triangleList );

	for( int i = -1; i <= 1; i++ )
	{
		for( int j = -1; j <= 1; j++ )
		{
			double w = 8.0;
			double h = 8.0;
			double x = double(i) * w;
			double y = double(j) * h;

			Triangle* triangle = new Triangle();
			triangle->vertex[0].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, x - w / 2.0, y - h / 2.0, 0.0 );
			triangle->vertex[1].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, x + w / 2.0, y - h / 2.0, 0.0 );
			triangle->vertex[2].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, x + w / 2.0, y + h / 2.0, 0.0 );
			triangleList->push_back( triangle );

			triangle = new Triangle();
			triangle->vertex[0].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, x - w / 2.0, y - h / 2.0, 0.0 );
			triangle->vertex[1].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, x + w / 2.0, y + h / 2.0, 0.0 );
			triangle->vertex[2].point.set( c3ga::vectorE3GA::coord_e1_e2_e3, x - w / 2.0, y + h / 2.0, 0.0 );
			triangleList->push_back( triangle );
		}
	}
}

void Puzzle::RecalculateAllUVs( void )
{
	GetRectangle();

	for( TriangleList::iterator iter = triangleList->begin(); iter != triangleList->end(); iter++ )
	{
		Triangle* triangle = *iter;

		for( int i = 0; i < 3; i++ )
			rectangle->CalculateUVs( triangle->vertex[i].point, triangle->vertex[i].u, triangle->vertex[i].v, texture );
	}
}

const Rectangle_* Puzzle::GetRectangle( void ) const
{
	// The rectangle of the puzzle never changes during the course
	// of the game, so we need only ever compute it once.
	if( !rectangle )
	{
		rectangle = new Rectangle_();

		rectangle->xMin = 9999.0;
		rectangle->xMax = -9999.0;
		rectangle->yMin = 9999.0;
		rectangle->yMax = -9999.0;

		for( TriangleList::const_iterator iter = triangleList->begin(); iter != triangleList->end(); iter++ )
		{
			const Triangle* triangle = *iter;
			for( int i = 0; i < 3; i++ )
			{
				const c3ga::vectorE3GA& point = triangle->vertex[i].point;
				if( point.get_e1() < rectangle->xMin )
					rectangle->xMin = point.get_e1();
				if( point.get_e1() > rectangle->xMax )
					rectangle->xMax = point.get_e1();
				if( point.get_e2() < rectangle->yMin )
					rectangle->yMin = point.get_e2();
				if( point.get_e2() > rectangle->yMax )
					rectangle->yMax = point.get_e2();
			}
		}
	}

	return rectangle;
}

bool Puzzle::GrabShape( const Shape& shape, TriangleList& grabbedTriangleList )
{
	modified = true;

	const TriangleList& shapeTriangleList = shape.GetTriangleList();

	LineSegmentList lineSegmentList;

	for( TriangleList::const_iterator iter = shapeTriangleList.begin(); iter != shapeTriangleList.end(); iter++ )
	{
		const Triangle* shapeTriangle = *iter;
		shapeTriangle->MakeLineSegments( lineSegmentList );
	}

	while( lineSegmentList.size() > 0 )
	{
		LineSegmentList::iterator iter = lineSegmentList.begin();
		LineSegment* lineSegment = *iter;

		TessellateTriangles( *lineSegment );

		lineSegmentList.erase( iter );
		delete lineSegment;
	}

	for( TriangleList::const_iterator iter = shapeTriangleList.begin(); iter != shapeTriangleList.end(); iter++ )
	{
		const Triangle* shapeTriangle = *iter;
		CollectTrianglesInTriangle( *shapeTriangle, grabbedTriangleList );
	}

	return( grabbedTriangleList.size() > 0 ? true : false );
}

void Puzzle::TessellateTriangles( const LineSegment& lineSegment )
{
	TriangleList* newTriangleList = new TriangleList();

	while( triangleList->size() > 0 )
	{
		TriangleList::iterator iter = triangleList->begin();
		Triangle* triangle = *iter;
		triangleList->erase( iter );

		if( lineSegment.TessellateTriangle( *triangle, *newTriangleList ) )
			delete triangle;
		else
			newTriangleList->push_back( triangle );
	}

	delete triangleList;
	triangleList = newTriangleList;
}

void Puzzle::CollectTrianglesInTriangle( const Triangle& triangleCover, TriangleList& collectedTriangleList )
{
	for( TriangleList::iterator iter = triangleList->begin(); iter != triangleList->end(); iter++ )
	{
		Triangle* triangle = *iter;
		if( triangleCover.Covers( *triangle, 1e-5 ) )
			collectedTriangleList.push_back( triangle );
	}
}

void Puzzle::Render( int renderMode, bool pickShapes /*= true*/ ) const
{
	if( renderMode == GL_RENDER )
	{
		struct CompareFunctor
		{
			bool operator()( const Triangle* triangleA, const Triangle* triangleB )
			{
				return( triangleA->sortKey < triangleB->sortKey ? true : false );
			}
		};

		triangleList->sort( CompareFunctor() );

		if( !texture || !texture->Bind() )
			glDisable( GL_TEXTURE_2D );

		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glBegin( GL_TRIANGLES );

		for( TriangleList::const_iterator iter = triangleList->cbegin(); iter != triangleList->cend(); iter++ )
		{
			const Triangle* triangle = *iter;
			triangle->Render( renderMode );
		}

		glEnd();
	}
	else if( renderMode == GL_SELECT )
	{
		glDisable( GL_TEXTURE_2D );
		glPushName(0);

		if( !pickShapes )
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

			for( TriangleList::const_iterator iter = triangleList->cbegin(); iter != triangleList->cend(); iter++ )
			{
				const Triangle* triangle = *iter;
				glLoadName( triangle->id );

				glBegin( GL_TRIANGLES );
				triangle->Render( renderMode );
				glEnd();
			}
		}
	}

	if( renderMode == GL_RENDER || ( renderMode == GL_SELECT && pickShapes ) )
	{
		glDisable( GL_TEXTURE_2D );

		for( ShapeList::const_iterator iter = shapeList.cbegin(); iter != shapeList.cend(); iter++ )
		{
			const Shape* shape = *iter;
			shape->Render( renderMode );
		}
	}
}

void Puzzle::ProcessHitRecords( unsigned int* hitBuffer, int hitBufferSize, int hitCount, int* triangleId )
{
	*triangleId = 0;

	// If the hit-count is -1 (indicating overflow), we don't process anything.
	unsigned int* hitRecord = hitBuffer;
	float smallestZ = 0.f;
	for( int i = 0; i < hitCount; i++ )
	{
		unsigned int nameCount = hitRecord[0];
		float minZ = float( hitRecord[1] ) / float( 0x7FFFFFFFF );
		if( nameCount == 1 )
		{
			if( *triangleId == 0 || minZ < smallestZ )
			{
				smallestZ = minZ;
				*triangleId = ( signed )hitRecord[3];
			}
		}
		hitRecord += 3 + nameCount;
	}
}

Shape* Puzzle::GetShapeOwningTriangle( int triangleId )
{
	for( ShapeList::iterator iter = shapeList.begin(); iter != shapeList.end(); iter++ )
	{
		Shape* shape = *iter;
		if( shape->OwnsTriangle( triangleId ) )
			return shape;
	}

	return nullptr;
}

Shape* Puzzle::GetShapeContainingPoint( const c3ga::vectorE3GA& point )
{
	// Now because the shapes in the puzzle overlap, here, which one
	// we return of two overlapping shapes, remains undefined.  This is
	// fine, however, because there will be plenty of each shape that
	// doesn't overlap with some other shape.
	for( ShapeList::iterator iter = shapeList.begin(); iter != shapeList.end(); iter++ )
	{
		Shape* shape = *iter;
		if( shape->ContainsPoint( point ) )
			return shape;
	}

	return nullptr;
}

Triangle* Puzzle::GetTriangleById( int triangleId )
{
	for( TriangleList::iterator iter = triangleList->begin(); iter != triangleList->end(); iter++ )
	{
		Triangle* triangle = *iter;
		if( triangle->id == triangleId )
			return triangle;
	}

	return nullptr;
}

double Puzzle::CalculatePercentageSolved( void ) const
{
	GetRectangle();

	BoxTreeNode* rootNode = GenerateBoxTree( *rectangle, rectangle->GetArea() / 10.0 );

	for( TriangleList::const_iterator iter = triangleList->cbegin(); iter != triangleList->cend(); iter++ )
	{
		const Triangle* triangle = *iter;
		for( int i = 0; i < 3; i++ )
			rootNode->InsertVertex( triangle->vertex[i] );
	}

	BoxTreeStats boxTreeStats;
	boxTreeStats.vertexGroupCount = 0;
	boxTreeStats.solvedVertexGroupCount = 0;
	rootNode->CalculateBoxTreeStats( boxTreeStats );

	double percentageSolved = 100.0 * double( boxTreeStats.solvedVertexGroupCount ) / double( boxTreeStats.vertexGroupCount );

	delete rootNode;

	return percentageSolved;
}

bool Puzzle::Save( void )
{
	return false;
}

bool Puzzle::Load( void )
{
	return false;
}

bool Puzzle::SetupLevel( int level )
{
	this->level = level;

	ResetTriangles();
	DeleteShapeList( shapeList );

	if( !texture )
		texture = new Texture();

	texture->Unload();
	
	wxString texName = wxString::Format( "Texture%d.jpg", ( level % MAX_IMAGES ) );
	wxArrayString texFileArray;

	if( level < MAX_LEVELS )
	{
		texFileArray.Add( "Textures/" + texName );
		texFileArray.Add( wxString( wxGetenv( "SNAP" ) ) + wxString( "/share/SymmetryGroupMadness/Textures/" ) + texName );
	}
	else
	{
		texFileArray.Add( "Textures/Winner.jpg" );
	}

	if( !texture->Load( texFileArray ) )
		return false;

	RecalculateAllUVs();

	wxGetApp().GetFrame()->GetStatusBar()->SetLabelText( "Left-click and drag to rotate.  Right-click and drag to reflect." );

	switch( level )
	{
		case 1:
		{
			// Level 1 is just the dihedral group D_3.
			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, -2.0, 0.0 ), 8.0, 3, -M_PI / 6.0 );
			shapeList.push_back( shape );

			EnqueueScrambles( 5, 123 );
			return true;
		}
		case 2:
		{
			// Level 2 is just the dihedral group D_4.
			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 ), 8.0, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			EnqueueScrambles( 5, 0 );
			return true;
		}
		case 3:
		{
			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, -4.0, 0.0, 0.0 ), 6.0, 3 );
			shapeList.push_back( shape );

			shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 4.0, 0.0, 0.0 ), 6.0, 3, M_PI / 3.0 );
			shapeList.push_back( shape );

			EnqueueScrambles( 10, 0 );
			return true;
		}
		case 4:
		{
			double a = 6.0 / sqrt( 2.0 );

			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, -a / 2.0, -a / 2.0, 0.0 ), 6.0, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, a / 2.0, a / 2.0, 0.0 ), 6.0, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			EnqueueScrambles( 10, 0 );
			break;
		}
		case MAX_LEVELS:
		{
			// The "winner" level has no shapes so that there's no way to advance further.
			wxMessageBox( "Congratulations!  You've solved every level!  More levels will be added as new releases of this program are made.", "You win!", wxOK | wxCENTRE, wxGetApp().GetFrame() );
			return true;
		}
	}

	return false;
}

void Puzzle::EnqueueScrambles( int scrambleCount, int scrambleSeed )
{
	srand( scrambleSeed );

	scrambleQueue.clear();

	Random* random = wxGetApp().GetRandom();

	Shape* lastShape = nullptr;
	for( int i = 0; i < scrambleCount; i++ )
	{
		Scramble scramble;
		scramble.animationAngle = 0.0;

		do
		{
			int j = random->Integer( 0, shapeList.size() - 1 );
			ShapeList::iterator iter = shapeList.begin();
			while( j > 0 )
			{
				iter++;
				j--;
			}

			scramble.shape = *iter;
		}
		while( scramble.shape == lastShape && shapeList.size() > 1 );

		lastShape = scramble.shape;

		if( ( shapeList.size() > 2 && i % 2 == 0 ) || ( i % 4 > 2 ) )
		{
			int cyclicSubgroupOrder = int( 2.0 * M_PI / scramble.shape->GetRotationDelta() );

			scramble.rotationAxis.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 1.0 );
			scramble.rotationAngle = double( random->Integer( 1, cyclicSubgroupOrder - 1 ) ) * scramble.shape->GetRotationDelta();
		}
		else
		{
			int j = random->Integer( 0, scramble.shape->GetReflectionAxisArray().size() - 1 );
			scramble.rotationAxis = scramble.shape->GetReflectionAxisArray()[j];
			scramble.rotationAngle = M_PI;
		}		
		
		scrambleQueue.push_back( scramble );
	}

	wxGetApp().GetFrame()->timer.Start(1);
}

// Puzzle.cpp