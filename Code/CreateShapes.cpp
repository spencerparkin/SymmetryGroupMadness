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
			Permutation shapePermutation;

			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, a / 2.0, a / 2.0, 0.0 ), 6.0, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			// R0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 16, 19, 3 );
			shapePermutation.DefineCycle( 1, 10, 18, 7 );
			shapePermutation.DefineCycle( 2, 4, 17, 13 );
			shapePermutation.DefineCycle( 5, 11, 12, 6 );
			shape->ccwRotationPermutation = shapePermutation;

			// D0'
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 2, 7 );
			shapePermutation.DefineCycle( 1, 13 );
			shapePermutation.DefineCycle( 0, 19 );
			shapePermutation.DefineCycle( 5, 12 );
			shapePermutation.DefineCycle( 4, 18 );
			shapePermutation.DefineCycle( 10, 17 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// V0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 3 );
			shapePermutation.DefineCycle( 1, 2 );
			shapePermutation.DefineCycle( 4, 7 );
			shapePermutation.DefineCycle( 5, 6 );
			shapePermutation.DefineCycle( 10, 13 );
			shapePermutation.DefineCycle( 11, 12 );
			shapePermutation.DefineCycle( 16, 19 );
			shapePermutation.DefineCycle( 17, 18 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// D0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 1, 4 );
			shapePermutation.DefineCycle( 2, 10 );
			shapePermutation.DefineCycle( 3, 16 );
			shapePermutation.DefineCycle( 6, 11 );
			shapePermutation.DefineCycle( 7, 17 );
			shapePermutation.DefineCycle( 13, 18 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// H0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 16 );
			shapePermutation.DefineCycle( 4, 10 );
			shapePermutation.DefineCycle( 1, 17 );
			shapePermutation.DefineCycle( 5, 11 );
			shapePermutation.DefineCycle( 2, 18 );
			shapePermutation.DefineCycle( 6, 12 );
			shapePermutation.DefineCycle( 3, 19 );
			shapePermutation.DefineCycle( 7, 13 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, -a / 2.0, -a / 2.0, 0.0 ), 6.0, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			// R1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 8, 24, 27, 11 );
			shapePermutation.DefineCycle( 9, 20, 26, 17 );
			shapePermutation.DefineCycle( 10, 14, 25, 23 );
			shapePermutation.DefineCycle( 15, 21, 22, 16 );
			shape->ccwRotationPermutation = shapePermutation;

			// D1'
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 10, 17 );
			shapePermutation.DefineCycle( 9, 23 );
			shapePermutation.DefineCycle( 8, 27 );
			shapePermutation.DefineCycle( 15, 22 );
			shapePermutation.DefineCycle( 14, 26 );
			shapePermutation.DefineCycle( 20, 25 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// V1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 8, 11 );
			shapePermutation.DefineCycle( 9, 10 );
			shapePermutation.DefineCycle( 14, 17 );
			shapePermutation.DefineCycle( 15, 16 );
			shapePermutation.DefineCycle( 20, 23 );
			shapePermutation.DefineCycle( 21, 22 );
			shapePermutation.DefineCycle( 24, 27 );
			shapePermutation.DefineCycle( 25, 26 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// D1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 9, 14 );
			shapePermutation.DefineCycle( 10, 20 );
			shapePermutation.DefineCycle( 11, 24 );
			shapePermutation.DefineCycle( 16, 21 );
			shapePermutation.DefineCycle( 17, 25 );
			shapePermutation.DefineCycle( 23, 26 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// H1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 8, 24 );
			shapePermutation.DefineCycle( 14, 20 );
			shapePermutation.DefineCycle( 9, 25 );
			shapePermutation.DefineCycle( 15, 21 );
			shapePermutation.DefineCycle( 10, 26 );
			shapePermutation.DefineCycle( 16, 22 );
			shapePermutation.DefineCycle( 11, 27 );
			shapePermutation.DefineCycle( 17, 23 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			return true;
		}
		case 5:
		{
			double r = 6.0;
			double a = r / sqrt( 2.0 );
			Permutation shapePermutation;

			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, a - a / 3.0, a / 3.0, 0.0 ), r, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			// R0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 46, 51, 5 );
			shapePermutation.DefineCycle( 1, 36, 50, 11 );
			shapePermutation.DefineCycle( 2, 26, 49, 21 );
			shapePermutation.DefineCycle( 3, 16, 48, 31 );
			shapePermutation.DefineCycle( 4, 6, 47, 41 );
			shapePermutation.DefineCycle( 7, 37, 40, 10 );
			shapePermutation.DefineCycle( 8, 27, 39, 20 );
			shapePermutation.DefineCycle( 9, 17, 38, 30 );
			shapePermutation.DefineCycle( 18, 28, 29, 19 );
			shape->ccwRotationPermutation = shapePermutation;

			// D0'
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 4, 11 );
			shapePermutation.DefineCycle( 3, 21 );
			shapePermutation.DefineCycle( 2, 31 );
			shapePermutation.DefineCycle( 9, 20 );
			shapePermutation.DefineCycle( 1, 41 );
			shapePermutation.DefineCycle( 0, 51 );
			shapePermutation.DefineCycle( 7, 40 );
			shapePermutation.DefineCycle( 18, 29 );
			shapePermutation.DefineCycle( 6, 50 );
			shapePermutation.DefineCycle( 16, 49 );
			shapePermutation.DefineCycle( 27, 38 );
			shapePermutation.DefineCycle( 26, 48 );
			shapePermutation.DefineCycle( 36, 47 );
			shapePermutation.DefineCycle( 17, 39 );
			shapePermutation.DefineCycle( 8, 30 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// V0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 5 );
			shapePermutation.DefineCycle( 1, 4 );
			shapePermutation.DefineCycle( 2, 3 );
			shapePermutation.DefineCycle( 6, 11 );
			shapePermutation.DefineCycle( 7, 10 );
			shapePermutation.DefineCycle( 8, 9 );
			shapePermutation.DefineCycle( 16, 21 );
			shapePermutation.DefineCycle( 17, 20 );
			shapePermutation.DefineCycle( 18, 19 );
			shapePermutation.DefineCycle( 26, 31 );
			shapePermutation.DefineCycle( 27, 30 );
			shapePermutation.DefineCycle( 28, 29 );
			shapePermutation.DefineCycle( 36, 41 );
			shapePermutation.DefineCycle( 37, 40 );
			shapePermutation.DefineCycle( 38, 39 );
			shapePermutation.DefineCycle( 46, 51 );
			shapePermutation.DefineCycle( 47, 50 );
			shapePermutation.DefineCycle( 48, 49 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// D0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 1, 6 );
			shapePermutation.DefineCycle( 2, 16 );
			shapePermutation.DefineCycle( 3, 26 );
			shapePermutation.DefineCycle( 8, 17 );
			shapePermutation.DefineCycle( 5, 46 );
			shapePermutation.DefineCycle( 10, 37 );
			shapePermutation.DefineCycle( 19, 28 );
			shapePermutation.DefineCycle( 11, 47 );
			shapePermutation.DefineCycle( 21, 48 );
			shapePermutation.DefineCycle( 30, 39 );
			shapePermutation.DefineCycle( 31, 49 );
			shapePermutation.DefineCycle( 41, 50 );
			shapePermutation.DefineCycle( 20, 38 );
			shapePermutation.DefineCycle( 4, 36 );
			shapePermutation.DefineCycle( 9, 27 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// H0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 46 );
			shapePermutation.DefineCycle( 6, 36 );
			shapePermutation.DefineCycle( 16, 26 );
			shapePermutation.DefineCycle( 1, 47 );
			shapePermutation.DefineCycle( 7, 37 );
			shapePermutation.DefineCycle( 17, 27 );
			shapePermutation.DefineCycle( 2, 48 );
			shapePermutation.DefineCycle( 8, 38 );
			shapePermutation.DefineCycle( 18, 28 );
			shapePermutation.DefineCycle( 3, 49 );
			shapePermutation.DefineCycle( 9, 39 );
			shapePermutation.DefineCycle( 19, 29 );
			shapePermutation.DefineCycle( 4, 50 );
			shapePermutation.DefineCycle( 10, 40 );
			shapePermutation.DefineCycle( 20, 30 );
			shapePermutation.DefineCycle( 5, 51 );
			shapePermutation.DefineCycle( 11, 41 );
			shapePermutation.DefineCycle( 21, 31 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, -a + a / 3.0, -a / 3.0, 0.0 ), r, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			// R1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 12, 58, 63, 17 );
			shapePermutation.DefineCycle( 13, 52, 62, 27 );
			shapePermutation.DefineCycle( 14, 42, 61, 37 );
			shapePermutation.DefineCycle( 15, 32, 60, 47 );
			shapePermutation.DefineCycle( 16, 22, 59, 57 );
			shapePermutation.DefineCycle( 23, 53, 56, 26 );
			shapePermutation.DefineCycle( 24, 43, 55, 36 );
			shapePermutation.DefineCycle( 25, 33, 54, 46 );
			shapePermutation.DefineCycle( 34, 44, 45, 35 );
			shape->ccwRotationPermutation = shapePermutation;

			// D1'
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 16, 17 );
			shapePermutation.DefineCycle( 15, 37 );
			shapePermutation.DefineCycle( 14, 47 );
			shapePermutation.DefineCycle( 25, 36 );
			shapePermutation.DefineCycle( 13, 57 );
			shapePermutation.DefineCycle( 24, 46 );
			shapePermutation.DefineCycle( 12, 63 );
			shapePermutation.DefineCycle( 23, 56 );
			shapePermutation.DefineCycle( 34, 45 );
			shapePermutation.DefineCycle( 33, 55 );
			shapePermutation.DefineCycle( 22, 62 );
			shapePermutation.DefineCycle( 32, 61 );
			shapePermutation.DefineCycle( 43, 54 );
			shapePermutation.DefineCycle( 42, 60 );
			shapePermutation.DefineCycle( 52, 59 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 12, 17 );
			shapePermutation.DefineCycle( 13, 16 );
			shapePermutation.DefineCycle( 14, 15 );
			shapePermutation.DefineCycle( 22, 27 );
			shapePermutation.DefineCycle( 23, 26 );
			shapePermutation.DefineCycle( 24, 25 );
			shapePermutation.DefineCycle( 32, 37 );
			shapePermutation.DefineCycle( 33, 36 );
			shapePermutation.DefineCycle( 34, 35 );
			shapePermutation.DefineCycle( 42, 47 );
			shapePermutation.DefineCycle( 43, 46 );
			shapePermutation.DefineCycle( 44, 45 );
			shapePermutation.DefineCycle( 52, 57 );
			shapePermutation.DefineCycle( 53, 56 );
			shapePermutation.DefineCycle( 54, 55 );
			shapePermutation.DefineCycle( 58, 63 );
			shapePermutation.DefineCycle( 59, 62 );
			shapePermutation.DefineCycle( 60, 61 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// D1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 13, 22 );
			shapePermutation.DefineCycle( 14, 32 );
			shapePermutation.DefineCycle( 15, 42 );
			shapePermutation.DefineCycle( 24, 33 );
			shapePermutation.DefineCycle( 16, 52 );
			shapePermutation.DefineCycle( 17, 58 );
			shapePermutation.DefineCycle( 26, 53 );
			shapePermutation.DefineCycle( 35, 44 );
			shapePermutation.DefineCycle( 27, 59 );
			shapePermutation.DefineCycle( 36, 54 );
			shapePermutation.DefineCycle( 37, 60 );
			shapePermutation.DefineCycle( 46, 55 );
			shapePermutation.DefineCycle( 47, 61 );
			shapePermutation.DefineCycle( 57, 62 );
			shapePermutation.DefineCycle( 25, 43 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// H1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 12, 58 );
			shapePermutation.DefineCycle( 22, 52 );
			shapePermutation.DefineCycle( 32, 42 );
			shapePermutation.DefineCycle( 13, 59 );
			shapePermutation.DefineCycle( 23, 53 );
			shapePermutation.DefineCycle( 33, 43 );
			shapePermutation.DefineCycle( 14, 60 );
			shapePermutation.DefineCycle( 24, 54 );
			shapePermutation.DefineCycle( 34, 44 );
			shapePermutation.DefineCycle( 15, 61 );
			shapePermutation.DefineCycle( 25, 55 );
			shapePermutation.DefineCycle( 35, 45 );
			shapePermutation.DefineCycle( 16, 62 );
			shapePermutation.DefineCycle( 26, 56 );
			shapePermutation.DefineCycle( 36, 46 );
			shapePermutation.DefineCycle( 17, 63 );
			shapePermutation.DefineCycle( 27, 57 );
			shapePermutation.DefineCycle( 37, 47 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

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