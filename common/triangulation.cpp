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
//generateMasks and split
float * bufNf6;
float * bufNf7;
float * bufNf8;
float * bufNf9;
float * bufNf10;
float * bufNf11;
float * bufNf12;
float * bufNf13;



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
	//generateMasks and split
	bufNf6 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf7 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf8 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf9 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf10 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf11 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf12 = (float*)malloc(maxTrianglesCount * sizeof(float));
	bufNf13 = (float*)malloc(maxTrianglesCount * sizeof(float));	
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
	//generateMasks and split
	free(bufNf6);
	free(bufNf7);
	free(bufNf8);
	free(bufNf9);
	free(bufNf10);
	free(bufNf11);
	free(bufNf12);
	free(bufNf13);
}

extern "C" void sumFlags( nm1 * srcVec, int * dstVec, int srcCount )
{
	for(int i = 0; i < srcCount; ++i)
	{
		dstVec[i] |= nmppsGet_1(srcVec, i);
	}
}

//extern "C" void sumFlags( int * flags, int * Flags, int srcCount )
//{
//	for(int i = 0; i < srcCount; ++i){
//		flags[i] 				|=  nmppsGetVal_1((nm1*)evenFlags,i);
//	}
//}

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

	int * evenFlagsInt = (int*)bufNf12;
	int * oddFlagsInt  = (int*)bufNf13;

	nmppsMerge_32f ( srcTriangles->v0.x, srcTriangles->v0.y, (float*)Axy, srcCount );
	nmppsMerge_32f ( srcTriangles->v1.x, srcTriangles->v1.y, (float*)Bxy, srcCount );
	nmppsMerge_32f ( srcTriangles->v2.x, srcTriangles->v2.y, (float*)Cxy, srcCount );

	nmppsSub_32f( (float*)Axy, (float*)Bxy, (float*)dAB, srcCount );
	nmppsSub_32f( (float*)Bxy, (float*)Cxy, (float*)dBC, srcCount );
	nmppsSub_32f( (float*)Axy, (float*)Cxy, (float*)dAC, srcCount );

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
	nmppsCmpGtC_v2nm32f (dAB, &limatationConstant, evenFlagsInt, 					   oddFlagsInt, 					  step, srcCount);
	nmppsCmpGtC_v2nm32f (dBC, &limatationConstant, evenFlagsInt + (srcCount / 32 + 2), oddFlagsInt + (srcCount / 32 + 2), step, srcCount);
	nmppsCmpGtC_v2nm32f (dAC, &limatationConstant, evenFlagsInt + (srcCount / 16 + 2), oddFlagsInt + (srcCount / 16 + 2), step, srcCount);

	for(int i = 0; i < srcCount / 32 + 1; ++i)
	{
		evenFlagsInt[i] |= evenFlagsInt[srcCount / 32 + 2 + i];
		evenFlagsInt[i] |= evenFlagsInt[srcCount / 16 + 2 + i];
		oddFlagsInt[i] |= oddFlagsInt[srcCount / 32 + 2 + i];
		oddFlagsInt[i] |= oddFlagsInt[srcCount / 16 + 2 + i];
		evenFlagsInt[i] |= oddFlagsInt[i];
	}
	
	sumFlags( evenFlagsInt, flags, srcCount );
}

extern "C" void sort( 	TrianglePointers * srcTriangles, int srcCount,
			TrianglePointers * toSplitTriangles, int * toSplitTrianglesCount,
			TrianglePointers * resultTriangles, int * resultCount,
			int * flags )
{
	(*toSplitTrianglesCount) = 0;
	int tempResultCount = *resultCount;
	int tempToSplitTrianglesCount = *toSplitTrianglesCount;
	for(int i = 0; i < srcCount; ++i)
	{
		if( flags[i] == 0 )
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

	for(int i = 0; i < maxTrianglesCount; ++i)
	{
		flags[i] = 0;
	}

	generateMasks( srcVertex, *srcCount, maxWidth, maxHeight, flags );

	sort( srcVertex, *srcCount, &toSplitTriangles, &toSplitTrianglesCount, dstSuitableVertex, dstSuitableCount, flags );
	
	split( &toSplitTriangles, toSplitTrianglesCount, srcVertex, srcCount );
}
