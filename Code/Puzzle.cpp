// Puzzle.cpp

#include <rapidjson/writer.h>
#include "Puzzle.h"
#include "Shape.h"
#include "Triangle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Texture.h"
#include "Application.h"
#include "Random.h"
#include "Frame.h"
#include <wx/glcanvas.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/xml/xml.h>
#include <wx/filename.h>
#include <StabilizerChain.h>

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

// Some sort of compression would be a nice optimization for puzzles that get heavy on the triangles.
// In some cases, however, new triangles, I believe, are being created unnecessarily.
// I want to add a comment here that since writing this (quite some time ago), I believe there is
// a much better way to implement this game by using a graph-theory-like data-structure instead of
// cutting up a triangle mesh.  Graphs can be combined into one and then sub-graphs read out of the
// result.  Planar graphs (which happen to also be polygons) can be tessellated before rendering.
// Triangle UVs can be calculated from transforms.  For at least one reason, this is a better approach,
// because it drastically reduces the number of polygons, even after tessellation, that need to be
// processed during cutting and rendering, and so, much more interesting and elaborate puzzles could be
// constructed without worry of bogging down the puzzle engine.  But alas, I don't feel I have the time
// to go back and revisit this kind of program, or enough motivation to do so anyway.  When using this
// program, certain puzzles use a rediculous number of triangles when it is clear that no where near that
// many triangles is needed for the rendering or mechanics of the puzzle.  A better puzzle engine that
// is graph theory based is certainly possible and easily consievable.
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

void Puzzle::SortForRender( void )
{
	struct CompareFunctor
	{
		bool operator()( const Triangle* triangleA, const Triangle* triangleB )
		{
			return( triangleA->sortKey < triangleB->sortKey ? true : false );
		}
	};

	triangleList->sort( CompareFunctor() );
}

// TODO: It wouldn't be hard to render an outline for the shape that the mouse is hovering over.
//       Just keep a list of line segments of the triangles making up the shape.  Add a line segment
//       if it is not there, or remove it if it is already there.  Render the net effect.
void Puzzle::Render( int renderMode, bool pickShapes /*= true*/ ) const
{
	if( renderMode == GL_RENDER )
	{
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

		if( pointArray.size() > 0 )
		{
			glPointSize( 5.0 );
			glColor3f( 1.f, 0.f, 0.f );
			glDisable( GL_TEXTURE_2D );
			glBegin( GL_POINTS );
			
			for( int i = 0; i < pointArray.size(); i++ )
			{
				const c3ga::vectorE3GA& point = pointArray[i];
				glVertex2d( point.get_e1(), point.get_e2() );
			}

			glEnd();
		}
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

	if( /*renderMode == GL_RENDER ||*/ ( renderMode == GL_SELECT && pickShapes ) )
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

bool Puzzle::Save( wxString puzzleFile /*= wxEmptyString*/ ) const
{
	bool success = false;

	do 
	{
		wxXmlNode* xmlRootNode = new wxXmlNode( 0, wxXML_ELEMENT_NODE, "Puzzle" );
		wxXmlDocument xmlDocument;
		xmlDocument.SetRoot( xmlRootNode );

		if( puzzleFile.IsEmpty() )
		{
			wxFileDialog fileDialog( wxGetApp().GetFrame(), "Save game.", wxEmptyString, wxEmptyString, "XML files (*.xml)|*.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
			if( fileDialog.ShowModal() != wxID_OK )
				break;

			wxBusyCursor busyCursor;
			wxString path = fileDialog.GetPath();
			wxFileName fileName( path );
			fileName.SetExt( "xml" );
			puzzleFile = fileName.GetFullPath();
		}

		wxBusyCursor busyCursor;

		wxXmlNode* xmlTrianglePoolNode = new wxXmlNode( xmlRootNode, wxXML_ELEMENT_NODE, "TrianglePool" );

		TriangleList::const_iterator iter = triangleList->cbegin();
		while( iter != triangleList->cend() )
		{
			const Triangle* triangle = *iter;
			wxXmlNode* xmlTriangleNode = new wxXmlNode( xmlTrianglePoolNode, wxXML_ELEMENT_NODE, "Triangle" );
			if( !triangle->SaveToXml( xmlTriangleNode ) )
				break;
			iter++;
		}

		if( iter != triangleList->cend() )
			break;

		if( texture )
		{
			wxString texFile = texture->GetFile();
			xmlRootNode->AddAttribute( new wxXmlAttribute( "texture", texFile ) );
		}

		rapidjson::Document doc;
		doc.SetObject();

		rapidjson::Value permutationValue( rapidjson::kObjectType );
		permutation.GetToJsonValue( permutationValue, doc.GetAllocator() );

		doc.AddMember( "data", permutationValue, doc.GetAllocator() );

		rapidjson::StringBuffer buffer;
		rapidjson::Writer< rapidjson::StringBuffer > writer( buffer );
		if( doc.Accept( writer ) )
		{
			wxString jsonString = buffer.GetString();
			wxXmlNode* xmlPermutationNode = new wxXmlNode( xmlRootNode, wxXML_ELEMENT_NODE, "Permutation" );
			wxXmlNode* xmlDataNode = new wxXmlNode( xmlPermutationNode, wxXML_CDATA_SECTION_NODE, "Data" );
			xmlDataNode->SetContent( jsonString );
		}

		xmlRootNode->AddAttribute( new wxXmlAttribute( "level", wxString::Format( "%d", level ) ) );

		if( !xmlDocument.Save( puzzleFile ) )
			break;

		modified = false;
		success = true;
	}
	while( false );

	return success;
}

bool Puzzle::Load( wxString puzzleFile /*= wxEmptyString*/ )
{
	bool success = false;

	do 
	{
		if( puzzleFile.IsEmpty() )
		{
			wxFileDialog fileDialog( wxGetApp().GetFrame(), "Load game.", wxEmptyString, wxEmptyString, "XML files (*.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
			if( fileDialog.ShowModal() != wxID_OK )
				break;

			puzzleFile = fileDialog.GetPath();
		}

		wxBusyCursor busyCursor;

		wxXmlDocument xmlDocument;
		if( !xmlDocument.Load( puzzleFile ) )
			break;

		wxXmlNode* xmlRootNode = xmlDocument.GetRoot();
		if( xmlRootNode->GetName() != "Puzzle" )
			break;

		wxString levelString = xmlRootNode->GetAttribute( "level" );
		if( levelString.IsEmpty() )
			break;

		long levelLong = 0;
		if( !levelString.ToLong( &levelLong ) )
			break;

		level = ( int )levelLong;

		wxXmlNode* xmlTrianglePoolNode = xmlRootNode->GetChildren();
		while( xmlTrianglePoolNode && xmlTrianglePoolNode->GetName() != "TrianglePool" )
			xmlTrianglePoolNode = xmlTrianglePoolNode->GetNext();

		if( !xmlTrianglePoolNode )
			break;

		delete rectangle;
		rectangle = nullptr;

		DeleteTriangleList( *triangleList );

		wxXmlNode* xmlTriangleNode = xmlTrianglePoolNode->GetChildren();
		while( xmlTriangleNode )
		{
			Triangle* triangle = new Triangle();
			triangleList->push_back( triangle );

			if( !triangle->LoadFromXml( xmlTriangleNode ) )
				break;

			xmlTriangleNode = xmlTriangleNode->GetNext();
		}

		if( xmlTriangleNode )
			break;

		if( !texture )
			texture = new Texture();

		texture->Unload();
		
		wxString texFile = xmlRootNode->GetAttribute( "texture" );
		if( texFile.IsEmpty() || !texture->Load( texFile ) )
		{
			wxArrayString texFileArray;
			GetTextureFileArray( texFileArray );

			if( !texture->Load( texFileArray ) )
				break;
		}

		if( !CreateShapes() )
			break;

		wxXmlNode* xmlPermNode = xmlRootNode->GetChildren();
		while( xmlPermNode && xmlPermNode->GetName() != "Permutation" )
			xmlPermNode = xmlPermNode->GetNext();

		if( xmlPermNode )
		{
			wxXmlNode* xmlDataNode = xmlPermNode->GetChildren();
			if( !xmlDataNode || xmlDataNode->GetType() != wxXML_CDATA_SECTION_NODE )
				break;

			wxString jsonString = xmlDataNode->GetContent();

			rapidjson::Document doc;
			doc.Parse( jsonString.c_str() );
			if( !doc.IsObject() )
				break;

			if( !doc.HasMember( "data" ) )
				break;

			rapidjson::Value permutationValue;
			permutationValue = doc[ "data" ];

			if( !permutation.SetFromJsonValue( permutationValue ) )
				break;
		}

		success = true;
	}
	while( false );

	if( !success )
	{
		DeleteTriangleList( *triangleList );
		DeleteShapeList( shapeList );
	}

	return success;
}

void Puzzle::GetTextureFileArray( wxArrayString& texFileArray )
{
	wxString texName = wxString::Format( "Texture%d.jpg", ( level % MAX_IMAGES ) );

	if( level == MAX_LEVELS )
		texName = "Winner.jpg";
	
	texFileArray.Add( "Textures/" + texName );
	texFileArray.Add( wxString( wxGetenv( "SNAP" ) ) + wxString( "/share/SymmetryGroupMadness/Textures/" ) + texName );
	texFileArray.Add( wxString( "/usr/share/SymmetryGroupMadness/Textures/" ) + texName );
}

bool Puzzle::SetupLevel( int level )
{
	this->level = level;

	ResetTriangles();

	if( !texture )
		texture = new Texture();

	texture->Unload();
	
	wxArrayString texFileArray;
	GetTextureFileArray( texFileArray );

	if( !texture->Load( texFileArray ) )
		return false;

	RecalculateAllUVs();

	if( !CreateShapes() )
		return false;

	wxGetApp().GetFrame()->GetStatusBar()->SetLabelText( "Left-click and drag to rotate.  Right-click and drag to reflect." );

	if( level < 3 )
		EnqueueScrambles( 2, 4321 );
	else
		EnqueueScrambles( 10, 0 );

	return true;
}

// Note that we do nothing here to insure that the scramble actually scrambles the puzzle.
// It would be unlikely that the scramble would only temporarily scramble the puzzle and then have it wind up in the solved state.
void Puzzle::EnqueueScrambles( int scrambleCount, int scrambleSeed )
{
	if( scrambleSeed == 0 )
		scrambleSeed = ( int )time( nullptr );

	srand( scrambleSeed );

	autoRotationQueue.clear();

	Random* random = wxGetApp().GetRandom();

	ShapeList::iterator shapeIter = shapeList.begin();
	if( shapeIter == shapeList.end() )
		return;

	for( int i = 0; i < scrambleCount; i++ )
	{
		AutoRotation autoRotation;
		autoRotation.animationAngle = 0.0;
		autoRotation.shape = *shapeIter;

		shapeIter++;
		if( shapeIter == shapeList.end() )
			shapeIter = shapeList.begin();

		if( ( shapeList.size() != 2 && ( i % 2 == 0 ) ) || ( i % 4 > 2 ) )
		{
			int cyclicSubgroupOrder = int( 2.0 * M_PI / autoRotation.shape->GetRotationDelta() );
			autoRotation.rotationAxis.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 1.0 );
			int rotationCount = random->Integer( 1, cyclicSubgroupOrder - 1 );
			autoRotation.rotationAngle = double( rotationCount ) * autoRotation.shape->GetRotationDelta();
			autoRotation.reflection = false;
		}
		else
		{
			int j = random->Integer( 0, autoRotation.shape->GetReflectionAxisArray().size() - 1 );
			autoRotation.rotationAxis = autoRotation.shape->GetReflectionAxisArray()[j];
			autoRotation.rotationAngle = M_PI;
			autoRotation.reflection = true;
		}		
		
		autoRotationQueue.push_back( autoRotation );
	}

	wxGetApp().GetFrame()->timer.Start(1);
}

bool Puzzle::EnqueueSolution( void )
{
	wxBusyCursor busyCursor;

	wxString stabChainFile = wxString::Format( "SymGrpMadPuzzle%d.txt", level );
	
	wxString stabChainFilePath = "StabChains/" + stabChainFile;
	if( !wxFileExists( stabChainFilePath ) )
	{
		stabChainFilePath = wxString( wxGetenv( "SNAP" ) ) + "/share/SymmetryGroupMadness/StabChains/" + stabChainFile;
		if( !wxFileExists( stabChainFile ) )
			return false;
	}

	wxFile file( stabChainFilePath );
	wxString jsonString;
	if( !file.ReadAll( &jsonString ) )
		return false;

	wxScopedPtr< StabilizerChain > stabChain( new StabilizerChain() );
	if( !stabChain->LoadFromJsonString( ( const char* )jsonString.c_str() ) )
		return false;

	CompressInfo compressInfo;
	if( !stabChain->group->MakeCompressInfo( compressInfo ) )
		return false;

	PermutationSet trembleSet;
	for( PermutationSet::iterator iter = stabChain->group->generatorSet.begin(); iter != stabChain->group->generatorSet.end(); iter++ )
		trembleSet.insert( *iter );

	Permutation invPermutation;
	invPermutation.word = new ElementList;
	if( !stabChain->group->FactorInverseWithTrembling( permutation, invPermutation, trembleSet, compressInfo ) )
		return false;

	if( !invPermutation.CompressWord( compressInfo ) )
		return false;

	// Sanity check: Did we actually find the inverse?
	Permutation product;
	product.Multiply( permutation, invPermutation );
	if( !product.IsIdentity() )
		return false;

	autoRotationQueue.clear();

	for( ElementList::const_iterator iter = invPermutation.word->cbegin(); iter != invPermutation.word->cend(); iter++ )
	{
		const Element& element = *iter;
		
		AutoRotation autoRotation;
		autoRotation.animationAngle = 0.0;

		PermutationMap::iterator permIter = compressInfo.permutationMap.find( element.name );
		if( permIter == compressInfo.permutationMap.end() )
			return false;

		bool foundAutoRotation = false;

		for( ShapeList::iterator shapeIter = shapeList.begin(); shapeIter != shapeList.end() && !foundAutoRotation; shapeIter++ )
		{
			Shape* shape = *shapeIter;

			if( shape->ccwRotationPermutation.IsEqualTo( permIter->second ) )
			{
				autoRotation.shape = shape;
				autoRotation.rotationAxis.set( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 1.0 );
				autoRotation.rotationAngle = shape->GetRotationDelta();
				autoRotation.reflection = false;
				foundAutoRotation = true;
			}
			else
			{
				for( int i = 0; i < ( int )shape->reflectionPermutationArray.size(); i++ )
				{
					if( shape->reflectionPermutationArray[i].IsEqualTo( permIter->second ) )
					{
						autoRotation.shape = shape;
						autoRotation.rotationAxis = shape->GetReflectionAxisArray()[i];
						autoRotation.rotationAngle = M_PI;
						autoRotation.reflection = true;
						foundAutoRotation = true;
						break;
					}
				}
			}
		}

		if( !foundAutoRotation )
			return false;

		if( element.exponent < 0 )
			autoRotation.rotationAngle *= -1.0;
		
		double rotationDelta = autoRotation.rotationAngle;
		for( int i = 0; i < abs( element.exponent ) - 1; i++ )
			autoRotation.rotationAngle += rotationDelta;

		autoRotationQueue.push_back( autoRotation );
	}

	return true;
}

// This routine is not used in the final program, but is used along the way to generate code for the final program.
wxString Puzzle::CalculateAndPrintGenerators( bool forStabChainGeneration ) const
{
	VectorArray allPointsArray;

	// TODO: What's a good base for the stabilizer chain?  See paper by Puschel again?
	//       We don't need to compute a base here.  We want to compute the generators
	//       in such a way that {0,1,2,3,...} is the desired/best base.

	// The point array should be populated with one member from each equivilance class of the domain of the permutation group.
	// Two points in the domain are equivilant if there exists an element of the group taking one point to the other.
	for( uint i = 0; i < pointArray.size(); i++ )
	{
		VectorArray orbitArray;
		CalculatePointOrbit( pointArray[i], orbitArray );

		for( uint j = 0; j < orbitArray.size(); j++ )
			allPointsArray.push_back( orbitArray[j] );
	}

	wxString code;
	int count = 0;

	for( ShapeList::const_iterator iter = shapeList.cbegin(); iter != shapeList.cend(); iter++ )
	{
		const Shape* shape = *iter;

		for( int i = -1; i < ( signed )shape->GetReflectionAxisArray().size(); i++ )
		{
			wxString permName;
			if( i < 0 )
				permName = wxString::Format( "R_%d", count );
			else
				permName = wxString::Format( "F%d_%d", i, count );

			code += "Permutation " + permName + ";\n";

			for( int j = 0; j < allPointsArray.size(); j++ )
			{
				c3ga::vectorE3GA point, otherPoint;
				point = allPointsArray[j];
				if( !shape->TransformPoint( point, otherPoint, i ) )
					continue;

				int k = FindArrayOffset( allPointsArray, otherPoint );
				wxASSERT( k >= 0 );

				if( j != k )
					code += permName + wxString::Format( ".Define( %d, %d );\n", j, k );
			}

			if( forStabChainGeneration )
				code += "generatorSet.insert( " + permName + " );\n";
			else
			{
				if( i < 0 )
					code += wxString::Format( "shape%d->ccwRotationPermutation = R_%d;\n", count, count );
				else
					code += wxString::Format( "shape%d->reflectionPermutationArray.push_back( F%d_%d );\n", count, i, count );
			}

			code += "\n";
		}

		count++;
	}

	return code;
}

void Puzzle::CalculatePointOrbit( const c3ga::vectorE3GA& givenPoint, VectorArray& orbitArray ) const
{
	orbitArray.clear();

	VectorArray pointQueue;
	pointQueue.push_back( givenPoint );

	while( pointQueue.size() > 0 )
	{
		c3ga::vectorE3GA point = pointQueue.back();
		pointQueue.pop_back();

		orbitArray.push_back( point );

		for( ShapeList::const_iterator iter = shapeList.cbegin(); iter != shapeList.cend(); iter++ )
		{
			const Shape* shape = *iter;
			if( !shape->ContainsPoint( point ) )
				continue;

			for( int i = -1; i < ( signed )shape->GetReflectionAxisArray().size(); i++ )
			{
				c3ga::vectorE3GA otherPoint;
				shape->TransformPoint( point, otherPoint, i );

				if( !( ArrayContains( orbitArray, otherPoint ) || ArrayContains( pointQueue, otherPoint ) ) )
					pointQueue.push_back( otherPoint );
			}
		}
	}
}

// Puzzle.cpp