#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "../../../include/primitive.h"
#include "../../../include/nmtype.h"
#include "nmpp.h"

struct point
{
	float x;
	float y;
	float z;

	point () { x = 0; y = 0; z = 0; }
};
struct triangle
{
	point a;
	point b;
	point c;
};

long long masks( TrianglePointers * srcTriangles, int srcCount, int maxWidth, int maxHeight, int * flags )
{
	float * dXab = (float*)malloc(srcCount * sizeof(float));
	float * dXbc = (float*)malloc(srcCount * sizeof(float));
	float * dXac = (float*)malloc(srcCount * sizeof(float));
	float * dYab = (float*)malloc(srcCount * sizeof(float));
	float * dYbc = (float*)malloc(srcCount * sizeof(float));
	float * dYac = (float*)malloc(srcCount * sizeof(float));
	
	float * constant = (float*)malloc(2 * sizeof(float));
	constant[0] = maxWidth;
	constant[1] = maxHeight;

	int * evenFlags = (int*)malloc((srcCount / 64) * sizeof(int));
	int * oddFlags = (int*)malloc((srcCount / 64) * sizeof(int));

	for(int i = 0; i < srcCount; ++i)
	{
		dXab[i] = abs(srcTriangles->v0.x[i] - srcTriangles->v1.x[i]);
		dXbc[i] = abs(srcTriangles->v1.x[i] - srcTriangles->v2.x[i]);
		dXac[i] = abs(srcTriangles->v0.x[i] - srcTriangles->v2.x[i]);
		dYab[i] = abs(srcTriangles->v0.y[i] - srcTriangles->v1.y[i]);
		dYbc[i] = abs(srcTriangles->v1.y[i] - srcTriangles->v2.y[i]);
		dYac[i] = abs(srcTriangles->v0.y[i] - srcTriangles->v2.y[i]);
	}
	//sum masks into one
	nmppsCmpLteC_v2nm32f (dXab, constant, evenFlags, oddFlags, 1, srcCount / 2);
	for(i = 0; i < srcCount / 64; ++i)
	{
		flags[i] = evenFlags[i];
	}
	for(i = srcCount / 64; i < srcCount / 32; ++i)
	{
		flags[i] = oddFlags[i];
	}
	nmppsCmpLteC_v2nm32f (dXbc, constant, evenFlags, oddFlags, 1, srcCount / 2);
	for(i = 0; i < srcCount / 64; ++i)
	{
		flags[i] |= evenFlags[i];
	}
	for(i = srcCount / 64; i < srcCount / 32; ++i)
	{
		flags[i] |= oddFlags[i];
	}
	nmppsCmpLteC_v2nm32f (dXac, constant, evenFlags, oddFlags, 1, srcCount / 2);
	for(i = 0; i < srcCount / 64; ++i)
	{
		flags[i] |= evenFlags[i];
	}
	for(i = srcCount / 64; i < srcCount / 32; ++i)
	{
		flags[i] |= oddFlags[i];
	}
	nmppsCmpLteC_v2nm32f (dYab, constant, evenFlags, oddFlags, 1, srcCount / 2);
	for(i = 0; i < srcCount / 64; ++i)
	{
		flags[i] |= evenFlags[i];
	}
	for(i = srcCount / 64; i < srcCount / 32; ++i)
	{
		flags[i] |= oddFlags[i];
	}
	nmppsCmpLteC_v2nm32f (dYab, constant, evenFlags, oddFlags, 1, srcCount / 2);
	for(i = 0; i < srcCount / 64; ++i)
	{
		flags[i] |= evenFlags[i];
	}
	for(i = srcCount / 64; i < srcCount / 32; ++i)
	{
		flags[i] |= oddFlags[i];
	}
	nmppsCmpLteC_v2nm32f (dYab, constant, evenFlags, oddFlags, 1, srcCount / 2);
	for(i = 0; i < srcCount / 64; ++i)
	{
		flags[i] |= evenFlags[i];
	}
	for(i = srcCount / 64; i < srcCount / 32; ++i)
	{
		flags[i] |= oddFlags[i];
	}

	free(dXab);
	free(dXbc);
	free(dXac);
	free(dYab);
	free(dYbc);
	free(dYac);
	free(constant);
	free(oddFlags);
	free(evenFlags);
}

void sort( 	TrianglePointers * srcTriangles, int srcCount,
			TrianglePointers * toSplitTriangles, int * toSplitTrianglesCount,
			TrianglePointers * resultTriangles, int * resultCount,
			int * flags )
{
	for(int i = 0; i < srcCount / 2; ++i)
	{
		if( (flags[i / 32] << i) >> 31 )
		{
			toSplitTriangles->v0.x[(*toSplitTrianglesCount)] = srcTriangles->v0.x[i * 2];
			toSplitTriangles->v0.y[(*toSplitTrianglesCount)] = srcTriangles->v0.y[i * 2];
			toSplitTriangles->v1.x[(*toSplitTrianglesCount)] = srcTriangles->v1.x[i * 2];
			toSplitTriangles->v1.y[(*toSplitTrianglesCount)] = srcTriangles->v1.y[i * 2];
			toSplitTriangles->v2.x[(*toSplitTrianglesCount)] = srcTriangles->v2.x[i * 2];
			toSplitTriangles->v2.y[(*toSplitTrianglesCount)] = srcTriangles->v2.y[i * 2];
			(*toSplitTrianglesCount)++;
		}
		else
		{
			resultTriangles->v0.x[(*resultCount)] = srcTriangles->v0.x[i * 2];
			resultTriangles->v0.y[(*resultCount)] = srcTriangles->v0.y[i * 2];
			resultTriangles->v1.x[(*resultCount)] = srcTriangles->v1.x[i * 2];
			resultTriangles->v1.y[(*resultCount)] = srcTriangles->v1.y[i * 2];
			resultTriangles->v2.x[(*resultCount)] = srcTriangles->v2.x[i * 2];
			resultTriangles->v2.y[(*resultCount)] = srcTriangles->v2.y[i * 2];
			(*resultCount)++;
		}
	}
	for(int i = 0; i < srcCount / 2; ++i)
	{
		if( (flags[i / 32] << i) >> 31 )
		{
			toSplitTriangles->v0.x[(*toSplitTrianglesCount)] = srcTriangles->v0.x[i * 2 + 1];
			toSplitTriangles->v0.y[(*toSplitTrianglesCount)] = srcTriangles->v0.y[i * 2 + 1];
			toSplitTriangles->v1.x[(*toSplitTrianglesCount)] = srcTriangles->v1.x[i * 2 + 1];
			toSplitTriangles->v1.y[(*toSplitTrianglesCount)] = srcTriangles->v1.y[i * 2 + 1];
			toSplitTriangles->v2.x[(*toSplitTrianglesCount)] = srcTriangles->v2.x[i * 2 + 1];
			toSplitTriangles->v2.y[(*toSplitTrianglesCount)] = srcTriangles->v2.y[i * 2 + 1];
			(*toSplitTrianglesCount)++;
		}
		else
		{
			resultTriangles->v0.x[(*resultCount)] = srcTriangles->v0.x[i * 2 + 1];
			resultTriangles->v0.y[(*resultCount)] = srcTriangles->v0.y[i * 2 + 1];
			resultTriangles->v1.x[(*resultCount)] = srcTriangles->v1.x[i * 2 + 1];
			resultTriangles->v1.y[(*resultCount)] = srcTriangles->v1.y[i * 2 + 1];
			resultTriangles->v2.x[(*resultCount)] = srcTriangles->v2.x[i * 2 + 1];
			resultTriangles->v2.y[(*resultCount)] = srcTriangles->v2.y[i * 2 + 1];
			(*resultCount)++;
		}
	}
}

float squareSum( float * edgeArray, float * dX, float * dY, int edgeCount )
{
	for(int i = 0; i < edgeCount; ++i)
	{
		edgeArray[i] = dX[i] * dX[i] + dY[i] * dY[i];
	}
}

int maxEdge( int * maxEdgeArray, float * edge1, float * edge2, float * edge3, int edgeCount )
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
			TrianglePointers * splittedTriangles, int * splittedTrianglesCount )
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
		temporary.x = (toSplitTriangles.a.x + toSplitTriangles.b.x) / 2;
		temporary.y = (toSplitTriangles.a.y + toSplitTriangles.b.y) / 2;

		splittedTriangles.v0.x[splittedTrianglesCount] = toSplitTriangles.a.x;
		splittedTriangles.v0.y[splittedTrianglesCount] = toSplitTriangles.a.y;
		splittedTriangles.v1.x[splittedTrianglesCount] = toSplitTriangles.c.x;
		splittedTriangles.v1.y[splittedTrianglesCount] = toSplitTriangles.c.y;
		splittedTriangles.v2.x[splittedTrianglesCount] = temporary.x;
		splittedTriangles.v2.y[splittedTrianglesCount] = temporary.y;

		splittedTriangles.v0.x[splittedTrianglesCount + 1] = toSplitTriangles.b.x;
		splittedTriangles.v0.y[splittedTrianglesCount + 1] = toSplitTriangles.b.y;
		splittedTriangles.v1.x[splittedTrianglesCount + 1] = toSplitTriangles.c.x;
		splittedTriangles.v1.y[splittedTrianglesCount + 1] = toSplitTriangles.c.y;
		splittedTriangles.v2.x[splittedTrianglesCount + 1] = temporary.x;
		splittedTriangles.v2.y[splittedTrianglesCount + 1] = temporary.y;

		(*splittedTrianglesCount) += 2;
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
	
	int * flags = (int*)malloc((maxDstSize / 32) * sizeof(int));

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

	while ( currentDstCount <= maxDstSize && checkForFitCount != 0 )
	{
		masks( trianglesArrayToCheck, checkForFitCount, maxWidth, maxHeight, flags );

		sort( trianglesArrayToCheck, checkForFitCount, toSplitTriangles, toSplitTrianglesCount, dstVertex, currentDstCount, flags );

		checkForFitCount = 0;

		if( toSplitTrianglesCount != 0 )
			split( toSplitTriangles, toSplitTrianglesCount, trianglesArrayToCheck, checkForFitCount );
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

const int size = 2;
const int maximumDestinationSize = 8;

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
	testTrianglesArray.v1.x[0] = 3;
	testTrianglesArray.v1.y[0] = 1;
	testTrianglesArray.v2.x[0] = 2;
	testTrianglesArray.v2.y[0] = 3;

	testTrianglesArray.v0.x[1] = 3;
	testTrianglesArray.v0.y[1] = 2;
	testTrianglesArray.v1.x[1] = 4;
	testTrianglesArray.v1.y[1] = 6;
	testTrianglesArray.v2.x[1] = 5;
	testTrianglesArray.v2.y[1] = 1;

	printf("\nGiven Triangle:");
	for(int i = 0; i < size; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testTrianglesArray.v0.x[i], testTrianglesArray.v0.y[i]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testTrianglesArray.v1.x[i], testTrianglesArray.v1.y[i]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testTrianglesArray.v2.x[i], testTrianglesArray.v2.y[i]);
	}

	triangulation( &testTrianglesArray, size, 2, 2, maximumDestinationSize, &testResultTrianglesArray, &treatedCounter );

	printf("\n\nResult Triangles:");
	for(int i = 0; i < size + treatedCounter; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i]);
	}
	

	return 0;
}

