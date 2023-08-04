#include "math.h"
#include "stdio.h"
#include "stdlib.h"
//#include "memory.h"
#include "../../../include/primitive.h"
#include "../../../include/nmtype.h"
#include "nmpp.h"
//#include "VShell.h"

const int size = 4;
const int maximumDestinationSize = 128;
const int maximumHeight = 40;
const int maximumWidth  = 40;
static const int WIDTH  = 512;
static const int HEIGHT = 512;

struct point
{
	float x;
	float y;
	float z;

	point () { x = 0; y = 0; z = 0; }
};

void masks( TrianglePointers * srcTriangles, int srcCount, int maxWidth, int maxHeight, int * flags )
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

//	int * temporaryArrayEven = (int*)malloc((srcCount / 128 + 2) * sizeof(int));
//	int * temporaryArrayOdd  = (int*)malloc((srcCount / 128 + 2) * sizeof(int));

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
	/*
	for(int i = 0; i < srcCount / 128 + 2; ++i)
	{
		temporaryArrayEven[i] = evenFlagsInt[i];
		temporaryArrayOdd[i] = oddFlagsInt[i];
	}
	*/
	for(int i = 0; i < srcCount / 2; ++i)
	{
		flags[i] = ((evenFlagsInt[i / 32]) << (31 - i)) >> 31;
		flags[i + srcCount / 2] = ((oddFlagsInt[i / 32]) << (31 - i)) >> 31;
	}
	/*
	for(int i = 0; i < srcCount / 2; ++i)
	{
		printf("dXab Tr[%.3d] = %f; ", i * 2, dXab[i].v0);
		if( flags[i] == 0 )
			printf("0");
		else
			printf("1");
		printf("%d\n", temporaryArrayEven[i / 32] % 2);
		temporaryArrayEven[i / 32] /= 2;
		printf("dXab Tr[%.3d] = %f; ", i * 2 + 1, dXab[i].v1);
		if( flags[i + (srcCount / 2)] == 0 )
			printf("0");
		else
			printf("1");
		printf("%d\n", temporaryArrayOdd[i / 32] % 2);
		temporaryArrayOdd[i / 32] /= 2;
	}
	*/
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
//	free(temporaryArrayEven);
//	free(temporaryArrayOdd);
}

void sort( 	TrianglePointers * srcTriangles, int srcCount,
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

void squareSum( float * edgeArray, float * dX, float * dY, int edgeCount )
{
	for(int i = 0; i < edgeCount; ++i)
	{
		edgeArray[i] = dX[i] * dX[i] + dY[i] * dY[i];
	}
}

void maxEdge( int * maxEdgeArray, float * edge1, float * edge2, float * edge3, int edgeCount )
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

void split( TrianglePointers * toSplitTriangles, int toSplitTrianglesCount,
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

void triangulation(	TrianglePointers* srcVertex, int srcCount,
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

int main()
{
	TrianglePointers testResultTrianglesArray;
	int treatedCounter = 0;

	float axRes[maximumDestinationSize];
	float ayRes[maximumDestinationSize];
	float bxRes[maximumDestinationSize];
	float byRes[maximumDestinationSize];
	float cxRes[maximumDestinationSize];
	float cyRes[maximumDestinationSize];

	testResultTrianglesArray.v0.x = axRes;
	testResultTrianglesArray.v0.y = ayRes;
	testResultTrianglesArray.v1.x = bxRes;
	testResultTrianglesArray.v1.y = byRes;
	testResultTrianglesArray.v2.x = cxRes;
	testResultTrianglesArray.v2.y = cyRes;

	TrianglePointers testTrianglesArray;

	float ax[size];
	float ay[size];
	float bx[size];
	float by[size];
	float cx[size];
	float cy[size];

	testTrianglesArray.v0.x = ax;
	testTrianglesArray.v0.y = ay;
	testTrianglesArray.v1.x = bx;
	testTrianglesArray.v1.y = by;
	testTrianglesArray.v2.x = cx;
	testTrianglesArray.v2.y = cy;
	testTrianglesArray.v0.x[0] = 0;
	testTrianglesArray.v0.y[0] = 0;
	testTrianglesArray.v1.x[0] = 150;
	testTrianglesArray.v1.y[0] = 50;
	testTrianglesArray.v2.x[0] = 100;
	testTrianglesArray.v2.y[0] = 150;

	testTrianglesArray.v0.x[1] = 150;
	testTrianglesArray.v0.y[1] = 50;
	testTrianglesArray.v1.x[1] = 200;
	testTrianglesArray.v1.y[1] = 300;
	testTrianglesArray.v2.x[1] = 100;
	testTrianglesArray.v2.y[1] = 150;

	testTrianglesArray.v0.x[2] = 150;
	testTrianglesArray.v0.y[2] = 50;
	testTrianglesArray.v1.x[2] = 200;
	testTrianglesArray.v1.y[2] = 300;
	testTrianglesArray.v2.x[2] = 210;
	testTrianglesArray.v2.y[2] = 120;
	
	testTrianglesArray.v0.x[3] = 150;
	testTrianglesArray.v0.y[3] = 50;
	testTrianglesArray.v1.x[3] = 300;
	testTrianglesArray.v1.y[3] = 90;
	testTrianglesArray.v2.x[3] = 210;
	testTrianglesArray.v2.y[3] = 120;

	printf("\nGiven Triangles:");
	for(int i = 0; i < size; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testTrianglesArray.v0.x[i], testTrianglesArray.v0.y[i]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testTrianglesArray.v1.x[i], testTrianglesArray.v1.y[i]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testTrianglesArray.v2.x[i], testTrianglesArray.v2.y[i]);
	}
	

	triangulation( &testTrianglesArray, size, maximumWidth, maximumHeight, maximumDestinationSize, &testResultTrianglesArray, &treatedCounter );


	int resultCount = 0;
	if( size + treatedCounter > maximumDestinationSize )
		resultCount = maximumDestinationSize;
	else
		resultCount = size + treatedCounter;
	printf("\n\n%d Result Triangles:", resultCount);
	/*
	for(int i = 0; i < resultCount; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i]);
	}
	*/
	/*
	if(!VS_Init())
    	return 0;
	VS_CreateImage("Given Triangles", 0, WIDTH, HEIGHT, VS_RGB8, NULL);
	VS_CreateImage("Result Triangles", 1, WIDTH, HEIGHT, VS_RGB8, NULL);
	while(VS_Run())
	{
		for(int i = 0; i < size; ++i)
		{
			VS_Line(0, testTrianglesArray.v0.x[i], testTrianglesArray.v0.y[i], testTrianglesArray.v1.x[i], testTrianglesArray.v1.y[i], RGB(255, 255, 255));
			VS_Line(0, testTrianglesArray.v0.x[i], testTrianglesArray.v0.y[i], testTrianglesArray.v2.x[i], testTrianglesArray.v2.y[i], RGB(255, 255, 255));
			VS_Line(0, testTrianglesArray.v2.x[i], testTrianglesArray.v2.y[i], testTrianglesArray.v1.x[i], testTrianglesArray.v1.y[i], RGB(255, 255, 255));
		}

		for(int i = 0; i < resultCount; ++i)
		{
			VS_Line(1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i], testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i], RGB(255, 255, 255));
			VS_Line(1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i], testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i], RGB(255, 255, 255));
			VS_Line(1, testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i], testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i], RGB(255, 255, 255));
		}

		VS_Rectangle(0, 10, 300, 10 + maximumWidth, 300 + maximumHeight, RGB(255, 255, 255), RGB(0, 0, 0));
		VS_Rectangle(1, 10, 300, 10 + maximumWidth, 300 + maximumHeight, RGB(255, 255, 255), RGB(0, 0, 0));

		VS_Draw(VS_DRAW_ALL);
	}
	*/
	//-----------------------------------------------------------------------------------nmpp-test-------------
	/*
	int testsize = 128;
	v2nm32f * dXab = (v2nm32f*)malloc(testsize / 2 * sizeof(v2nm32f));
	for(int i = 0; i < testsize / 2; ++i)
	{
		dXab[i].v0 = i * 2;
		dXab[i].v1 = i * 2 + 1;
	}
//	dXab[3].v1 = 50.25;
//	dXab[1].v0 = 45.98;
//	dXab[35].v0 = 2.03;
//	dXab[34].v1 = 29.76;
	printf("\n");
	for(int i = 0; i < testsize / 2; ++i)
	{
		if( i % 16 == 0)
			printf("\n");
		printf("%f, %f\n", dXab[i].v0, dXab[i].v1);
	}
	
	v2nm32f constant[1];
	constant[0].v0 = 0;
	constant[0].v1 = 0;
	printf("Constant:\n");
	printf("%f, %f\n", constant[0].v0, constant[0].v1);


	int * evenFlagsInt = (int*)malloc((testsize / 128 + 2) * sizeof(int));
	int * oddFlagsInt  = (int*)malloc((testsize / 128 + 2) * sizeof(int));

	int * evenFlags = (int*)malloc(sizeof(int) * testsize / 2);
	int * oddFlags  = (int*)malloc(sizeof(int) * testsize / 2);

	int step = 1;
	nmppsCmpGtC_v2nm32f (dXab, constant, evenFlagsInt, oddFlagsInt, step, testsize / 2);
	
	printf("\nGtC Even:\n");
	for (int i = 0; i < testsize / 2; i++)
	{
		evenFlags[i] = ((evenFlagsInt[i / 32]) << (31 - i)) >> 31;
	}
	for(int i = 0; i < testsize / 2; ++i)
	{
		if( i % 16 == 0)
			printf(" ");
		if( evenFlags[i] == 0 )
			printf("0");
		else
			printf("1");
	}

	printf("\nGtC Odd:\n");
	for (int i = 0; i < testsize / 2; i++)
	{
		oddFlags[i] = ((oddFlagsInt[i / 32]) << (31 - i)) >> 31;
	}
	for(int i = 0; i < testsize / 2; ++i)
	{
		if( i % 16 == 0)
			printf(" ");
		if( oddFlags[i] == 0 )
			printf("0");
		else
			printf("1");
	}

	nmppsCmpLteC_v2nm32f (dXab, constant, evenFlagsInt, oddFlagsInt, step, testsize / 2);

	printf("\nLteC Even:\n");
	for (int i = 0; i < testsize / 2; i++)
	{
		evenFlags[i] = ((evenFlagsInt[i / 32]) << (31 - i)) >> 31;
	}
	for(int i = 0; i < testsize / 2; ++i)
	{
		if( i % 16 == 0)
			printf(" ");
		if( evenFlags[i] == 0 )
			printf("0");
		else
			printf("1");
	}

	printf("\nLteC Odd:\n");
	for (int i = 0; i < testsize / 2; i++)
	{
		oddFlags[i] = ((oddFlagsInt[i / 32]) << (31 - i)) >> 31;
	}
	for(int i = 0; i < testsize / 2; ++i)
	{
		if( i % 16 == 0)
			printf(" ");
		if( oddFlags[i] == 0 )
			printf("0");
		else
			printf("1");
	}
	printf("\n\n");

	free(dXab);
	free(evenFlagsInt);
	free(oddFlagsInt);
	free(evenFlags);
	free(oddFlags);
	*/

	return 0;
}

