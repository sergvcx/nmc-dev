#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "triangulation.h"
#include "primitive.h"
#include "nmtype.h"
#include "nmpp.h"
#include "nmassert.h"

int maxTrianglesCount = 256;
//triangulate
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
//generateMasks
v2nm32f * bufNf12;
v2nm32f * bufNf13;
v2nm32f * bufNf14;
v2nm32f * bufNf15;
v2nm32f * bufNf16;
v2nm32f * bufNf17;
int * bufFlagsEven;
int * bufFlagsOdd;
//split
float * bufDeltaNf0;
float * bufDeltaNf1;
float * bufEdgeNf0;
float * bufEdgeNf1;
float * bufEdgeNf2;
int * bufMaxEdgeNi;
float * bufNf18;
float * bufNf19;



extern "C" void triangulationInit()
{
	//triangulate
	bufNi0 = (int*)malloc(maxTrianglesCount * sizeof(int));
	bufNf0 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf1 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf2 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf3 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf4 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf5 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf6 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf7 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf8 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf9 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf10 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf11 = (float*)malloc(maxTrianglesCount * sizeof(float));
	//generateMasks
	bufNf12 = (v2nm32f*)malloc((maxTrianglesCount / 2) * sizeof(v2nm32f));
	bufNf13 = (v2nm32f*)malloc((maxTrianglesCount / 2) * sizeof(v2nm32f));
	bufNf14 = (v2nm32f*)malloc((maxTrianglesCount / 2) * sizeof(v2nm32f));
	bufNf15 = (v2nm32f*)malloc((maxTrianglesCount / 2) * sizeof(v2nm32f));
	bufNf16 = (v2nm32f*)malloc((maxTrianglesCount / 2) * sizeof(v2nm32f));
	bufNf17 = (v2nm32f*)malloc((maxTrianglesCount / 2) * sizeof(v2nm32f));
	bufFlagsEven = (int*)malloc((maxTrianglesCount / 64 + 2) * sizeof(int));
	bufFlagsOdd = (int*)malloc((maxTrianglesCount / 64 + 2) * sizeof(int));
	//split
	bufDeltaNf0 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufDeltaNf1 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufEdgeNf0 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufEdgeNf1 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufEdgeNf2 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufMaxEdgeNi = (int*)malloc(maxTrianglesCount * sizeof(int));
	bufNf18 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf19 = (float*)malloc(maxTrianglesCount * sizeof(float));	
}

extern "C" void triangulationFree()
{
	//triangulate
	free(bufNi0);
	free(bufNf0);
	free(bufNf1);
	free(bufNf2);
	free(bufNf3);
	free(bufNf4);
	free(bufNf5);
	free(bufNf6);
	free(bufNf7);
	free(bufNf8);
	free(bufNf9);
	free(bufNf10);
	free(bufNf11);
	//generateMasks
	free(bufNf12);
	free(bufNf13);
	free(bufNf14);
	free(bufNf15);
	free(bufNf16);
	free(bufNf17);
	free(bufFlagsEven);
	free(bufFlagsOdd);
	//split
	free(bufDeltaNf0);
	free(bufDeltaNf1);
	free(bufEdgeNf0);
	free(bufEdgeNf1);
	free(bufEdgeNf2);
	free(bufMaxEdgeNi);
	free(bufNf18);
	free(bufNf19);
}

extern "C" void sumFlags( int * flags, int * evenFlags, int * oddFlags, int srcCount )
{
	for(int i = 0; i < srcCount / 2; ++i)
	{
		flags[i] 				|= ((evenFlags[i / 32]) << (31 - i)) >> 31;
		flags[i + srcCount / 2] |= (( oddFlags[i / 32]) << (31 - i)) >> 31;
	}
}

extern "C" void generateMasks( TrianglePointers * srcTriangles, int srcCount, int maxWidth, int maxHeight, int * flags )
{
	v2nm32f * dXab = bufNf12;
	v2nm32f * dXbc = bufNf13;
	v2nm32f * dXac = bufNf14;
	v2nm32f * dYab = bufNf15;
	v2nm32f * dYbc = bufNf16;
	v2nm32f * dYac = bufNf17;

	v2nm32f maxWidthConstant;
	maxWidthConstant.v0 = maxWidth;
	maxWidthConstant.v1 = maxWidth;
	v2nm32f maxHeightConstant;
	maxHeightConstant.v0 = maxHeight;
	maxHeightConstant.v1 = maxHeight;

	int * evenFlagsInt = bufFlagsEven;
	int * oddFlagsInt  = bufFlagsOdd;

	for(int i = 0; i < srcCount / 2; ++i)
	{
		dXab[i].v0 = abs(srcTriangles->v0.x[i * 2] - srcTriangles->v1.x[i * 2]);
		dXab[i].v1 = abs(srcTriangles->v0.x[i * 2 + 1] - srcTriangles->v1.x[i * 2 + 1]);
		dXbc[i].v0 = abs(srcTriangles->v1.x[i * 2] - srcTriangles->v2.x[i * 2]);
		dXbc[i].v1 = abs(srcTriangles->v1.x[i * 2 + 1] - srcTriangles->v2.x[i * 2 + 1]);
		dXac[i].v0 = abs(srcTriangles->v0.x[i * 2] - srcTriangles->v2.x[i * 2]);
		dXac[i].v1 = abs(srcTriangles->v0.x[i * 2 + 1] - srcTriangles->v2.x[i * 2 + 1]);
		dYab[i].v0 = abs(srcTriangles->v0.y[i * 2] - srcTriangles->v1.y[i * 2]);
		dYab[i].v1 = abs(srcTriangles->v0.y[i * 2 + 1] - srcTriangles->v1.y[i * 2 + 1]);
		dYbc[i].v0 = abs(srcTriangles->v1.y[i * 2] - srcTriangles->v2.y[i * 2]);
		dYbc[i].v1 = abs(srcTriangles->v1.y[i * 2 + 1] - srcTriangles->v2.y[i * 2 + 1]);
		dYac[i].v0 = abs(srcTriangles->v0.y[i * 2] - srcTriangles->v2.y[i * 2]);
		dYac[i].v1 = abs(srcTriangles->v0.y[i * 2 + 1] - srcTriangles->v2.y[i * 2 + 1]);
	}

	int step = 1;

	nmppsCmpGtC_v2nm32f (dXab, &maxWidthConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	sumFlags( flags, evenFlagsInt, oddFlagsInt, srcCount );

	nmppsCmpGtC_v2nm32f (dXbc, &maxWidthConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	sumFlags( flags, evenFlagsInt, oddFlagsInt, srcCount );

	nmppsCmpGtC_v2nm32f (dXac, &maxWidthConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	sumFlags( flags, evenFlagsInt, oddFlagsInt, srcCount );

	nmppsCmpGtC_v2nm32f (dYab, &maxHeightConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	sumFlags( flags, evenFlagsInt, oddFlagsInt, srcCount );

	nmppsCmpGtC_v2nm32f (dYbc, &maxHeightConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	sumFlags( flags, evenFlagsInt, oddFlagsInt, srcCount );

	nmppsCmpGtC_v2nm32f (dYac, &maxHeightConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	sumFlags( flags, evenFlagsInt, oddFlagsInt, srcCount );
}

extern "C" void sort( 	TrianglePointers * srcTriangles, int srcCount,
			TrianglePointers * toSplitTriangles, int * toSplitTrianglesCount,
			TrianglePointers * resultTriangles, int * resultCount,
			int * flags )
{
	(*toSplitTrianglesCount) = 0;
	int tempResultCount = *resultCount;
	int tempToSplitTrianglesCount = *toSplitTrianglesCount;
	for(int i = 0; i < srcCount / 2; ++i)
	{
		if( flags[i] == 0 )
		{
			resultTriangles->v0.x[tempResultCount] = srcTriangles->v0.x[i * 2];
			resultTriangles->v0.y[tempResultCount] = srcTriangles->v0.y[i * 2];
			resultTriangles->v1.x[tempResultCount] = srcTriangles->v1.x[i * 2];
			resultTriangles->v1.y[tempResultCount] = srcTriangles->v1.y[i * 2];
			resultTriangles->v2.x[tempResultCount] = srcTriangles->v2.x[i * 2];
			resultTriangles->v2.y[tempResultCount] = srcTriangles->v2.y[i * 2];
			tempResultCount++;
		}
		else
		{
			toSplitTriangles->v0.x[tempToSplitTrianglesCount] = srcTriangles->v0.x[i * 2];
			toSplitTriangles->v0.y[tempToSplitTrianglesCount] = srcTriangles->v0.y[i * 2];
			toSplitTriangles->v1.x[tempToSplitTrianglesCount] = srcTriangles->v1.x[i * 2];
			toSplitTriangles->v1.y[tempToSplitTrianglesCount] = srcTriangles->v1.y[i * 2];
			toSplitTriangles->v2.x[tempToSplitTrianglesCount] = srcTriangles->v2.x[i * 2];
			toSplitTriangles->v2.y[tempToSplitTrianglesCount] = srcTriangles->v2.y[i * 2];
			tempToSplitTrianglesCount++;
		}
		if( flags[i + (srcCount / 2)] == 0 )
		{
			resultTriangles->v0.x[tempResultCount] = srcTriangles->v0.x[i * 2 + 1];
			resultTriangles->v0.y[tempResultCount] = srcTriangles->v0.y[i * 2 + 1];
			resultTriangles->v1.x[tempResultCount] = srcTriangles->v1.x[i * 2 + 1];
			resultTriangles->v1.y[tempResultCount] = srcTriangles->v1.y[i * 2 + 1];
			resultTriangles->v2.x[tempResultCount] = srcTriangles->v2.x[i * 2 + 1];
			resultTriangles->v2.y[tempResultCount] = srcTriangles->v2.y[i * 2 + 1];
			tempResultCount++;
		}
		else
		{
			toSplitTriangles->v0.x[tempToSplitTrianglesCount] = srcTriangles->v0.x[i * 2 + 1];
			toSplitTriangles->v0.y[tempToSplitTrianglesCount] = srcTriangles->v0.y[i * 2 + 1];
			toSplitTriangles->v1.x[tempToSplitTrianglesCount] = srcTriangles->v1.x[i * 2 + 1];
			toSplitTriangles->v1.y[tempToSplitTrianglesCount] = srcTriangles->v1.y[i * 2 + 1];
			toSplitTriangles->v2.x[tempToSplitTrianglesCount] = srcTriangles->v2.x[i * 2 + 1];
			toSplitTriangles->v2.y[tempToSplitTrianglesCount] = srcTriangles->v2.y[i * 2 + 1];
			tempToSplitTrianglesCount++;
		}
	}
	*resultCount = tempResultCount;
	*toSplitTrianglesCount = tempToSplitTrianglesCount;
}

extern "C" void squareSum( float * edgeArray, float * dX, float * dY, int edgeCount )
{
	for(int i = 0; i < edgeCount; ++i)
	{
		edgeArray[i] = dX[i] * dX[i] + dY[i] * dY[i];
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
	float * dXab = bufDeltaNf0;
	float * dYab = bufDeltaNf1;
	nmppsSub_32f ( toSplitTriangles->v0.x, toSplitTriangles->v1.x, dXab, toSplitTrianglesCount + 1 );
	nmppsSub_32f ( toSplitTriangles->v0.y, toSplitTriangles->v1.y, dYab, toSplitTrianglesCount + 1 );
	float * edge1 = bufEdgeNf0;
	squareSum( edge1, dXab, dYab, toSplitTrianglesCount );
//	nmppsMul_Mul_Add_32f( dXab, dXab, dYab, dYab, edge1, toSplitTrianglesCount );

	float * dXbc = dXab;
	float * dYbc = dYab;
	nmppsSub_32f ( toSplitTriangles->v1.x, toSplitTriangles->v2.x, dXbc, toSplitTrianglesCount + 1 );
	nmppsSub_32f ( toSplitTriangles->v1.y, toSplitTriangles->v2.y, dYbc, toSplitTrianglesCount + 1 );
	float * edge2 = bufEdgeNf1;
	squareSum( edge2, dXbc, dYbc, toSplitTrianglesCount );
//	nmppsMul_Mul_Add_32f( dXbc, dXbc, dYbc, dYbc, edge2, toSplitTrianglesCount );

	float * dXac = dXab;
	float * dYac = dYab;
	nmppsSub_32f ( toSplitTriangles->v0.x, toSplitTriangles->v2.x, dXac, toSplitTrianglesCount + 1 );
	nmppsSub_32f ( toSplitTriangles->v0.y, toSplitTriangles->v2.y, dYac, toSplitTrianglesCount + 1 );	
	float * edge3 = bufEdgeNf2;
	squareSum( edge3, dXac, dYac, toSplitTrianglesCount );
//	nmppsMul_Mul_Add_32f( dXac, dXac, dYac, dYac, edge3, toSplitTrianglesCount );

	int * maxEdgeArray = bufMaxEdgeNi;
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
	float * newVertexX = bufNf18;
	float * newVertexY = bufNf19;
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

	float * axNew = bufNf6;
	float * ayNew = bufNf7;
	float * bxNew = bufNf8;
	float * byNew = bufNf9;
	float * cxNew = bufNf10;
	float * cyNew = bufNf11;

	toSplitTriangles.v0.x = axNew;
	toSplitTriangles.v0.y = ayNew;
	toSplitTriangles.v1.x = bxNew;
	toSplitTriangles.v1.y = byNew;
	toSplitTriangles.v2.x = cxNew;
	toSplitTriangles.v2.y = cyNew;

	for(int i = 0; i < maxTrianglesCount; ++i)
	{
		flags[i] = 0;
	}

	generateMasks( srcVertex, *srcCount, maxWidth, maxHeight, flags );
	
	sort( srcVertex, *srcCount, &toSplitTriangles, &toSplitTrianglesCount, srcVertex, dstSuitableCount, flags );
	
	split( &toSplitTriangles, toSplitTrianglesCount, srcVertex, srcCount );
}
