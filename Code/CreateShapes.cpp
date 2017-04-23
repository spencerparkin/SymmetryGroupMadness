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

			Permutation permR0;
			permR0.Define( 0, 46 );
			permR0.Define( 1, 36 );
			permR0.Define( 2, 26 );
			permR0.Define( 3, 16 );
			permR0.Define( 4, 6 );
			permR0.Define( 5, 0 );
			permR0.Define( 6, 47 );
			permR0.Define( 7, 37 );
			permR0.Define( 8, 27 );
			permR0.Define( 9, 17 );
			permR0.Define( 10, 7 );
			permR0.Define( 11, 1 );
			permR0.Define( 16, 48 );
			permR0.Define( 17, 38 );
			permR0.Define( 18, 28 );
			permR0.Define( 19, 18 );
			permR0.Define( 20, 8 );
			permR0.Define( 21, 2 );
			permR0.Define( 26, 49 );
			permR0.Define( 27, 39 );
			permR0.Define( 28, 29 );
			permR0.Define( 29, 19 );
			permR0.Define( 30, 9 );
			permR0.Define( 31, 3 );
			permR0.Define( 36, 50 );
			permR0.Define( 37, 40 );
			permR0.Define( 38, 30 );
			permR0.Define( 39, 20 );
			permR0.Define( 40, 10 );
			permR0.Define( 41, 4 );
			permR0.Define( 46, 51 );
			permR0.Define( 47, 41 );
			permR0.Define( 48, 31 );
			permR0.Define( 49, 21 );
			permR0.Define( 50, 11 );
			permR0.Define( 51, 5 );

			Permutation permD0p;
			permD0p.Define( 0, 51 );
			permD0p.Define( 1, 41 );
			permD0p.Define( 2, 31 );
			permD0p.Define( 3, 21 );
			permD0p.Define( 4, 11 );
			permD0p.Define( 6, 50 );
			permD0p.Define( 7, 40 );
			permD0p.Define( 8, 30 );
			permD0p.Define( 9, 20 );
			permD0p.Define( 11, 4 );
			permD0p.Define( 16, 49 );
			permD0p.Define( 17, 39 );
			permD0p.Define( 18, 29 );
			permD0p.Define( 20, 9 );
			permD0p.Define( 21, 3 );
			permD0p.Define( 26, 48 );
			permD0p.Define( 27, 38 );
			permD0p.Define( 29, 18 );
			permD0p.Define( 30, 8 );
			permD0p.Define( 31, 2 );
			permD0p.Define( 36, 47 );
			permD0p.Define( 38, 27 );
			permD0p.Define( 39, 17 );
			permD0p.Define( 40, 7 );
			permD0p.Define( 41, 1 );
			permD0p.Define( 47, 36 );
			permD0p.Define( 48, 26 );
			permD0p.Define( 49, 16 );
			permD0p.Define( 50, 6 );
			permD0p.Define( 51, 0 );

			Permutation permV0;
			permV0.Define( 0, 5 );
			permV0.Define( 1, 4 );
			permV0.Define( 2, 3 );
			permV0.Define( 3, 2 );
			permV0.Define( 4, 1 );
			permV0.Define( 5, 0 );
			permV0.Define( 6, 11 );
			permV0.Define( 7, 10 );
			permV0.Define( 8, 9 );
			permV0.Define( 9, 8 );
			permV0.Define( 10, 7 );
			permV0.Define( 11, 6 );
			permV0.Define( 16, 21 );
			permV0.Define( 17, 20 );
			permV0.Define( 18, 19 );
			permV0.Define( 19, 18 );
			permV0.Define( 20, 17 );
			permV0.Define( 21, 16 );
			permV0.Define( 26, 31 );
			permV0.Define( 27, 30 );
			permV0.Define( 28, 29 );
			permV0.Define( 29, 28 );
			permV0.Define( 30, 27 );
			permV0.Define( 31, 26 );
			permV0.Define( 36, 41 );
			permV0.Define( 37, 40 );
			permV0.Define( 38, 39 );
			permV0.Define( 39, 38 );
			permV0.Define( 40, 37 );
			permV0.Define( 41, 36 );
			permV0.Define( 46, 51 );
			permV0.Define( 47, 50 );
			permV0.Define( 48, 49 );
			permV0.Define( 49, 48 );
			permV0.Define( 50, 47 );
			permV0.Define( 51, 46 );

			Permutation permD0;
			permD0.Define( 1, 6 );
			permD0.Define( 2, 16 );
			permD0.Define( 3, 26 );
			permD0.Define( 4, 36 );
			permD0.Define( 5, 46 );
			permD0.Define( 6, 1 );
			permD0.Define( 8, 17 );
			permD0.Define( 9, 27 );
			permD0.Define( 10, 37 );
			permD0.Define( 11, 47 );
			permD0.Define( 16, 2 );
			permD0.Define( 17, 8 );
			permD0.Define( 19, 28 );
			permD0.Define( 20, 38 );
			permD0.Define( 21, 48 );
			permD0.Define( 26, 3 );
			permD0.Define( 27, 9 );
			permD0.Define( 28, 19 );
			permD0.Define( 30, 39 );
			permD0.Define( 31, 49 );
			permD0.Define( 36, 4 );
			permD0.Define( 37, 10 );
			permD0.Define( 38, 20 );
			permD0.Define( 39, 30 );
			permD0.Define( 41, 50 );
			permD0.Define( 46, 5 );
			permD0.Define( 47, 11 );
			permD0.Define( 48, 21 );
			permD0.Define( 49, 31 );
			permD0.Define( 50, 41 );

			Permutation permH0;
			permH0.Define( 0, 46 );
			permH0.Define( 1, 47 );
			permH0.Define( 2, 48 );
			permH0.Define( 3, 49 );
			permH0.Define( 4, 50 );
			permH0.Define( 5, 51 );
			permH0.Define( 6, 36 );
			permH0.Define( 7, 37 );
			permH0.Define( 8, 38 );
			permH0.Define( 9, 39 );
			permH0.Define( 10, 40 );
			permH0.Define( 11, 41 );
			permH0.Define( 16, 26 );
			permH0.Define( 17, 27 );
			permH0.Define( 18, 28 );
			permH0.Define( 19, 29 );
			permH0.Define( 20, 30 );
			permH0.Define( 21, 31 );
			permH0.Define( 26, 16 );
			permH0.Define( 27, 17 );
			permH0.Define( 28, 18 );
			permH0.Define( 29, 19 );
			permH0.Define( 30, 20 );
			permH0.Define( 31, 21 );
			permH0.Define( 36, 6 );
			permH0.Define( 37, 7 );
			permH0.Define( 38, 8 );
			permH0.Define( 39, 9 );
			permH0.Define( 40, 10 );
			permH0.Define( 41, 11 );
			permH0.Define( 46, 0 );
			permH0.Define( 47, 1 );
			permH0.Define( 48, 2 );
			permH0.Define( 49, 3 );
			permH0.Define( 50, 4 );
			permH0.Define( 51, 5 );

			shape->ccwRotationPermutation = permR0;
			shape->reflectionPermutationArray.push_back( permD0p );
			shape->reflectionPermutationArray.push_back( permV0 );
			shape->reflectionPermutationArray.push_back( permD0 );
			shape->reflectionPermutationArray.push_back( permH0 );

			shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, -a + a / 3.0, -a / 3.0, 0.0 ), r, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			Permutation permR1;
			permR1.Define( 12, 58 );
			permR1.Define( 13, 52 );
			permR1.Define( 14, 42 );
			permR1.Define( 15, 32 );
			permR1.Define( 16, 22 );
			permR1.Define( 17, 12 );
			permR1.Define( 22, 59 );
			permR1.Define( 23, 53 );
			permR1.Define( 24, 43 );
			permR1.Define( 25, 33 );
			permR1.Define( 26, 23 );
			permR1.Define( 27, 13 );
			permR1.Define( 32, 60 );
			permR1.Define( 33, 54 );
			permR1.Define( 34, 44 );
			permR1.Define( 35, 34 );
			permR1.Define( 36, 24 );
			permR1.Define( 37, 14 );
			permR1.Define( 42, 61 );
			permR1.Define( 43, 55 );
			permR1.Define( 44, 45 );
			permR1.Define( 45, 35 );
			permR1.Define( 46, 25 );
			permR1.Define( 47, 15 );
			permR1.Define( 52, 62 );
			permR1.Define( 53, 56 );
			permR1.Define( 54, 46 );
			permR1.Define( 55, 36 );
			permR1.Define( 56, 26 );
			permR1.Define( 57, 16 );
			permR1.Define( 58, 63 );
			permR1.Define( 59, 57 );
			permR1.Define( 60, 47 );
			permR1.Define( 61, 37 );
			permR1.Define( 62, 27 );
			permR1.Define( 63, 17 );

			Permutation permD1p;
			permD1p.Define( 12, 63 );
			permD1p.Define( 13, 57 );
			permD1p.Define( 14, 47 );
			permD1p.Define( 15, 37 );
			permD1p.Define( 16, 27 );
			permD1p.Define( 22, 62 );
			permD1p.Define( 23, 56 );
			permD1p.Define( 24, 46 );
			permD1p.Define( 25, 36 );
			permD1p.Define( 27, 16 );
			permD1p.Define( 32, 61 );
			permD1p.Define( 33, 55 );
			permD1p.Define( 34, 45 );
			permD1p.Define( 36, 25 );
			permD1p.Define( 37, 15 );
			permD1p.Define( 42, 60 );
			permD1p.Define( 43, 54 );
			permD1p.Define( 45, 34 );
			permD1p.Define( 46, 24 );
			permD1p.Define( 47, 14 );
			permD1p.Define( 52, 59 );
			permD1p.Define( 54, 43 );
			permD1p.Define( 55, 33 );
			permD1p.Define( 56, 23 );
			permD1p.Define( 57, 13 );
			permD1p.Define( 59, 52 );
			permD1p.Define( 60, 42 );
			permD1p.Define( 61, 32 );
			permD1p.Define( 62, 22 );
			permD1p.Define( 63, 12 );

			Permutation permV1;
			permV1.Define( 12, 17 );
			permV1.Define( 13, 16 );
			permV1.Define( 14, 15 );
			permV1.Define( 15, 14 );
			permV1.Define( 16, 13 );
			permV1.Define( 17, 12 );
			permV1.Define( 22, 27 );
			permV1.Define( 23, 26 );
			permV1.Define( 24, 25 );
			permV1.Define( 25, 24 );
			permV1.Define( 26, 23 );
			permV1.Define( 27, 22 );
			permV1.Define( 32, 37 );
			permV1.Define( 33, 36 );
			permV1.Define( 34, 35 );
			permV1.Define( 35, 34 );
			permV1.Define( 36, 33 );
			permV1.Define( 37, 32 );
			permV1.Define( 42, 47 );
			permV1.Define( 43, 46 );
			permV1.Define( 44, 45 );
			permV1.Define( 45, 44 );
			permV1.Define( 46, 43 );
			permV1.Define( 47, 42 );
			permV1.Define( 52, 57 );
			permV1.Define( 53, 56 );
			permV1.Define( 54, 55 );
			permV1.Define( 55, 54 );
			permV1.Define( 56, 53 );
			permV1.Define( 57, 52 );
			permV1.Define( 58, 63 );
			permV1.Define( 59, 62 );
			permV1.Define( 60, 61 );
			permV1.Define( 61, 60 );
			permV1.Define( 62, 59 );
			permV1.Define( 63, 58 );

			Permutation permD1;
			permD1.Define( 13, 22 );
			permD1.Define( 14, 32 );
			permD1.Define( 15, 42 );
			permD1.Define( 16, 52 );
			permD1.Define( 17, 58 );
			permD1.Define( 22, 13 );
			permD1.Define( 24, 33 );
			permD1.Define( 25, 43 );
			permD1.Define( 26, 53 );
			permD1.Define( 27, 59 );
			permD1.Define( 32, 14 );
			permD1.Define( 33, 24 );
			permD1.Define( 35, 44 );
			permD1.Define( 36, 54 );
			permD1.Define( 37, 60 );
			permD1.Define( 42, 15 );
			permD1.Define( 43, 25 );
			permD1.Define( 44, 35 );
			permD1.Define( 46, 55 );
			permD1.Define( 47, 61 );
			permD1.Define( 52, 16 );
			permD1.Define( 53, 26 );
			permD1.Define( 54, 36 );
			permD1.Define( 55, 46 );
			permD1.Define( 57, 62 );
			permD1.Define( 58, 17 );
			permD1.Define( 59, 27 );
			permD1.Define( 60, 37 );
			permD1.Define( 61, 47 );
			permD1.Define( 62, 57 );

			Permutation permH1;
			permH1.Define( 12, 58 );
			permH1.Define( 13, 59 );
			permH1.Define( 14, 60 );
			permH1.Define( 15, 61 );
			permH1.Define( 16, 62 );
			permH1.Define( 17, 63 );
			permH1.Define( 22, 52 );
			permH1.Define( 23, 53 );
			permH1.Define( 24, 54 );
			permH1.Define( 25, 55 );
			permH1.Define( 26, 56 );
			permH1.Define( 27, 57 );
			permH1.Define( 32, 42 );
			permH1.Define( 33, 43 );
			permH1.Define( 34, 44 );
			permH1.Define( 35, 45 );
			permH1.Define( 36, 46 );
			permH1.Define( 37, 47 );
			permH1.Define( 42, 32 );
			permH1.Define( 43, 33 );
			permH1.Define( 44, 34 );
			permH1.Define( 45, 35 );
			permH1.Define( 46, 36 );
			permH1.Define( 47, 37 );
			permH1.Define( 52, 22 );
			permH1.Define( 53, 23 );
			permH1.Define( 54, 24 );
			permH1.Define( 55, 25 );
			permH1.Define( 56, 26 );
			permH1.Define( 57, 27 );
			permH1.Define( 58, 12 );
			permH1.Define( 59, 13 );
			permH1.Define( 60, 14 );
			permH1.Define( 61, 15 );
			permH1.Define( 62, 16 );
			permH1.Define( 63, 17 );

			shape->ccwRotationPermutation = permR1;
			shape->reflectionPermutationArray.push_back( permD1p );
			shape->reflectionPermutationArray.push_back( permV1 );
			shape->reflectionPermutationArray.push_back( permD1 );
			shape->reflectionPermutationArray.push_back( permH1 );

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