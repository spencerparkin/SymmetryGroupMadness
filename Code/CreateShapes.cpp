// CreateShapes.cpp

#include "Application.h"
#include "Frame.h"
#include "Puzzle.h"
#include "Shape.h"
#include <wx/msgdlg.h>

bool Puzzle::CreateShapes( void )
{
	DeleteShapeList( shapeList );

	permutation.DefineIdentity();

	switch( level )
	{
		case 1:
		{
			// Level 1 is just the dihedral group D_3.
			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, -2.0, 0.0 ), 8.0, 3, -M_PI / 6.0 );
			shapeList.push_back( shape );

			return true;
		}
		case 2:
		{
			// Level 2 is just the dihedral group D_4.
			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 ), 8.0, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

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

			return true;
		}
		case 5:
		{
			double r = 6.0;
			double a = r / sqrt( 2.0 );
			Permutation permutation;

			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, a - a / 3.0, a / 3.0, 0.0 ), r, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			// R0
			permutation.DefineIdentity();
			permutation.DefineCycle( 0, 46, 51, 5 );
			permutation.DefineCycle( 1, 36, 50, 11 );
			permutation.DefineCycle( 2, 26, 49, 21 );
			permutation.DefineCycle( 3, 16, 48, 31 );
			permutation.DefineCycle( 4, 6, 47, 41 );
			permutation.DefineCycle( 7, 37, 40, 10 );
			permutation.DefineCycle( 8, 27, 39, 20 );
			permutation.DefineCycle( 9, 17, 38, 30 );
			permutation.DefineCycle( 18, 28, 29, 19 );
			shape->ccwRotationPermutation = permutation;

			// D0'
			permutation.DefineIdentity();
			permutation.DefineCycle( 4, 11 );
			permutation.DefineCycle( 3, 21 );
			permutation.DefineCycle( 2, 31 );
			permutation.DefineCycle( 9, 20 );
			permutation.DefineCycle( 1, 41 );
			permutation.DefineCycle( 0, 51 );
			permutation.DefineCycle( 7, 40 );
			permutation.DefineCycle( 18, 29 );
			permutation.DefineCycle( 6, 50 );
			permutation.DefineCycle( 16, 49 );
			permutation.DefineCycle( 27, 38 );
			permutation.DefineCycle( 26, 48 );
			permutation.DefineCycle( 36, 47 );
			permutation.DefineCycle( 17, 39 );
			permutation.DefineCycle( 8, 30 );
			shape->reflectionPermutationArray.push_back( permutation );

			// V0
			permutation.DefineIdentity();
			permutation.DefineCycle( 0, 5 );
			permutation.DefineCycle( 1, 4 );
			permutation.DefineCycle( 2, 3 );
			permutation.DefineCycle( 6, 11 );
			permutation.DefineCycle( 7, 10 );
			permutation.DefineCycle( 8, 9 );
			permutation.DefineCycle( 16, 21 );
			permutation.DefineCycle( 17, 20 );
			permutation.DefineCycle( 18, 19 );
			permutation.DefineCycle( 26, 31 );
			permutation.DefineCycle( 27, 30 );
			permutation.DefineCycle( 28, 29 );
			permutation.DefineCycle( 36, 41 );
			permutation.DefineCycle( 37, 40 );
			permutation.DefineCycle( 38, 39 );
			permutation.DefineCycle( 46, 51 );
			permutation.DefineCycle( 47, 50 );
			permutation.DefineCycle( 48, 49 );
			shape->reflectionPermutationArray.push_back( permutation );

			// D0
			permutation.DefineIdentity();
			permutation.DefineCycle( 1, 6 );
			permutation.DefineCycle( 2, 16 );
			permutation.DefineCycle( 3, 26 );
			permutation.DefineCycle( 8, 17 );
			permutation.DefineCycle( 5, 46 );
			permutation.DefineCycle( 10, 37 );
			permutation.DefineCycle( 19, 28 );
			permutation.DefineCycle( 11, 47 );
			permutation.DefineCycle( 21, 48 );
			permutation.DefineCycle( 30, 39 );
			permutation.DefineCycle( 31, 49 );
			permutation.DefineCycle( 41, 50 );
			permutation.DefineCycle( 20, 38 );
			permutation.DefineCycle( 4, 36 );
			permutation.DefineCycle( 9, 27 );
			shape->reflectionPermutationArray.push_back( permutation );

			// H0
			permutation.DefineIdentity();
			permutation.DefineCycle( 0, 46 );
			permutation.DefineCycle( 6, 36 );
			permutation.DefineCycle( 16, 26 );
			permutation.DefineCycle( 1, 47 );
			permutation.DefineCycle( 7, 37 );
			permutation.DefineCycle( 17, 27 );
			permutation.DefineCycle( 2, 48 );
			permutation.DefineCycle( 8, 38 );
			permutation.DefineCycle( 18, 28 );
			permutation.DefineCycle( 3, 49 );
			permutation.DefineCycle( 9, 39 );
			permutation.DefineCycle( 19, 29 );
			permutation.DefineCycle( 4, 50 );
			permutation.DefineCycle( 10, 40 );
			permutation.DefineCycle( 20, 30 );
			permutation.DefineCycle( 5, 51 );
			permutation.DefineCycle( 11, 41 );
			permutation.DefineCycle( 21, 31 );
			shape->reflectionPermutationArray.push_back( permutation );

			shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, -a + a / 3.0, -a / 3.0, 0.0 ), r, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			// R1
			permutation.DefineIdentity();
			permutation.DefineCycle( 12, 58, 63, 17 );
			permutation.DefineCycle( 13, 52, 62, 27 );
			permutation.DefineCycle( 14, 42, 61, 37 );
			permutation.DefineCycle( 15, 32, 60, 47 );
			permutation.DefineCycle( 16, 22, 59, 57 );
			permutation.DefineCycle( 23, 53, 56, 26 );
			permutation.DefineCycle( 24, 43, 55, 36 );
			permutation.DefineCycle( 25, 33, 54, 46 );
			permutation.DefineCycle( 34, 44, 45, 35 );
			shape->ccwRotationPermutation = permutation;

			// D1'
			permutation.DefineIdentity();
			permutation.DefineCycle( 16, 17 );
			permutation.DefineCycle( 15, 37 );
			permutation.DefineCycle( 14, 47 );
			permutation.DefineCycle( 25, 36 );
			permutation.DefineCycle( 13, 57 );
			permutation.DefineCycle( 24, 46 );
			permutation.DefineCycle( 12, 63 );
			permutation.DefineCycle( 23, 56 );
			permutation.DefineCycle( 34, 45 );
			permutation.DefineCycle( 33, 55 );
			permutation.DefineCycle( 22, 62 );
			permutation.DefineCycle( 32, 61 );
			permutation.DefineCycle( 43, 54 );
			permutation.DefineCycle( 42, 60 );
			permutation.DefineCycle( 52, 59 );
			shape->reflectionPermutationArray.push_back( permutation );

			permutation.DefineIdentity();
			permutation.DefineCycle( 12, 17 );
			permutation.DefineCycle( 13, 16 );
			permutation.DefineCycle( 14, 15 );
			permutation.DefineCycle( 22, 27 );
			permutation.DefineCycle( 23, 26 );
			permutation.DefineCycle( 24, 25 );
			permutation.DefineCycle( 32, 37 );
			permutation.DefineCycle( 33, 36 );
			permutation.DefineCycle( 34, 35 );
			permutation.DefineCycle( 42, 47 );
			permutation.DefineCycle( 43, 46 );
			permutation.DefineCycle( 44, 45 );
			permutation.DefineCycle( 52, 57 );
			permutation.DefineCycle( 53, 56 );
			permutation.DefineCycle( 54, 55 );
			permutation.DefineCycle( 58, 63 );
			permutation.DefineCycle( 59, 62 );
			permutation.DefineCycle( 60, 61 );
			shape->reflectionPermutationArray.push_back( permutation );

			// D1
			permutation.DefineIdentity();
			permutation.DefineCycle( 13, 22 );
			permutation.DefineCycle( 14, 32 );
			permutation.DefineCycle( 15, 42 );
			permutation.DefineCycle( 24, 33 );
			permutation.DefineCycle( 16, 52 );
			permutation.DefineCycle( 17, 58 );
			permutation.DefineCycle( 26, 53 );
			permutation.DefineCycle( 35, 44 );
			permutation.DefineCycle( 27, 59 );
			permutation.DefineCycle( 36, 54 );
			permutation.DefineCycle( 37, 60 );
			permutation.DefineCycle( 46, 55 );
			permutation.DefineCycle( 47, 61 );
			permutation.DefineCycle( 57, 62 );
			permutation.DefineCycle( 25, 43 );
			shape->reflectionPermutationArray.push_back( permutation );

			// H1
			permutation.DefineIdentity();
			permutation.DefineCycle( 12, 58 );
			permutation.DefineCycle( 22, 52 );
			permutation.DefineCycle( 32, 42 );
			permutation.DefineCycle( 13, 59 );
			permutation.DefineCycle( 23, 53 );
			permutation.DefineCycle( 33, 43 );
			permutation.DefineCycle( 14, 60 );
			permutation.DefineCycle( 24, 54 );
			permutation.DefineCycle( 34, 44 );
			permutation.DefineCycle( 15, 61 );
			permutation.DefineCycle( 25, 55 );
			permutation.DefineCycle( 35, 45 );
			permutation.DefineCycle( 16, 62 );
			permutation.DefineCycle( 26, 56 );
			permutation.DefineCycle( 36, 46 );
			permutation.DefineCycle( 17, 63 );
			permutation.DefineCycle( 27, 57 );
			permutation.DefineCycle( 37, 47 );
			shape->reflectionPermutationArray.push_back( permutation );

			return true;
		}
		case 6:
		{
			Shape* shape = nullptr;

			shape = new Shape();
			shape->MakeRectangle( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, -5.0, 0.0 ), 12.0, 2.0, 0.0 );
			shapeList.push_back( shape );

			shape = new Shape();
			shape->MakeRectangle( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 5.0, 0.0 ), 12.0, 2.0, 0.0 );
			shapeList.push_back( shape );

			shape = new Shape();
			shape->MakeRectangle( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, -5.0, 0.0, 0.0 ), 12.0, 2.0, M_PI / 2.0 );
			shapeList.push_back( shape );

			shape = new Shape();
			shape->MakeRectangle( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 5.0, 0.0, 0.0 ), 12.0, 2.0, M_PI / 2.0 );
			shapeList.push_back( shape );

			return true;
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

// CreateShapes.cpp