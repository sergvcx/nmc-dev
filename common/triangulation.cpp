#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "triangulation.h"
#include "primitive.h"
#include "nmtype.h"
#include "nmpp.h"
#include "nmassert.h"

int maxTrianglesCount = 256;
int * bufNi0;
float * bufNf0;
float * bufNf1;
float * bufNf2;
float * bufNf3;
float * bufNf4;
float * bufNf5;
float * bufNf6;
float * bufNf7;
float * bufNf8;
float * bufNf9;
float * bufNf10;
float * bufNf11;
float * bufNf12;
float * bufNf13;

int * protectedMallocInt( int * dstPointer, int N )
{
	int * mallocPointer = (int*)malloc((N + 4) * sizeof(int));
	mallocPointer[0] = 77;
	mallocPointer[1] = 77;
	mallocPointer[N + 2] = 77;
	mallocPointer[N + 3] = 77;
	dstPointer = mallocPointer + 2;
	return dstPointer;
}

float * protectedMallocFloat( float * dstPointer, int N )
{
	float * mallocPointer = (float*)malloc((N + 4) * sizeof(float));
	mallocPointer[0] = 66.0;
	mallocPointer[1] = 66.0;
	mallocPointer[N + 2] = 66.0;
	mallocPointer[N + 3] = 66.0;
	dstPointer = mallocPointer + 2;
	return dstPointer;
}

extern "C" int triangulationInit()
{
	bufNi0 = protectedMallocInt( bufNi0, maxTrianglesCount);
	if(!bufNi0)
		return -1;
	// printf("\nbufNi0 %p _ %d", bufNi0, (*(bufNi0 - 1)));
	bufNf0 = protectedMallocFloat( bufNf0, maxTrianglesCount );
	if(!bufNf0)
		return -1;
	// printf("\nbufNf0 %p _ %f", bufNf0, (*(bufNf0 - 1)));
	bufNf1 = protectedMallocFloat( bufNf1, maxTrianglesCount );
	if(!bufNf1)
		return -1;
	// printf("\nbufNf1 %p _ %f", bufNf1, (*(bufNf1 - 1)));
	bufNf2 = protectedMallocFloat( bufNf2, maxTrianglesCount );
	if(!bufNf2)
		return -1;
	// printf("\nbufNf2 %p _ %f", bufNf2, (*(bufNf2 - 1)));
	bufNf3 = protectedMallocFloat( bufNf3, maxTrianglesCount );
	if(!bufNf3)
		return -1;
	// printf("\nbufNf3 %p _ %f", bufNf3, (*(bufNf3 - 1)));
	bufNf4 = protectedMallocFloat( bufNf4, maxTrianglesCount );
	if(!bufNf4)
		return -1;
	// printf("\nbufNf4 %p _ %f", bufNf4, (*(bufNf4 - 1)));
	bufNf5 = protectedMallocFloat( bufNf5, maxTrianglesCount );
	if(!bufNf5)
		return -1;
	// printf("\nbufNf5 %p _ %f", bufNf5, (*(bufNf5 - 1)));
	bufNf6 = protectedMallocFloat( bufNf6, maxTrianglesCount );
	if(!bufNf6)
		return -1;
	// printf("\nbufNf6 %p _ %f", bufNf6, (*(bufNf6 - 1)));
	bufNf7 = protectedMallocFloat( bufNf7, maxTrianglesCount );
	if(!bufNf7)
		return -1;
	// printf("\nbufNf7 %p _ %f", bufNf7, (*(bufNf7 - 1)));
	bufNf8 = protectedMallocFloat( bufNf8, maxTrianglesCount );
	if(!bufNf8)
		return -1;
	// printf("\nbufNf8 %p _ %f", bufNf8, (*(bufNf8 - 1)));
	bufNf9 = protectedMallocFloat( bufNf9, maxTrianglesCount );
	if(!bufNf9)
		return -1;
	// printf("\nbufNf9 %p _ %f", bufNf9, (*(bufNf9 - 1)));
	bufNf10 = protectedMallocFloat( bufNf10, maxTrianglesCount );
	if(!bufNf10)
		return -1;
	// printf("\nbufNf10 %p _ %f", bufNf10, (*(bufNf10 - 1)));
	bufNf11 = protectedMallocFloat( bufNf11, maxTrianglesCount );
	if(!bufNf11)
		return -1;
	// printf("\nbufNf11 %p _ %f", bufNf11, (*(bufNf11 - 1)));
	bufNf12 = protectedMallocFloat( bufNf12, maxTrianglesCount );
	if(!bufNf12)
		return -1;
	// printf("\nbufNf12 %p _ %f", bufNf12, (*(bufNf12 - 1)));
	bufNf13 = protectedMallocFloat( bufNf13, maxTrianglesCount );
	if(!bufNf13)
		return -1;
	// printf("\nbufNf13 %p _ %f", bufNf13, (*(bufNf13 - 1)));
	return 0;
}

void freeBufCheckInt()
{
	if ( (*(bufNi0 - 2)) != 77 || (*(bufNi0 - 1)) != 77 || (*(bufNi0 + maxTrianglesCount)) != 77 || (*(bufNi0 + maxTrianglesCount + 1)) != 77 )
		printf("\nbufNi0 { %d, %d, ..., %d, %d}", (*(bufNi0 - 2)), (*(bufNi0 - 1)), (*(bufNi0 + maxTrianglesCount)), (*(bufNi0 + maxTrianglesCount + 1)));
	if ( (*(bufNf0 - 2)) != 66.0 || (*(bufNf0 - 1)) != 66.0 || (*(bufNf0 + maxTrianglesCount)) != 66.0 || (*(bufNf0 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf0 { %f, %f, ..., %f, %f}", (*(bufNf0 - 2)), (*(bufNf0 - 1)), (*(bufNf0 + maxTrianglesCount)), (*(bufNf0 + maxTrianglesCount + 1)));
	if ( (*(bufNf1 - 2)) != 66.0 || (*(bufNf1 - 1)) != 66.0 || (*(bufNf1 + maxTrianglesCount)) != 66.0 || (*(bufNf1 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf1 { %f, %f, ..., %f, %f}", (*(bufNf1 - 2)), (*(bufNf1 - 1)), (*(bufNf1 + maxTrianglesCount)), (*(bufNf1 + maxTrianglesCount + 1)));
	if ( (*(bufNf2 - 2)) != 66.0 || (*(bufNf2 - 1)) != 66.0 || (*(bufNf2 + maxTrianglesCount)) != 66.0 || (*(bufNf2 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf2 { %f, %f, ..., %f, %f}", (*(bufNf2 - 2)), (*(bufNf2 - 1)), (*(bufNf2 + maxTrianglesCount)), (*(bufNf2 + maxTrianglesCount + 1)));
	if ( (*(bufNf3 - 2)) != 66.0 || (*(bufNf3 - 1)) != 66.0 || (*(bufNf3 + maxTrianglesCount)) != 66.0 || (*(bufNf3 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf3 { %f, %f, ..., %f, %f}", (*(bufNf3 - 2)), (*(bufNf3 - 1)), (*(bufNf3 + maxTrianglesCount)), (*(bufNf3 + maxTrianglesCount + 1)));
	if ( (*(bufNf4 - 2)) != 66.0 || (*(bufNf4 - 1)) != 66.0 || (*(bufNf4 + maxTrianglesCount)) != 66.0 || (*(bufNf4 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf4 { %f, %f, ..., %f, %f}", (*(bufNf4 - 2)), (*(bufNf4 - 1)), (*(bufNf4 + maxTrianglesCount)), (*(bufNf4 + maxTrianglesCount + 1)));
	if ( (*(bufNf5 - 2)) != 66.0 || (*(bufNf5 - 1)) != 66.0 || (*(bufNf5 + maxTrianglesCount)) != 66.0 || (*(bufNf5 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf5 { %f, %f, ..., %f, %f}", (*(bufNf5 - 2)), (*(bufNf5 - 1)), (*(bufNf5 + maxTrianglesCount)), (*(bufNf5 + maxTrianglesCount + 1)));
	if ( (*(bufNf6 - 2)) != 66.0 || (*(bufNf6 - 1)) != 66.0 || (*(bufNf6 + maxTrianglesCount)) != 66.0 || (*(bufNf6 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf6 { %f, %f, ..., %f, %f}", (*(bufNf6 - 2)), (*(bufNf6 - 1)), (*(bufNf6 + maxTrianglesCount)), (*(bufNf6 + maxTrianglesCount + 1)));
	if ( (*(bufNf7 - 2)) != 66.0 || (*(bufNf7 - 1)) != 66.0 || (*(bufNf7 + maxTrianglesCount)) != 66.0 || (*(bufNf7 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf7 { %f, %f, ..., %f, %f}", (*(bufNf7 - 2)), (*(bufNf7 - 1)), (*(bufNf7 + maxTrianglesCount)), (*(bufNf7 + maxTrianglesCount + 1)));
	if ( (*(bufNf8 - 2)) != 66.0 || (*(bufNf8 - 1)) != 66.0 || (*(bufNf8 + maxTrianglesCount)) != 66.0 || (*(bufNf8 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf8 { %f, %f, ..., %f, %f}", (*(bufNf8 - 2)), (*(bufNf8 - 1)), (*(bufNf8 + maxTrianglesCount)), (*(bufNf8 + maxTrianglesCount + 1)));
	if ( (*(bufNf9 - 2)) != 66.0 || (*(bufNf9 - 1)) != 66.0 || (*(bufNf9 + maxTrianglesCount)) != 66.0 || (*(bufNf9 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf9 { %f, %f, ..., %f, %f}", (*(bufNf9 - 2)), (*(bufNf9 - 1)), (*(bufNf9 + maxTrianglesCount)), (*(bufNf9 + maxTrianglesCount + 1)));
	if ( (*(bufNf10 - 2)) != 66.0 || (*(bufNf10 - 1)) != 66.0 || (*(bufNf10 + maxTrianglesCount)) != 66.0 || (*(bufNf10 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf10 { %f, %f, ..., %f, %f}", (*(bufNf10 - 2)), (*(bufNf10 - 1)), (*(bufNf10 + maxTrianglesCount)), (*(bufNf10 + maxTrianglesCount + 1)));
	if ( (*(bufNf11 - 2)) != 66.0 || (*(bufNf11 - 1)) != 66.0 || (*(bufNf11 + maxTrianglesCount)) != 66.0 || (*(bufNf11 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf11 { %f, %f, ..., %f, %f}", (*(bufNf11 - 2)), (*(bufNf11 - 1)), (*(bufNf11 + maxTrianglesCount)), (*(bufNf11 + maxTrianglesCount + 1)));
	if ( (*(bufNf12 - 2)) != 66.0 || (*(bufNf12 - 1)) != 66.0 || (*(bufNf12 + maxTrianglesCount)) != 66.0 || (*(bufNf12 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf12 { %f, %f, ..., %f, %f}", (*(bufNf12 - 2)), (*(bufNf12 - 1)), (*(bufNf12 + maxTrianglesCount)), (*(bufNf12 + maxTrianglesCount + 1)));
	if ( (*(bufNf13 - 2)) != 66.0 || (*(bufNf13 - 1)) != 66.0 || (*(bufNf13 + maxTrianglesCount)) != 66.0 || (*(bufNf13 + maxTrianglesCount + 1)) != 66.0 )
		printf("\nbufNf13 { %f, %f, ..., %f, %f}", (*(bufNf13 - 2)), (*(bufNf13 - 1)), (*(bufNf13 + maxTrianglesCount)), (*(bufNf13 + maxTrianglesCount + 1)));
}

extern "C" void triangulationFree()
{
	freeBufCheckInt();
	free((bufNi0 - 2));
	free((bufNf0 - 2));
	free((bufNf1 - 2));
	free((bufNf2 - 2));
	free((bufNf3 - 2));
	free((bufNf4 - 2));
	free((bufNf5 - 2));
	free((bufNf6 - 2));
	free((bufNf7 - 2));
	free((bufNf8 - 2));
	free((bufNf9 - 2));
	free((bufNf10 - 2));
	free((bufNf11 - 2));
	free((bufNf12 - 2));
	free((bufNf13 - 2));
}

extern "C" void generateMasks( TrianglePointers * srcTriangles, int srcCount, int maxWidth, int maxHeight, int * flags )
{
	v2nm32f * Axy = (v2nm32f*)bufNf6;
	v2nm32f * Bxy = (v2nm32f*)bufNf7;
	v2nm32f * Cxy = (v2nm32f*)bufNf8;

	v2nm32f * dAB = (v2nm32f*)bufNf9;
	v2nm32f * dBC = (v2nm32f*)bufNf10;
	v2nm32f * dAC = (v2nm32f*)bufNf11;

	v2nm32f limatationConstant;
	limatationConstant.v0 = maxWidth;
	limatationConstant.v1 = maxHeight;

	int * evenFlagsInt = flags;
	int * oddFlagsInt  = (int*)bufNf13;

	nmppsMerge_32f ( srcTriangles->v0.x, srcTriangles->v0.y, (float*)Axy, srcCount );
	nmppsMerge_32f ( srcTriangles->v1.x, srcTriangles->v1.y, (float*)Bxy, srcCount );
	nmppsMerge_32f ( srcTriangles->v2.x, srcTriangles->v2.y, (float*)Cxy, srcCount );

	nmppsSub_32f( (float*)Axy, (float*)Bxy, (float*)dAB, srcCount * 2 );
	nmppsSub_32f( (float*)Bxy, (float*)Cxy, (float*)dBC, srcCount * 2 );
	nmppsSub_32f( (float*)Axy, (float*)Cxy, (float*)dAC, srcCount * 2 );

	for(int i = 0; i < srcCount; ++i)
	{
		dAB[i].v0 = fabs(dAB[i].v0);
		dAB[i].v1 = fabs(dAB[i].v1);
		dBC[i].v0 = fabs(dBC[i].v0);
		dBC[i].v1 = fabs(dBC[i].v1);
		dAC[i].v0 = fabs(dAC[i].v0);
		dAC[i].v1 = fabs(dAC[i].v1);
	}

	int step = 1;
	nmppsCmpGtC_v2nm32f (dAB, &limatationConstant, evenFlagsInt, 				   oddFlagsInt,					  step, srcCount * 2);
	nmppsCmpGtC_v2nm32f (dBC, &limatationConstant, evenFlagsInt + (srcCount + 32), oddFlagsInt + (srcCount + 32), step, srcCount * 2);
	nmppsCmpGtC_v2nm32f (dAC, &limatationConstant, evenFlagsInt + (srcCount + 64), oddFlagsInt + (srcCount + 64), step, srcCount * 2);

	for(int i = 0; i < srcCount / 32 + 1; ++i)
	{
		evenFlagsInt[i] |= evenFlagsInt[srcCount + 32 + i];
		evenFlagsInt[i] |= evenFlagsInt[srcCount + 64 + i];
		oddFlagsInt[i] |= oddFlagsInt[srcCount + 32 + i];
		oddFlagsInt[i] |= oddFlagsInt[srcCount + 64 + i];
		evenFlagsInt[i] |= oddFlagsInt[i];
	}
}

extern "C" void sort( 	TrianglePointers * srcTriangles, int srcCount,
			TrianglePointers * toSplitTriangles, int * toSplitTrianglesCount,
			TrianglePointers * resultTriangles, int * resultCount,
			nm1 * flags )
{
	(*toSplitTrianglesCount) = 0;
	int tempResultCount = *resultCount;
	int tempToSplitTrianglesCount = *toSplitTrianglesCount;
	for(int i = 0; i < srcCount; ++i)
	{
		if( nmppsGet_1(flags, i) == 0 )
		{
			resultTriangles->v0.x[tempResultCount] = srcTriangles->v0.x[i];
			resultTriangles->v0.y[tempResultCount] = srcTriangles->v0.y[i];
			resultTriangles->v1.x[tempResultCount] = srcTriangles->v1.x[i];
			resultTriangles->v1.y[tempResultCount] = srcTriangles->v1.y[i];
			resultTriangles->v2.x[tempResultCount] = srcTriangles->v2.x[i];
			resultTriangles->v2.y[tempResultCount] = srcTriangles->v2.y[i];
			tempResultCount++;
		}
		else
		{
			toSplitTriangles->v0.x[tempToSplitTrianglesCount] = srcTriangles->v0.x[i];
			toSplitTriangles->v0.y[tempToSplitTrianglesCount] = srcTriangles->v0.y[i];
			toSplitTriangles->v1.x[tempToSplitTrianglesCount] = srcTriangles->v1.x[i];
			toSplitTriangles->v1.y[tempToSplitTrianglesCount] = srcTriangles->v1.y[i];
			toSplitTriangles->v2.x[tempToSplitTrianglesCount] = srcTriangles->v2.x[i];
			toSplitTriangles->v2.y[tempToSplitTrianglesCount] = srcTriangles->v2.y[i];
			tempToSplitTrianglesCount++;
		}
	}
	*resultCount = tempResultCount;
	*toSplitTrianglesCount = tempToSplitTrianglesCount;
}

extern "C" void sumOfSquares( float * srcVec1, float * srcVec2, float * dstVec, int srcCount )
{
	for(int i = 0; i < srcCount; ++i)
	{
		dstVec[i] = srcVec1[i] * srcVec1[i] + srcVec2[i] * srcVec2[i];
	}
}

extern "C" void maxEdge( int * maxEdgeArray, float * edge1, float * edge2, float * edge3, int edgeCount )
{
	for(int i = 0; i < edgeCount; ++i)
	{
		if( edge1[i] > edge2[i] )
			if( edge1[i] > edge3[i] )
				maxEdgeArray[i] = 1;
			else
				maxEdgeArray[i] = 3;
		else
			if( edge2[i] > edge3[i] )
				maxEdgeArray[i] = 2;
			else
				maxEdgeArray[i] = 3;
	}
}

extern "C" void split( TrianglePointers * toSplitTriangles, int toSplitTrianglesCount,
			TrianglePointers * splittedTriangles, int * splittedTrianglesCount)
{
	float * dXab = bufNf6;
	float * dYab = bufNf7;
	nmppsSub_32f ( toSplitTriangles->v0.x, toSplitTriangles->v1.x, dXab, toSplitTrianglesCount + 1 );
	nmppsSub_32f ( toSplitTriangles->v0.y, toSplitTriangles->v1.y, dYab, toSplitTrianglesCount + 1 );
	float * edge1 = bufNf8;
	sumOfSquares( dXab, dYab, edge1, toSplitTrianglesCount );
//	nmppsMul_Mul_Add_32f( dXab, dXab, dYab, dYab, edge1, toSplitTrianglesCount );

	float * dXbc = dXab;
	float * dYbc = dYab;
	nmppsSub_32f ( toSplitTriangles->v1.x, toSplitTriangles->v2.x, dXbc, toSplitTrianglesCount + 1 );
	nmppsSub_32f ( toSplitTriangles->v1.y, toSplitTriangles->v2.y, dYbc, toSplitTrianglesCount + 1 );
	float * edge2 = bufNf9;
	sumOfSquares( dXbc, dYbc, edge2, toSplitTrianglesCount );
//	nmppsMul_Mul_Add_32f( dXbc, dXbc, dYbc, dYbc, edge2, toSplitTrianglesCount );

	float * dXac = dXab;
	float * dYac = dYab;
	nmppsSub_32f ( toSplitTriangles->v0.x, toSplitTriangles->v2.x, dXac, toSplitTrianglesCount + 1 );
	nmppsSub_32f ( toSplitTriangles->v0.y, toSplitTriangles->v2.y, dYac, toSplitTrianglesCount + 1 );	
	float * edge3 = bufNf10;
	sumOfSquares( dXac, dYac, edge3, toSplitTrianglesCount );
//	nmppsMul_Mul_Add_32f( dXac, dXac, dYac, dYac, edge3, toSplitTrianglesCount );

	int * maxEdgeArray = (int*)bufNf11;
	maxEdge( maxEdgeArray, edge1, edge2, edge3, toSplitTrianglesCount );

	float tempX;
	float tempY;
	for(int i = 0; i < toSplitTrianglesCount; ++i)
	{
		if( maxEdgeArray[i] == 2 )
		{
			tempX = toSplitTriangles->v2.x[i];
			tempY = toSplitTriangles->v2.y[i];
			toSplitTriangles->v2.x[i] = toSplitTriangles->v0.x[i];
			toSplitTriangles->v2.y[i] = toSplitTriangles->v0.y[i];
			toSplitTriangles->v0.x[i] = toSplitTriangles->v1.x[i];
			toSplitTriangles->v0.y[i] = toSplitTriangles->v1.y[i];
			toSplitTriangles->v1.x[i] = tempX;
			toSplitTriangles->v1.y[i] = tempY;
		}
		else if( maxEdgeArray[i] == 3 )
		{
			tempX = toSplitTriangles->v2.x[i];
			tempY = toSplitTriangles->v2.y[i];
			toSplitTriangles->v2.x[i] = toSplitTriangles->v1.x[i];
			toSplitTriangles->v2.y[i] = toSplitTriangles->v1.y[i];
			toSplitTriangles->v1.x[i] = tempX;
			toSplitTriangles->v1.y[i] = tempY;
		}
	}

	float constValue[2] = {0.5, 0.5};
	float * newVertexX = bufNf12;
	float * newVertexY = bufNf13;
	nmppsAdd_MulC_32f   ( toSplitTriangles->v0.x, toSplitTriangles->v1.x, newVertexX, constValue,  toSplitTrianglesCount + 1 );
	nmppsAdd_MulC_32f   ( toSplitTriangles->v0.y, toSplitTriangles->v1.y, newVertexY, constValue,  toSplitTrianglesCount + 1 );

	nmppsMerge_32f ( toSplitTriangles->v0.x, toSplitTriangles->v1.x, splittedTriangles->v0.x, toSplitTrianglesCount + 1 );
	nmppsMerge_32f ( toSplitTriangles->v0.y, toSplitTriangles->v1.y, splittedTriangles->v0.y, toSplitTrianglesCount + 1 );
	nmppsMerge_32f ( toSplitTriangles->v2.x, toSplitTriangles->v2.x, splittedTriangles->v1.x, toSplitTrianglesCount + 1 );
	nmppsMerge_32f ( toSplitTriangles->v2.y, toSplitTriangles->v2.y, splittedTriangles->v1.y, toSplitTrianglesCount + 1 );
	nmppsMerge_32f ( newVertexX,			 newVertexX,			 splittedTriangles->v2.x, toSplitTrianglesCount + 1 );
	nmppsMerge_32f ( newVertexY,			 newVertexY,			 splittedTriangles->v2.y, toSplitTrianglesCount + 1 );
	(*splittedTrianglesCount) = 2 * toSplitTrianglesCount;
}

extern "C" void triangulate(	TrianglePointers* srcVertex, int * srcCount,
						int maxWidth, int maxHeight,
						TrianglePointers* dstSuitableVertex, int * dstSuitableCount)
{
	int toSplitTrianglesCount = 0;

	int * flags = bufNi0;

	TrianglePointers toSplitTriangles;

	float * axNew = bufNf0;
	float * ayNew = bufNf1;
	float * bxNew = bufNf2;
	float * byNew = bufNf3;
	float * cxNew = bufNf4;
	float * cyNew = bufNf5;

	toSplitTriangles.v0.x = axNew;
	toSplitTriangles.v0.y = ayNew;
	toSplitTriangles.v1.x = bxNew;
	toSplitTriangles.v1.y = byNew;
	toSplitTriangles.v2.x = cxNew;
	toSplitTriangles.v2.y = cyNew;

	generateMasks( srcVertex, *srcCount, maxWidth, maxHeight, flags );

	sort( srcVertex, *srcCount, &toSplitTriangles, &toSplitTrianglesCount, dstSuitableVertex, dstSuitableCount, flags );
	
	split( &toSplitTriangles, toSplitTrianglesCount, srcVertex, srcCount );
}
