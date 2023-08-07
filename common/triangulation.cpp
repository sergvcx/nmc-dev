#include "math.h"
#include "stdio.h"
#include "stdlib.h"
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
	/*
	printf("\nflags");
	for(int i = 0; i < srcCount; ++i)
	{
		if(i == 32)
			printf(" ");
		if( flags[i] == 0 )
			printf("0");
		else
			printf("1");
	}
	printf("\n\n\n");
	*/
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
	float * dXbc = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	float * dXac = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	float * dYab = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	float * dYbc = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	float * dYac = (float*)malloc(toSplitTrianglesCount * sizeof(float));

	for(int i = 0; i < toSplitTrianglesCount; ++i)
	{
		dXab[i] = toSplitTriangles->v0.x[i] - toSplitTriangles->v1.x[i];
		dXbc[i] = toSplitTriangles->v1.x[i] - toSplitTriangles->v2.x[i];
		dXac[i] = toSplitTriangles->v0.x[i] - toSplitTriangles->v2.x[i];
		dYab[i] = toSplitTriangles->v0.y[i] - toSplitTriangles->v1.y[i];
		dYbc[i] = toSplitTriangles->v1.y[i] - toSplitTriangles->v2.y[i];
		dYac[i] = toSplitTriangles->v0.y[i] - toSplitTriangles->v2.y[i];
	}

	int * maxEdgeArray = (int*)malloc(toSplitTrianglesCount * sizeof(int));
	float * edge1 = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	float * edge2 = (float*)malloc(toSplitTrianglesCount * sizeof(float));
	float * edge3 = (float*)malloc(toSplitTrianglesCount * sizeof(float));

	squareSum( edge1, dXab, dYab, toSplitTrianglesCount );
	squareSum( edge2, dXbc, dYbc, toSplitTrianglesCount );
	squareSum( edge3, dXac, dYac, toSplitTrianglesCount );
	maxEdge( maxEdgeArray, edge1, edge2, edge3, toSplitTrianglesCount );

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

	for(int i = 0; i < toSplitTrianglesCount; ++i)
	{
		temporary.x = (toSplitTriangles->v0.x[i] + toSplitTriangles->v1.x[i]) / 2;
		temporary.y = (toSplitTriangles->v0.y[i] + toSplitTriangles->v1.y[i]) / 2;
		
		splittedTriangles->v0.x[(*splittedTrianglesCount)] = toSplitTriangles->v0.x[i];
		splittedTriangles->v0.y[(*splittedTrianglesCount)] = toSplitTriangles->v0.y[i];
		splittedTriangles->v1.x[(*splittedTrianglesCount)] = toSplitTriangles->v2.x[i];
		splittedTriangles->v1.y[(*splittedTrianglesCount)] = toSplitTriangles->v2.y[i];
		splittedTriangles->v2.x[(*splittedTrianglesCount)] = temporary.x;
		splittedTriangles->v2.y[(*splittedTrianglesCount)] = temporary.y;

		splittedTriangles->v0.x[(*splittedTrianglesCount) + 1] = toSplitTriangles->v1.x[i];
		splittedTriangles->v0.y[(*splittedTrianglesCount) + 1] = toSplitTriangles->v1.y[i];
		splittedTriangles->v1.x[(*splittedTrianglesCount) + 1] = toSplitTriangles->v2.x[i];
		splittedTriangles->v1.y[(*splittedTrianglesCount) + 1] = toSplitTriangles->v2.y[i];
		splittedTriangles->v2.x[(*splittedTrianglesCount) + 1] = temporary.x;
		splittedTriangles->v2.y[(*splittedTrianglesCount) + 1] = temporary.y;

		(*splittedTrianglesCount) += 2;
		(*srcTreatedCount)++;
	}
	
	free(dXab);
	free(dXbc);
	free(dXac);
	free(dYab);
	free(dYbc);
	free(dYac);
	free(edge1);
	free(edge2);
	free(edge3);
	free(maxEdgeArray);
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

	for(int i = 0; i < srcCount; ++i)
	{
		trianglesArrayToCheck.v0.x[i] = (*srcVertex).v0.x[i];
		trianglesArrayToCheck.v0.y[i] = (*srcVertex).v0.y[i];
		trianglesArrayToCheck.v1.x[i] = (*srcVertex).v1.x[i];
		trianglesArrayToCheck.v1.y[i] = (*srcVertex).v1.y[i];
		trianglesArrayToCheck.v2.x[i] = (*srcVertex).v2.x[i];
		trianglesArrayToCheck.v2.y[i] = (*srcVertex).v2.y[i];
	}

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
		{
			checkForFitCount = 0;
			split( &toSplitTriangles, toSplitTrianglesCount, &trianglesArrayToCheck, &checkForFitCount, srcTreatedCount );
		}
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
