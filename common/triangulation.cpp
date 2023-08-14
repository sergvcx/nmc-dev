#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "../include/triangulation.h"
#include "../include/primitive.h"
#include "../include/nmtype.h"
#include "nmpp.h"

struct point
{
	float x;
	float y;
	float z;

	point () { x = 0; y = 0; z = 0; }
};

extern "C" void masks( TrianglePointers * srcTriangles, int srcCount, int maxWidth, int maxHeight, int * flags )
{
	v2nm32f * dXab = (v2nm32f*)malloc((srcCount / 2) * sizeof(v2nm32f));
	v2nm32f * dXbc = (v2nm32f*)malloc((srcCount / 2) * sizeof(v2nm32f));
	v2nm32f * dXac = (v2nm32f*)malloc((srcCount / 2) * sizeof(v2nm32f));
	v2nm32f * dYab = (v2nm32f*)malloc((srcCount / 2) * sizeof(v2nm32f));
	v2nm32f * dYbc = (v2nm32f*)malloc((srcCount / 2) * sizeof(v2nm32f));
	v2nm32f * dYac = (v2nm32f*)malloc((srcCount / 2) * sizeof(v2nm32f));

	v2nm32f maxWidthConstant;
	maxWidthConstant.v0 = maxWidth;
	maxWidthConstant.v1 = maxWidth;
	v2nm32f maxHeightConstant;
	maxHeightConstant.v0 = maxHeight;
	maxHeightConstant.v1 = maxHeight;

	int * evenFlagsInt = (int*)malloc((srcCount / 128 + 2) * sizeof(int));
	int * oddFlagsInt  = (int*)malloc((srcCount / 128 + 2) * sizeof(int));

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
	//sum masks into one
	int step = 1;

	nmppsCmpGtC_v2nm32f (dXab, &maxWidthConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	for(int i = 0; i < srcCount / 2; ++i)
	{
		flags[i] = ((evenFlagsInt[i / 32]) << (31 - i)) >> 31;
		flags[i + srcCount / 2] = ((oddFlagsInt[i / 32]) << (31 - i)) >> 31;
	}

	nmppsCmpGtC_v2nm32f (dXbc, &maxWidthConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	for(int i = 0; i < srcCount / 2; ++i)
	{
		flags[i] |= ((evenFlagsInt[i / 32]) << (31 - i)) >> 31;
		flags[i + srcCount / 2] |= ((oddFlagsInt[i / 32]) << (31 - i)) >> 31;
	}

	nmppsCmpGtC_v2nm32f (dXac, &maxWidthConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	for(int i = 0; i < srcCount / 2; ++i)
	{
		flags[i] |= ((evenFlagsInt[i / 32]) << (31 - i)) >> 31;
		flags[i + srcCount / 2] |= ((oddFlagsInt[i / 32]) << (31 - i)) >> 31;
	}

	nmppsCmpGtC_v2nm32f (dYab, &maxHeightConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	for(int i = 0; i < srcCount / 2; ++i)
	{
		flags[i] |= ((evenFlagsInt[i / 32]) << (31 - i)) >> 31;
		flags[i + srcCount / 2] |= ((oddFlagsInt[i / 32]) << (31 - i)) >> 31;
	}

	nmppsCmpGtC_v2nm32f (dYbc, &maxHeightConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	for(int i = 0; i < srcCount / 2; ++i)
	{
		flags[i] |= ((evenFlagsInt[i / 32]) << (31 - i)) >> 31;
		flags[i + srcCount / 2] |= ((oddFlagsInt[i / 32]) << (31 - i)) >> 31;
	}

	nmppsCmpGtC_v2nm32f (dYac, &maxHeightConstant, evenFlagsInt, oddFlagsInt, step, srcCount / 2);

	for(int i = 0; i < srcCount / 2; ++i)
	{
		flags[i] |= ((evenFlagsInt[i / 32]) << (31 - i)) >> 31;
		flags[i + srcCount / 2] |= ((oddFlagsInt[i / 32]) << (31 - i)) >> 31;
	}

	free(dXab);
	free(dXbc);
	free(dXac);
	free(dYab);
	free(dYbc);
	free(dYac);
	free(evenFlagsInt);
	free(oddFlagsInt);
}

extern "C" void sort( 	TrianglePointers * srcTriangles, int srcCount,
			TrianglePointers * toSplitTriangles, int * toSplitTrianglesCount,
			TrianglePointers * resultTriangles, int * resultCount,
			int maxDstSize, int * flags )
{
	(*toSplitTrianglesCount) = 0;
	for(int i = 0; i < srcCount / 2; ++i)
	{
		if( (*resultCount) == maxDstSize )
			break;
		if( flags[i] == 0 )
		{
			resultTriangles->v0.x[(*resultCount)] = srcTriangles->v0.x[i * 2];
			resultTriangles->v0.y[(*resultCount)] = srcTriangles->v0.y[i * 2];
			resultTriangles->v1.x[(*resultCount)] = srcTriangles->v1.x[i * 2];
			resultTriangles->v1.y[(*resultCount)] = srcTriangles->v1.y[i * 2];
			resultTriangles->v2.x[(*resultCount)] = srcTriangles->v2.x[i * 2];
			resultTriangles->v2.y[(*resultCount)] = srcTriangles->v2.y[i * 2];
			(*resultCount)++;
		}
		else
		{
			toSplitTriangles->v0.x[(*toSplitTrianglesCount)] = srcTriangles->v0.x[i * 2];
			toSplitTriangles->v0.y[(*toSplitTrianglesCount)] = srcTriangles->v0.y[i * 2];
			toSplitTriangles->v1.x[(*toSplitTrianglesCount)] = srcTriangles->v1.x[i * 2];
			toSplitTriangles->v1.y[(*toSplitTrianglesCount)] = srcTriangles->v1.y[i * 2];
			toSplitTriangles->v2.x[(*toSplitTrianglesCount)] = srcTriangles->v2.x[i * 2];
			toSplitTriangles->v2.y[(*toSplitTrianglesCount)] = srcTriangles->v2.y[i * 2];
			(*toSplitTrianglesCount)++;
		}
	}
	for(int i = 0; i < srcCount / 2; ++i)
	{
		if( (*resultCount) == maxDstSize )
			break;
		if( flags[i + (srcCount / 2)] == 0 )
		{
			resultTriangles->v0.x[(*resultCount)] = srcTriangles->v0.x[i * 2 + 1];
			resultTriangles->v0.y[(*resultCount)] = srcTriangles->v0.y[i * 2 + 1];
			resultTriangles->v1.x[(*resultCount)] = srcTriangles->v1.x[i * 2 + 1];
			resultTriangles->v1.y[(*resultCount)] = srcTriangles->v1.y[i * 2 + 1];
			resultTriangles->v2.x[(*resultCount)] = srcTriangles->v2.x[i * 2 + 1];
			resultTriangles->v2.y[(*resultCount)] = srcTriangles->v2.y[i * 2 + 1];
			(*resultCount)++;
		}
		else
		{
			toSplitTriangles->v0.x[(*toSplitTrianglesCount)] = srcTriangles->v0.x[i * 2 + 1];
			toSplitTriangles->v0.y[(*toSplitTrianglesCount)] = srcTriangles->v0.y[i * 2 + 1];
			toSplitTriangles->v1.x[(*toSplitTrianglesCount)] = srcTriangles->v1.x[i * 2 + 1];
			toSplitTriangles->v1.y[(*toSplitTrianglesCount)] = srcTriangles->v1.y[i * 2 + 1];
			toSplitTriangles->v2.x[(*toSplitTrianglesCount)] = srcTriangles->v2.x[i * 2 + 1];
			toSplitTriangles->v2.y[(*toSplitTrianglesCount)] = srcTriangles->v2.y[i * 2 + 1];
			(*toSplitTrianglesCount)++;
		}
	}
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
			TrianglePointers * splittedTriangles, int * splittedTrianglesCount,
			int * srcTreatedCount )
{
	float * dXab = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	float * dYab = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	nmppsSub_32f ( toSplitTriangles->v0.x, toSplitTriangles->v1.x, dXab, toSplitTrianglesCount );
	nmppsSub_32f ( toSplitTriangles->v0.y, toSplitTriangles->v1.y, dYab, toSplitTrianglesCount );
	float * edge1 = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	squareSum( edge1, dXab, dYab, toSplitTrianglesCount );
//	nmppsMul_Mul_Add_32f( dXab, dXab, dYab, dYab, edge1, toSplitTrianglesCount );
	free(dXab);
	free(dYab);

	float * dXbc = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	float * dYbc = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	nmppsSub_32f ( toSplitTriangles->v1.x, toSplitTriangles->v2.x, dXbc, toSplitTrianglesCount );
	nmppsSub_32f ( toSplitTriangles->v1.y, toSplitTriangles->v2.y, dYbc, toSplitTrianglesCount );
	float * edge2 = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	squareSum( edge2, dXbc, dYbc, toSplitTrianglesCount );
//	nmppsMul_Mul_Add_32f( dXbc, dXbc, dYbc, dYbc, edge2, toSplitTrianglesCount );
	free(dXbc);
	free(dYbc);

	float * dXac = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	float * dYac = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	nmppsSub_32f ( toSplitTriangles->v0.x, toSplitTriangles->v2.x, dXac, toSplitTrianglesCount );
	nmppsSub_32f ( toSplitTriangles->v0.y, toSplitTriangles->v2.y, dYac, toSplitTrianglesCount );	
	float * edge3 = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	squareSum( edge3, dXac, dYac, toSplitTrianglesCount );
//	nmppsMul_Mul_Add_32f( dXac, dXac, dYac, dYac, edge3, toSplitTrianglesCount );
	free(dXac);
	free(dYac);

	int * maxEdgeArray = (int*)malloc(toSplitTrianglesCount * sizeof(int));
	maxEdge( maxEdgeArray, edge1, edge2, edge3, toSplitTrianglesCount );
	free(edge1);
	free(edge2);
	free(edge3);

	point temporary = point();
	for(int i = 0; i < toSplitTrianglesCount; ++i)
	{
		if( maxEdgeArray[i] == 2 )
		{
			temporary.x = toSplitTriangles->v2.x[i];
			temporary.y = toSplitTriangles->v2.y[i];
			toSplitTriangles->v2.x[i] = toSplitTriangles->v0.x[i];
			toSplitTriangles->v2.y[i] = toSplitTriangles->v0.y[i];
			toSplitTriangles->v0.x[i] = toSplitTriangles->v1.x[i];
			toSplitTriangles->v0.y[i] = toSplitTriangles->v1.y[i];
			toSplitTriangles->v1.x[i] = temporary.x;
			toSplitTriangles->v1.y[i] = temporary.y;
		}
		else if( maxEdgeArray[i] == 3 )
		{
			temporary.x = toSplitTriangles->v2.x[i];
			temporary.y = toSplitTriangles->v2.y[i];
			toSplitTriangles->v2.x[i] = toSplitTriangles->v1.x[i];
			toSplitTriangles->v2.y[i] = toSplitTriangles->v1.y[i];
			toSplitTriangles->v1.x[i] = temporary.x;
			toSplitTriangles->v1.y[i] = temporary.y;
		}
	}
	free(maxEdgeArray);

	float constValue[2] = {0.5, 0.5};
	float * newVertexX = (float*)malloc((toSplitTrianglesCount + 1) * sizeof(float));
	float * newVertexY = (float*)malloc((toSplitTrianglesCount + 1) * sizeof(float));	
	nmppsAdd_MulC_32f   ( toSplitTriangles->v0.x, toSplitTriangles->v1.x, newVertexX, constValue,  toSplitTrianglesCount + 1 );
	nmppsAdd_MulC_32f   ( toSplitTriangles->v0.y, toSplitTriangles->v1.y, newVertexY, constValue,  toSplitTrianglesCount + 1);
	
	printf("\n");
	for(int i = 0; i < toSplitTrianglesCount; ++i)
		printf("\nA[%d]: %f; B[%d]: %f; NewP: %f\n", i, toSplitTriangles->v0.x[i], i, toSplitTriangles->v1.x[i], newVertexX[i]);
	printf("\n");

	nmppsMerge_32f ( toSplitTriangles->v0.x, toSplitTriangles->v1.x, splittedTriangles->v0.x, toSplitTrianglesCount );
	nmppsMerge_32f ( toSplitTriangles->v0.y, toSplitTriangles->v1.y, splittedTriangles->v0.y, toSplitTrianglesCount );
	nmppsMerge_32f ( toSplitTriangles->v2.x, toSplitTriangles->v2.x, splittedTriangles->v1.x, toSplitTrianglesCount );
	nmppsMerge_32f ( toSplitTriangles->v2.y, toSplitTriangles->v2.y, splittedTriangles->v1.y, toSplitTrianglesCount );
	nmppsMerge_32f ( newVertexX,			 newVertexX,			 splittedTriangles->v2.x, toSplitTrianglesCount );
	nmppsMerge_32f ( newVertexY,			 newVertexY,			 splittedTriangles->v2.y, toSplitTrianglesCount );
	(*splittedTrianglesCount) = 2 * toSplitTrianglesCount;
	(*srcTreatedCount) += toSplitTrianglesCount;
	free(newVertexX);
	free(newVertexY);
}

extern "C" void triangulation(	TrianglePointers* srcVertex, int srcCount,
						int maxWidth, int maxHeight,
						int maxDstSize, TrianglePointers* dstVertex,
						int* srcTreatedCount)
{
	int currentDstCount = 0;
	int checkForFitCount = srcCount;
	int toSplitTrianglesCount = 0;

	int * flags = (int*)malloc((maxDstSize) * 8);

	TrianglePointers trianglesArrayToCheck;

	float * ax = (float*)malloc(maxDstSize * sizeof(float));
	float * ay = (float*)malloc(maxDstSize * sizeof(float));
	float * bx = (float*)malloc(maxDstSize * sizeof(float));
	float * by = (float*)malloc(maxDstSize * sizeof(float));
	float * cx = (float*)malloc(maxDstSize * sizeof(float));
	float * cy = (float*)malloc(maxDstSize * sizeof(float));
	
	trianglesArrayToCheck.v0.x = ax;
	trianglesArrayToCheck.v0.y = ay;
	trianglesArrayToCheck.v1.x = bx;
	trianglesArrayToCheck.v1.y = by;
	trianglesArrayToCheck.v2.x = cx;
	trianglesArrayToCheck.v2.y = cy;
	
	nmppsCopy_32f ( (*srcVertex).v0.x, trianglesArrayToCheck.v0.x, srcCount );
	nmppsCopy_32f ( (*srcVertex).v1.x, trianglesArrayToCheck.v1.x, srcCount );
	nmppsCopy_32f ( (*srcVertex).v2.x, trianglesArrayToCheck.v2.x, srcCount );
	nmppsCopy_32f ( (*srcVertex).v0.y, trianglesArrayToCheck.v0.y, srcCount );
	nmppsCopy_32f ( (*srcVertex).v1.y, trianglesArrayToCheck.v1.y, srcCount );
	nmppsCopy_32f ( (*srcVertex).v2.y, trianglesArrayToCheck.v2.y, srcCount );

	TrianglePointers toSplitTriangles;

	float * axNew = (float*)malloc(maxDstSize * sizeof(float));
	float * ayNew = (float*)malloc(maxDstSize * sizeof(float));
	float * bxNew = (float*)malloc(maxDstSize * sizeof(float));
	float * byNew = (float*)malloc(maxDstSize * sizeof(float));
	float * cxNew = (float*)malloc(maxDstSize * sizeof(float));
	float * cyNew = (float*)malloc(maxDstSize * sizeof(float));

	toSplitTriangles.v0.x = axNew;
	toSplitTriangles.v0.y = ayNew;
	toSplitTriangles.v1.x = bxNew;
	toSplitTriangles.v1.y = byNew;
	toSplitTriangles.v2.x = cxNew;
	toSplitTriangles.v2.y = cyNew;

	while ( currentDstCount < maxDstSize && checkForFitCount != 0 )
	{
		for(int i = 0; i < maxDstSize; ++i)
		{
			flags[i] = 0;
		}

		masks( &trianglesArrayToCheck, checkForFitCount, maxWidth, maxHeight, flags );

		sort( &trianglesArrayToCheck, checkForFitCount, &toSplitTriangles, &toSplitTrianglesCount, dstVertex, &currentDstCount, maxDstSize, flags );

		if( currentDstCount < maxDstSize )
			split( &toSplitTriangles, toSplitTrianglesCount, &trianglesArrayToCheck, &checkForFitCount, srcTreatedCount );
	}
	
	free(flags);
	free(ax);
	free(ay);
	free(bx);
	free(by);
	free(cx);
	free(cy);
	free(axNew);
	free(ayNew);
	free(bxNew);
	free(byNew);
	free(cxNew);
	free(cyNew);
}
