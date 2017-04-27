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
	pointArray.clear();

	switch( level )
	{
		case 1:
		{
			Permutation shapePermutation;

			// Level 1 is just the dihedral group D_3.
			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, -2.0, 0.0 ), 8.0, 3, 3.0 * M_PI / 6.0 );
			shapeList.push_back( shape );

			// R
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 1, 2 );
			shape->ccwRotationPermutation = shapePermutation;

			// F0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 1 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// F1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 1, 2 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// F2
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 2 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			return true;
		}
		case 2:
		{
			Permutation shapePermutation;

			// Level 2 is just the dihedral group D_4.
			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 0.0, 0.0 ), 8.0, 4, M_PI / 4.0 );
			shapeList.push_back( shape );

			// R
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 1, 2, 3 );
			shape->ccwRotationPermutation = shapePermutation;

			// Dp
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 1, 3 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// V
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 1 );
			shapePermutation.DefineCycle( 2, 3 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// D
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 2 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// H
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 3 );
			shapePermutation.DefineCycle( 1, 2 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			return true;
		}
		case 3:
		{
			Permutation shapePermutation;

			Shape* shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, -4.0, 0.0, 0.0 ), 6.0, 3 );
			shapeList.push_back( shape );

			// aR
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 4, 18 );
			shapePermutation.DefineCycle( 1, 5, 19 );
			shapePermutation.DefineCycle( 2, 6, 16 );
			shapePermutation.DefineCycle( 3, 7, 17 );
			shapePermutation.DefineCycle( 20, 21, 22 );
			shape->ccwRotationPermutation = shapePermutation;

			// aF0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 4 );
			shapePermutation.DefineCycle( 1, 7 );
			shapePermutation.DefineCycle( 3, 5 );
			shapePermutation.DefineCycle( 2, 6 );
			shapePermutation.DefineCycle( 21, 22 );
			shapePermutation.DefineCycle( 17, 19 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// aF1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 4, 18 );
			shapePermutation.DefineCycle( 5, 17 );
			shapePermutation.DefineCycle( 7, 19 );
			shapePermutation.DefineCycle( 6, 16 );
			shapePermutation.DefineCycle( 20, 22 );
			shapePermutation.DefineCycle( 1, 3 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// aF2
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 18 );
			shapePermutation.DefineCycle( 3, 19 );
			shapePermutation.DefineCycle( 1, 17 );
			shapePermutation.DefineCycle( 2, 16 );
			shapePermutation.DefineCycle( 20, 21 );
			shapePermutation.DefineCycle( 5, 7 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			shape = new Shape();
			shape->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 4.0, 0.0, 0.0 ), 6.0, 3, M_PI / 3.0 );
			shapeList.push_back( shape );

			// bR
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 8, 12, 16 );
			shapePermutation.DefineCycle( 9, 13, 17 );
			shapePermutation.DefineCycle( 10, 14, 18 );
			shapePermutation.DefineCycle( 11, 15, 19 );
			shapePermutation.DefineCycle( 23, 24, 25 );
			shape->ccwRotationPermutation = shapePermutation;

			// bF0
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 8, 16 );
			shapePermutation.DefineCycle( 11, 17 );
			shapePermutation.DefineCycle( 9, 19 );
			shapePermutation.DefineCycle( 10, 18 );
			shapePermutation.DefineCycle( 24, 25 );
			shapePermutation.DefineCycle( 13, 15 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// bF1
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 8, 12 );
			shapePermutation.DefineCycle( 9, 15 );
			shapePermutation.DefineCycle( 11, 13 );
			shapePermutation.DefineCycle( 10, 14 );
			shapePermutation.DefineCycle( 23, 25 );
			shapePermutation.DefineCycle( 17, 19 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// bF2
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 12, 16 );
			shapePermutation.DefineCycle( 13, 19 );
			shapePermutation.DefineCycle( 15, 17 );
			shapePermutation.DefineCycle( 14, 18 );
			shapePermutation.DefineCycle( 23, 24 );
			shapePermutation.DefineCycle( 9, 11 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

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
			Permutation shapePermutation;

			Shape* shape = nullptr;

			shape = new Shape();
			shape->MakeRectangle( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, -5.0, 0.0 ), 12.0, 2.0, 0.0 );
			shapeList.push_back( shape );

			// aR
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 25, 26 );
			shapePermutation.DefineCycle( 20, 31 );
			shapePermutation.DefineCycle( 24, 27 );
			shapePermutation.DefineCycle( 21, 30 );
			shapePermutation.DefineCycle( 22, 29 );
			shapePermutation.DefineCycle( 23, 28 );
			shape->ccwRotationPermutation = shapePermutation;

			// aH
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 20, 26 );
			shapePermutation.DefineCycle( 21, 27 );
			shapePermutation.DefineCycle( 22, 28 );
			shapePermutation.DefineCycle( 23, 29 );
			shapePermutation.DefineCycle( 24, 30 );
			shapePermutation.DefineCycle( 25, 31 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// aV
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 20, 25 );
			shapePermutation.DefineCycle( 21, 24 );
			shapePermutation.DefineCycle( 22, 23 );
			shapePermutation.DefineCycle( 26, 31 );
			shapePermutation.DefineCycle( 27, 30 );
			shapePermutation.DefineCycle( 28, 29 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			shape = new Shape();
			shape->MakeRectangle( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 0.0, 5.0, 0.0 ), 12.0, 2.0, 0.0 );
			shapeList.push_back( shape );

			// cR
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 11 );
			shapePermutation.DefineCycle( 6, 5 );
			shapePermutation.DefineCycle( 1, 10 );
			shapePermutation.DefineCycle( 4, 7 );
			shapePermutation.DefineCycle( 2, 9 );
			shapePermutation.DefineCycle( 3, 8 );
			shape->ccwRotationPermutation = shapePermutation;

			// cH
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 6 );
			shapePermutation.DefineCycle( 1, 7 );
			shapePermutation.DefineCycle( 2, 8 );
			shapePermutation.DefineCycle( 3, 9 );
			shapePermutation.DefineCycle( 4, 10 );
			shapePermutation.DefineCycle( 5, 11 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// cV
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 5 );
			shapePermutation.DefineCycle( 1, 4 );
			shapePermutation.DefineCycle( 2, 3 );
			shapePermutation.DefineCycle( 6, 11 );
			shapePermutation.DefineCycle( 7, 10 );
			shapePermutation.DefineCycle( 8, 9 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			shape = new Shape();
			shape->MakeRectangle( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, -5.0, 0.0, 0.0 ), 12.0, 2.0, M_PI / 2.0 );
			shapeList.push_back( shape );

			// dR
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 27 );
			shapePermutation.DefineCycle( 1, 26 );
			shapePermutation.DefineCycle( 6, 21 );
			shapePermutation.DefineCycle( 7, 20 );
			shapePermutation.DefineCycle( 12, 17 );
			shapePermutation.DefineCycle( 13, 16 );
			shape->ccwRotationPermutation = shapePermutation;

			// dV
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 1 );
			shapePermutation.DefineCycle( 6, 7 );
			shapePermutation.DefineCycle( 12, 13 );
			shapePermutation.DefineCycle( 16, 17 );
			shapePermutation.DefineCycle( 20, 21 );
			shapePermutation.DefineCycle( 26, 27 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// dH
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 0, 26 );
			shapePermutation.DefineCycle( 6, 20 );
			shapePermutation.DefineCycle( 12, 16 );
			shapePermutation.DefineCycle( 1, 27 );
			shapePermutation.DefineCycle( 7, 21 );
			shapePermutation.DefineCycle( 13, 17 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			shape = new Shape();
			shape->MakeRectangle( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, 5.0, 0.0, 0.0 ), 12.0, 2.0, M_PI / 2.0 );
			shapeList.push_back( shape );

			// bR
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 5, 30 );
			shapePermutation.DefineCycle( 4, 31 );
			shapePermutation.DefineCycle( 10, 25 );
			shapePermutation.DefineCycle( 11, 24 );
			shapePermutation.DefineCycle( 14, 19 );
			shapePermutation.DefineCycle( 15, 18 );
			shape->ccwRotationPermutation = shapePermutation;

			// bV
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 4, 5 );
			shapePermutation.DefineCycle( 10, 11 );
			shapePermutation.DefineCycle( 14, 15 );
			shapePermutation.DefineCycle( 18, 19 );
			shapePermutation.DefineCycle( 24, 25 );
			shapePermutation.DefineCycle( 30, 31 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			// bH
			shapePermutation.DefineIdentity();
			shapePermutation.DefineCycle( 4, 30 );
			shapePermutation.DefineCycle( 10, 24 );
			shapePermutation.DefineCycle( 14, 18 );
			shapePermutation.DefineCycle( 5, 31 );
			shapePermutation.DefineCycle( 11, 25 );
			shapePermutation.DefineCycle( 15, 19 );
			shape->reflectionPermutationArray.push_back( shapePermutation );

			return true;
		}
		case 7:
		{
			c3ga::vectorE3GA point;

			double x = 2.0;
			double y = -4.0;
			
			Shape* shape0 = new Shape();
			shape0->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, x, y, 0.0 ), 5.0, 5, 0.0, &point );
			shapeList.push_back( shape0 );
			pointArray.push_back( point );

			double angle = 2.0 * M_PI / 5.0;

			c3ga::vectorE3GA vertex;
			vertex.set_e1( x + 5.0 * cos( angle ) );
			vertex.set_e2( y + 5.0 * sin( angle ) );
			vertex.set_e3( 0.0 );
			point = point + 0.3 * ( vertex - point );
			pointArray.push_back( point );

			angle = 4.0 * M_PI / 5.0;
			vertex.set_e1( x + 5.0 * cos( angle ) );
			vertex.set_e2( y + 5.0 * sin( angle ) );
			point = point + 0.93 * ( vertex - point );
			pointArray.push_back( point );

			angle = 2.0 * M_PI / 5.0;
			double distance = 7.0;

			Shape* shape1 = new Shape();
			shape1->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, x + distance * cos( angle ), y + distance * sin( angle ), 0.0 ), 5.0, 5, -M_PI / 5.0, &point );
			shapeList.push_back( shape1 );
			pointArray.push_back( point );

			angle = 2.0 * ( 2.0 * M_PI / 5.0 );

			Shape* shape2 = new Shape();
			shape2->MakePolygon( c3ga::vectorE3GA( c3ga::vectorE3GA::coord_e1_e2_e3, x + distance * cos( angle ), y + distance * sin( angle ), 0.0 ), 3.0, 5, -M_PI / 5.0, &point );
			shapeList.push_back( shape2 );
			pointArray.push_back( point );

			//wxString code = CalculateAndPrintGenerators();
			pointArray.clear();

			Permutation R_0;
			R_0.Define( 0, 4 );
			R_0.Define( 1, 2 );
			R_0.Define( 2, 3 );
			R_0.Define( 3, 0 );
			R_0.Define( 4, 1 );
			R_0.Define( 5, 22 );
			R_0.Define( 14, 19 );
			R_0.Define( 15, 16 );
			R_0.Define( 16, 5 );
			R_0.Define( 17, 15 );
			R_0.Define( 18, 20 );
			R_0.Define( 19, 21 );
			R_0.Define( 20, 14 );
			R_0.Define( 21, 18 );
			R_0.Define( 22, 17 );
			R_0.Define( 23, 48 );
			R_0.Define( 32, 45 );
			R_0.Define( 41, 42 );
			R_0.Define( 42, 23 );
			R_0.Define( 43, 41 );
			R_0.Define( 44, 46 );
			R_0.Define( 45, 47 );
			R_0.Define( 46, 32 );
			R_0.Define( 47, 44 );
			R_0.Define( 48, 43 );

			Permutation F0_0;
			F0_0.Define( 0, 3 );
			F0_0.Define( 2, 4 );
			F0_0.Define( 3, 0 );
			F0_0.Define( 4, 2 );
			F0_0.Define( 5, 21 );
			F0_0.Define( 14, 17 );
			F0_0.Define( 15, 20 );
			F0_0.Define( 16, 18 );
			F0_0.Define( 17, 14 );
			F0_0.Define( 18, 16 );
			F0_0.Define( 19, 22 );
			F0_0.Define( 20, 15 );
			F0_0.Define( 21, 5 );
			F0_0.Define( 22, 19 );
			F0_0.Define( 23, 47 );
			F0_0.Define( 32, 43 );
			F0_0.Define( 41, 46 );
			F0_0.Define( 42, 44 );
			F0_0.Define( 43, 32 );
			F0_0.Define( 44, 42 );
			F0_0.Define( 45, 48 );
			F0_0.Define( 46, 41 );
			F0_0.Define( 47, 23 );
			F0_0.Define( 48, 45 );

			Permutation F1_0;
			F1_0.Define( 0, 4 );
			F1_0.Define( 1, 3 );
			F1_0.Define( 3, 1 );
			F1_0.Define( 4, 0 );
			F1_0.Define( 5, 20 );
			F1_0.Define( 14, 16 );
			F1_0.Define( 15, 19 );
			F1_0.Define( 16, 14 );
			F1_0.Define( 17, 21 );
			F1_0.Define( 18, 22 );
			F1_0.Define( 19, 15 );
			F1_0.Define( 20, 5 );
			F1_0.Define( 21, 17 );
			F1_0.Define( 22, 18 );
			F1_0.Define( 23, 46 );
			F1_0.Define( 32, 42 );
			F1_0.Define( 41, 45 );
			F1_0.Define( 42, 32 );
			F1_0.Define( 43, 47 );
			F1_0.Define( 44, 48 );
			F1_0.Define( 45, 41 );
			F1_0.Define( 46, 23 );
			F1_0.Define( 47, 43 );
			F1_0.Define( 48, 44 );

			Permutation F2_0;
			F2_0.Define( 0, 2 );
			F2_0.Define( 1, 4 );
			F2_0.Define( 2, 0 );
			F2_0.Define( 4, 1 );
			F2_0.Define( 5, 19 );
			F2_0.Define( 14, 22 );
			F2_0.Define( 15, 18 );
			F2_0.Define( 16, 21 );
			F2_0.Define( 17, 20 );
			F2_0.Define( 18, 15 );
			F2_0.Define( 19, 5 );
			F2_0.Define( 20, 17 );
			F2_0.Define( 21, 16 );
			F2_0.Define( 22, 14 );
			F2_0.Define( 23, 45 );
			F2_0.Define( 32, 48 );
			F2_0.Define( 41, 44 );
			F2_0.Define( 42, 47 );
			F2_0.Define( 43, 46 );
			F2_0.Define( 44, 41 );
			F2_0.Define( 45, 23 );
			F2_0.Define( 46, 43 );
			F2_0.Define( 47, 42 );
			F2_0.Define( 48, 32 );

			Permutation F3_0;
			F3_0.Define( 1, 2 );
			F3_0.Define( 2, 1 );
			F3_0.Define( 3, 4 );
			F3_0.Define( 4, 3 );
			F3_0.Define( 5, 18 );
			F3_0.Define( 14, 15 );
			F3_0.Define( 15, 14 );
			F3_0.Define( 16, 20 );
			F3_0.Define( 17, 19 );
			F3_0.Define( 18, 5 );
			F3_0.Define( 19, 17 );
			F3_0.Define( 20, 16 );
			F3_0.Define( 21, 22 );
			F3_0.Define( 22, 21 );
			F3_0.Define( 23, 44 );
			F3_0.Define( 32, 41 );
			F3_0.Define( 41, 32 );
			F3_0.Define( 42, 46 );
			F3_0.Define( 43, 45 );
			F3_0.Define( 44, 23 );
			F3_0.Define( 45, 43 );
			F3_0.Define( 46, 42 );
			F3_0.Define( 47, 48 );
			F3_0.Define( 48, 47 );

			Permutation F4_0;
			F4_0.Define( 0, 1 );
			F4_0.Define( 1, 0 );
			F4_0.Define( 2, 3 );
			F4_0.Define( 3, 2 );
			F4_0.Define( 5, 14 );
			F4_0.Define( 14, 5 );
			F4_0.Define( 15, 21 );
			F4_0.Define( 16, 19 );
			F4_0.Define( 17, 18 );
			F4_0.Define( 18, 17 );
			F4_0.Define( 19, 16 );
			F4_0.Define( 20, 22 );
			F4_0.Define( 21, 15 );
			F4_0.Define( 22, 20 );
			F4_0.Define( 23, 32 );
			F4_0.Define( 32, 23 );
			F4_0.Define( 41, 47 );
			F4_0.Define( 42, 45 );
			F4_0.Define( 43, 44 );
			F4_0.Define( 44, 43 );
			F4_0.Define( 45, 42 );
			F4_0.Define( 46, 48 );
			F4_0.Define( 47, 41 );
			F4_0.Define( 48, 46 );

			shape0->ccwRotationPermutation = R_0;
			shape0->reflectionPermutationArray.push_back( F0_0 );
			shape0->reflectionPermutationArray.push_back( F1_0 );
			shape0->reflectionPermutationArray.push_back( F2_0 );
			shape0->reflectionPermutationArray.push_back( F3_0 );
			shape0->reflectionPermutationArray.push_back( F4_0 );

			Permutation R_1;
			R_1.Define( 5, 13 );
			R_1.Define( 6, 11 );
			R_1.Define( 7, 8 );
			R_1.Define( 8, 9 );
			R_1.Define( 9, 5 );
			R_1.Define( 10, 12 );
			R_1.Define( 11, 20 );
			R_1.Define( 12, 6 );
			R_1.Define( 13, 7 );
			R_1.Define( 20, 10 );
			R_1.Define( 32, 40 );
			R_1.Define( 33, 38 );
			R_1.Define( 34, 35 );
			R_1.Define( 35, 36 );
			R_1.Define( 36, 32 );
			R_1.Define( 37, 39 );
			R_1.Define( 38, 42 );
			R_1.Define( 39, 33 );
			R_1.Define( 40, 34 );
			R_1.Define( 42, 37 );
			R_1.Define( 49, 53 );
			R_1.Define( 50, 51 );
			R_1.Define( 51, 52 );
			R_1.Define( 52, 49 );
			R_1.Define( 53, 50 );

			Permutation F0_1;
			F0_1.Define( 5, 12 );
			F0_1.Define( 6, 9 );
			F0_1.Define( 7, 20 );
			F0_1.Define( 8, 11 );
			F0_1.Define( 9, 6 );
			F0_1.Define( 10, 13 );
			F0_1.Define( 11, 8 );
			F0_1.Define( 12, 5 );
			F0_1.Define( 13, 10 );
			F0_1.Define( 20, 7 );
			F0_1.Define( 32, 39 );
			F0_1.Define( 33, 36 );
			F0_1.Define( 34, 42 );
			F0_1.Define( 35, 38 );
			F0_1.Define( 36, 33 );
			F0_1.Define( 37, 40 );
			F0_1.Define( 38, 35 );
			F0_1.Define( 39, 32 );
			F0_1.Define( 40, 37 );
			F0_1.Define( 42, 34 );
			F0_1.Define( 49, 52 );
			F0_1.Define( 51, 53 );
			F0_1.Define( 52, 49 );
			F0_1.Define( 53, 51 );

			Permutation F1_1;
			F1_1.Define( 5, 11 );
			F1_1.Define( 6, 13 );
			F1_1.Define( 7, 12 );
			F1_1.Define( 8, 10 );
			F1_1.Define( 9, 20 );
			F1_1.Define( 10, 8 );
			F1_1.Define( 11, 5 );
			F1_1.Define( 12, 7 );
			F1_1.Define( 13, 6 );
			F1_1.Define( 20, 9 );
			F1_1.Define( 32, 38 );
			F1_1.Define( 33, 40 );
			F1_1.Define( 34, 39 );
			F1_1.Define( 35, 37 );
			F1_1.Define( 36, 42 );
			F1_1.Define( 37, 35 );
			F1_1.Define( 38, 32 );
			F1_1.Define( 39, 34 );
			F1_1.Define( 40, 33 );
			F1_1.Define( 42, 36 );
			F1_1.Define( 49, 53 );
			F1_1.Define( 50, 52 );
			F1_1.Define( 52, 50 );
			F1_1.Define( 53, 49 );

			Permutation F2_1;
			F2_1.Define( 5, 10 );
			F2_1.Define( 6, 8 );
			F2_1.Define( 7, 11 );
			F2_1.Define( 8, 6 );
			F2_1.Define( 9, 12 );
			F2_1.Define( 10, 5 );
			F2_1.Define( 11, 7 );
			F2_1.Define( 12, 9 );
			F2_1.Define( 13, 20 );
			F2_1.Define( 20, 13 );
			F2_1.Define( 32, 37 );
			F2_1.Define( 33, 35 );
			F2_1.Define( 34, 38 );
			F2_1.Define( 35, 33 );
			F2_1.Define( 36, 39 );
			F2_1.Define( 37, 32 );
			F2_1.Define( 38, 34 );
			F2_1.Define( 39, 36 );
			F2_1.Define( 40, 42 );
			F2_1.Define( 42, 40 );
			F2_1.Define( 49, 51 );
			F2_1.Define( 50, 53 );
			F2_1.Define( 51, 49 );
			F2_1.Define( 53, 50 );

			Permutation F3_1;
			F3_1.Define( 5, 6 );
			F3_1.Define( 6, 5 );
			F3_1.Define( 7, 10 );
			F3_1.Define( 8, 20 );
			F3_1.Define( 9, 11 );
			F3_1.Define( 10, 7 );
			F3_1.Define( 11, 9 );
			F3_1.Define( 12, 13 );
			F3_1.Define( 13, 12 );
			F3_1.Define( 20, 8 );
			F3_1.Define( 32, 33 );
			F3_1.Define( 33, 32 );
			F3_1.Define( 34, 37 );
			F3_1.Define( 35, 42 );
			F3_1.Define( 36, 38 );
			F3_1.Define( 37, 34 );
			F3_1.Define( 38, 36 );
			F3_1.Define( 39, 40 );
			F3_1.Define( 40, 39 );
			F3_1.Define( 42, 35 );
			F3_1.Define( 50, 51 );
			F3_1.Define( 51, 50 );
			F3_1.Define( 52, 53 );
			F3_1.Define( 53, 52 );

			Permutation F4_1;
			F4_1.Define( 5, 20 );
			F4_1.Define( 6, 7 );
			F4_1.Define( 7, 6 );
			F4_1.Define( 8, 12 );
			F4_1.Define( 9, 10 );
			F4_1.Define( 10, 9 );
			F4_1.Define( 11, 13 );
			F4_1.Define( 12, 8 );
			F4_1.Define( 13, 11 );
			F4_1.Define( 20, 5 );
			F4_1.Define( 32, 42 );
			F4_1.Define( 33, 34 );
			F4_1.Define( 34, 33 );
			F4_1.Define( 35, 39 );
			F4_1.Define( 36, 37 );
			F4_1.Define( 37, 36 );
			F4_1.Define( 38, 40 );
			F4_1.Define( 39, 35 );
			F4_1.Define( 40, 38 );
			F4_1.Define( 42, 32 );
			F4_1.Define( 49, 50 );
			F4_1.Define( 50, 49 );
			F4_1.Define( 51, 52 );
			F4_1.Define( 52, 51 );

			shape1->ccwRotationPermutation = R_1;
			shape1->reflectionPermutationArray.push_back( F0_1 );
			shape1->reflectionPermutationArray.push_back( F1_1 );
			shape1->reflectionPermutationArray.push_back( F2_1 );
			shape1->reflectionPermutationArray.push_back( F3_1 );
			shape1->reflectionPermutationArray.push_back( F4_1 );

			Permutation R_2;
			R_2.Define( 23, 31 );
			R_2.Define( 24, 29 );
			R_2.Define( 25, 26 );
			R_2.Define( 26, 23 );
			R_2.Define( 27, 25 );
			R_2.Define( 28, 30 );
			R_2.Define( 29, 45 );
			R_2.Define( 30, 24 );
			R_2.Define( 31, 27 );
			R_2.Define( 45, 28 );
			R_2.Define( 54, 58 );
			R_2.Define( 55, 56 );
			R_2.Define( 56, 57 );
			R_2.Define( 57, 54 );
			R_2.Define( 58, 55 );

			Permutation F0_2;
			F0_2.Define( 23, 45 );
			F0_2.Define( 24, 27 );
			F0_2.Define( 25, 30 );
			F0_2.Define( 26, 28 );
			F0_2.Define( 27, 24 );
			F0_2.Define( 28, 26 );
			F0_2.Define( 29, 31 );
			F0_2.Define( 30, 25 );
			F0_2.Define( 31, 29 );
			F0_2.Define( 45, 23 );
			F0_2.Define( 54, 57 );
			F0_2.Define( 56, 58 );
			F0_2.Define( 57, 54 );
			F0_2.Define( 58, 56 );

			Permutation F1_2;
			F1_2.Define( 23, 30 );
			F1_2.Define( 24, 26 );
			F1_2.Define( 25, 29 );
			F1_2.Define( 26, 24 );
			F1_2.Define( 27, 45 );
			F1_2.Define( 28, 31 );
			F1_2.Define( 29, 25 );
			F1_2.Define( 30, 23 );
			F1_2.Define( 31, 28 );
			F1_2.Define( 45, 27 );
			F1_2.Define( 54, 58 );
			F1_2.Define( 55, 57 );
			F1_2.Define( 57, 55 );
			F1_2.Define( 58, 54 );

			Permutation F2_2;
			F2_2.Define( 23, 29 );
			F2_2.Define( 24, 31 );
			F2_2.Define( 25, 28 );
			F2_2.Define( 26, 45 );
			F2_2.Define( 27, 30 );
			F2_2.Define( 28, 25 );
			F2_2.Define( 29, 23 );
			F2_2.Define( 30, 27 );
			F2_2.Define( 31, 24 );
			F2_2.Define( 45, 26 );
			F2_2.Define( 54, 56 );
			F2_2.Define( 55, 58 );
			F2_2.Define( 56, 54 );
			F2_2.Define( 58, 55 );

			Permutation F3_2;
			F3_2.Define( 23, 28 );
			F3_2.Define( 24, 25 );
			F3_2.Define( 25, 24 );
			F3_2.Define( 26, 30 );
			F3_2.Define( 27, 29 );
			F3_2.Define( 28, 23 );
			F3_2.Define( 29, 27 );
			F3_2.Define( 30, 26 );
			F3_2.Define( 31, 45 );
			F3_2.Define( 45, 31 );
			F3_2.Define( 55, 56 );
			F3_2.Define( 56, 55 );
			F3_2.Define( 57, 58 );
			F3_2.Define( 58, 57 );

			Permutation F4_2;
			F4_2.Define( 23, 24 );
			F4_2.Define( 24, 23 );
			F4_2.Define( 25, 45 );
			F4_2.Define( 26, 29 );
			F4_2.Define( 27, 28 );
			F4_2.Define( 28, 27 );
			F4_2.Define( 29, 26 );
			F4_2.Define( 30, 31 );
			F4_2.Define( 31, 30 );
			F4_2.Define( 45, 25 );
			F4_2.Define( 54, 55 );
			F4_2.Define( 55, 54 );
			F4_2.Define( 56, 57 );
			F4_2.Define( 57, 56 );

			shape0->ccwRotationPermutation = R_2;
			shape0->reflectionPermutationArray.push_back( F0_2 );
			shape0->reflectionPermutationArray.push_back( F1_2 );
			shape0->reflectionPermutationArray.push_back( F2_2 );
			shape0->reflectionPermutationArray.push_back( F3_2 );
			shape0->reflectionPermutationArray.push_back( F4_2 );

			return true;
		}
		// TODO: Concentric pentagons...?
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