#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "../../../include/primitive.h"
#include "../../../include/nmtype.h"

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

bool isFit( triangle srcTriangle, int maxHeight, int maxWidth)
{
	//возможно нахождение попарных максимумов будет дольше или так же по времени, что и проверка большего в 2 раза количества условий
	/*
	if(	max(a.x, b.x) - min(a.x, b.x) <= maxWidth &&
		max(b.x, c.x) - min(b.x, c.x) <= maxWidth &&
		max(a.x, c.x) - min(a.x, c.x) <= maxWidth &&
		max(a.x, b.x) - min(a.x, b.x) <= maxHeight &&
		max(b.x, c.x) - min(b.x, c.x) <= maxHeight &&
		max(a.x, c.x) - min(a.x, c.x) <= maxHeight
	)
	if(	srcTriangle.a.x - srcTriangle.b.x <= maxWidth &&
		srcTriangle.b.x - srcTriangle.a.x <= maxWidth &&
		srcTriangle.b.x - srcTriangle.c.x <= maxWidth &&
		srcTriangle.c.x - srcTriangle.b.x <= maxWidth &&
		srcTriangle.a.x - srcTriangle.c.x <= maxWidth &&
		srcTriangle.c.x - srcTriangle.a.x <= maxWidth &&
		srcTriangle.a.y - srcTriangle.b.y <= maxHeight &&
		srcTriangle.b.y - srcTriangle.a.y <= maxHeight &&
		srcTriangle.b.y - srcTriangle.c.y <= maxHeight &&
		srcTriangle.c.y - srcTriangle.b.y <= maxHeight &&
		srcTriangle.a.y - srcTriangle.c.y <= maxHeight &&
		srcTriangle.c.y - srcTriangle.a.y <= maxHeight
	)
	*/
	if(	abs( srcTriangle.a.x - srcTriangle.b.x ) <= maxWidth &&
		abs( srcTriangle.b.x - srcTriangle.c.x ) <= maxWidth &&
		abs( srcTriangle.c.x - srcTriangle.a.x ) <= maxWidth &&
		abs( srcTriangle.a.y - srcTriangle.b.y ) <= maxHeight &&
		abs( srcTriangle.b.y - srcTriangle.c.y ) <= maxHeight &&
		abs( srcTriangle.c.y - srcTriangle.a.y ) <= maxHeight
	)
		return true;
	
	return false;
}

int maxEdge( float edge1, float edge2, float edge3 )
{
	if( edge1 > edge2 )
		if( edge1 > edge3 )
			return 1;
		else
			return 3;
	else
		if( edge2 > edge3 )
			return 2;
		else
			return 3;
}

void partition( triangle triangleToPart, TrianglePointers* newTriangles, int newTrianglesIndex )
{
	float edge1 = 0;
	float edge2 = 0;
	float edge3 = 0;
	int maximumEdge = 0;
	point newVertex;

	edge1 = pow(( triangleToPart.a.x - triangleToPart.b.x ), 2) + pow(( triangleToPart.a.y - triangleToPart.b.y ), 2);
//	printf("\nedge1 %f\n", edge1);
	edge2 = pow(( triangleToPart.b.x - triangleToPart.c.x ), 2) + pow(( triangleToPart.b.y - triangleToPart.c.y ), 2);
//	printf("\nedge2 %f\n", edge2);
	edge3 = pow(( triangleToPart.a.x - triangleToPart.c.x ), 2) + pow(( triangleToPart.a.y - triangleToPart.c.y ), 2);
//	printf("\nedge3 %f\n", edge3);

	maximumEdge = maxEdge( edge1, edge2, edge3 );

	if( maximumEdge == 1 )
	{
		newVertex.x = (triangleToPart.a.x + triangleToPart.b.x) / 2;
		newVertex.y = (triangleToPart.a.y + triangleToPart.b.y) / 2;
//		newVertex.z = (triangleToPart.a.z + triangleToPart.b.z) / 2;

		(*newTriangles).v0.x[newTrianglesIndex] = triangleToPart.a.x;
		(*newTriangles).v0.y[newTrianglesIndex] = triangleToPart.a.y;
//		(*newTriangles).v0.z[newTrianglesIndex] = triangleToPart.a.z;
		(*newTriangles).v1.x[newTrianglesIndex] = triangleToPart.c.x;
		(*newTriangles).v1.y[newTrianglesIndex] = triangleToPart.c.y;
//		(*newTriangles).v1.z[newTrianglesIndex] = triangleToPart.c.z;
		(*newTriangles).v2.x[newTrianglesIndex] = newVertex.x;
		(*newTriangles).v2.y[newTrianglesIndex] = newVertex.y;
//		(*newTriangles).v2.z[newTrianglesIndex] = newVertex.z;

		(*newTriangles).v0.x[newTrianglesIndex + 1] = triangleToPart.b.x;
		(*newTriangles).v0.y[newTrianglesIndex + 1] = triangleToPart.b.y;
//		(*newTriangles).v0.z[newTrianglesIndex + 1] = triangleToPart.b.z;
		(*newTriangles).v1.x[newTrianglesIndex + 1] = triangleToPart.c.x;
		(*newTriangles).v1.y[newTrianglesIndex + 1] = triangleToPart.c.y;
//		(*newTriangles).v1.z[newTrianglesIndex + 1] = triangleToPart.c.z;
		(*newTriangles).v2.x[newTrianglesIndex + 1] = newVertex.x;
		(*newTriangles).v2.y[newTrianglesIndex + 1] = newVertex.y;
//		(*newTriangles).v2.z[newTrianglesIndex + 1] = newVertex.z;
	}
	else if ( maximumEdge == 2 )
	{
		newVertex.x = (triangleToPart.c.x + triangleToPart.b.x) / 2;
		newVertex.y = (triangleToPart.c.y + triangleToPart.b.y) / 2;
//		newVertex.z = (triangleToPart.c.z + triangleToPart.b.z) / 2;

		(*newTriangles).v0.x[newTrianglesIndex] = triangleToPart.a.x;
		(*newTriangles).v0.y[newTrianglesIndex] = triangleToPart.a.y;
//		(*newTriangles).v0.z[newTrianglesIndex] = triangleToPart.a.z;
		(*newTriangles).v1.x[newTrianglesIndex] = triangleToPart.b.x;
		(*newTriangles).v1.y[newTrianglesIndex] = triangleToPart.b.y;
//		(*newTriangles).v1.z[newTrianglesIndex] = triangleToPart.b.z;
		(*newTriangles).v2.x[newTrianglesIndex] = newVertex.x;
		(*newTriangles).v2.y[newTrianglesIndex] = newVertex.y;
//		(*newTriangles).v2.z[newTrianglesIndex] = newVertex.z;

		(*newTriangles).v0.x[newTrianglesIndex + 1] = triangleToPart.a.x;
		(*newTriangles).v0.y[newTrianglesIndex + 1] = triangleToPart.a.y;
//		(*newTriangles).v0.z[newTrianglesIndex + 1] = triangleToPart.a.z;
		(*newTriangles).v1.x[newTrianglesIndex + 1] = triangleToPart.c.x;
		(*newTriangles).v1.y[newTrianglesIndex + 1] = triangleToPart.c.y;
//		(*newTriangles).v1.z[newTrianglesIndex + 1] = triangleToPart.c.z;
		(*newTriangles).v2.x[newTrianglesIndex + 1] = newVertex.x;
		(*newTriangles).v2.y[newTrianglesIndex + 1] = newVertex.y;
//		(*newTriangles).v2.z[newTrianglesIndex + 1] = newVertex.z;
	}
	else //maximumEdge == 3
	{
		newVertex.x = (triangleToPart.c.x + triangleToPart.a.x) / 2;
		newVertex.y = (triangleToPart.c.y + triangleToPart.a.y) / 2;
//		newVertex.z = (triangleToPart.c.z + triangleToPart.a.z) / 2;

		(*newTriangles).v0.x[newTrianglesIndex] = triangleToPart.a.x;
		(*newTriangles).v0.y[newTrianglesIndex] = triangleToPart.a.y;
//		(*newTriangles).v0.z[newTrianglesIndex] = triangleToPart.a.z;
		(*newTriangles).v1.x[newTrianglesIndex] = triangleToPart.b.x;
		(*newTriangles).v1.y[newTrianglesIndex] = triangleToPart.b.y;
//		(*newTriangles).v1.z[newTrianglesIndex] = triangleToPart.b.z;
		(*newTriangles).v2.x[newTrianglesIndex] = newVertex.x;
		(*newTriangles).v2.y[newTrianglesIndex] = newVertex.y;
//		(*newTriangles).v2.z[newTrianglesIndex] = newVertex.z;

		(*newTriangles).v0.x[newTrianglesIndex + 1] = triangleToPart.b.x;
		(*newTriangles).v0.y[newTrianglesIndex + 1] = triangleToPart.b.y;
//		(*newTriangles).v0.z[newTrianglesIndex + 1] = triangleToPart.b.z;
		(*newTriangles).v1.x[newTrianglesIndex + 1] = triangleToPart.c.x;
		(*newTriangles).v1.y[newTrianglesIndex + 1] = triangleToPart.c.y;
//		(*newTriangles).v1.z[newTrianglesIndex + 1] = triangleToPart.c.z;
		(*newTriangles).v2.x[newTrianglesIndex + 1] = newVertex.x;
		(*newTriangles).v2.y[newTrianglesIndex + 1] = newVertex.y;
//		(*newTriangles).v2.z[newTrianglesIndex + 1] = newVertex.z;
	}
}

void addToResultArray( triangle fitTriangle, TrianglePointers* resultArray, int resultIndex )
{
	/*
	printf("\nTriangle point a: ( %f; %f )", fitTriangle.a.x, fitTriangle.a.y);
	printf("\nTriangle point b: ( %f; %f )", fitTriangle.b.x, fitTriangle.b.y);
	printf("\nTriangle point c: ( %f; %f )\n", fitTriangle.c.x, fitTriangle.c.y);
	*/
	(*resultArray).v0.x[resultIndex] = fitTriangle.a.x;
	(*resultArray).v0.y[resultIndex] = fitTriangle.a.y;
//	(*resultArray).v0.z[resultIndex] = fitTriangle.a.z;
	(*resultArray).v1.x[resultIndex] = fitTriangle.b.x;
	(*resultArray).v1.y[resultIndex] = fitTriangle.b.y;
//	(*resultArray).v1.z[resultIndex] = fitTriangle.b.z;
	(*resultArray).v2.x[resultIndex] = fitTriangle.c.x;
	(*resultArray).v2.y[resultIndex] = fitTriangle.c.y;
//	(*resultArray).v2.z[resultIndex] = fitTriangle.c.z;
}

void triangulation_C(	TrianglePointers* srcVertex, int srcCount,
						int maxWidth, int maxHeight,
						int maxDstSize, TrianglePointers* dstVertex,
						int* srcTreatedCount)
{
	int currentDstSize = 0;
	int checkForFitCount = srcCount;
	int checkForFitCountNew = 0;

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

	TrianglePointers trianglesArrayToCheckNew;

	float * axNew = (float*)malloc(maxDstSize * sizeof(float));
	float * ayNew = (float*)malloc(maxDstSize * sizeof(float));
	float * bxNew = (float*)malloc(maxDstSize * sizeof(float));
	float * byNew = (float*)malloc(maxDstSize * sizeof(float));
	float * cxNew = (float*)malloc(maxDstSize * sizeof(float));
	float * cyNew = (float*)malloc(maxDstSize * sizeof(float));

	trianglesArrayToCheckNew.v0.x = axNew;
	trianglesArrayToCheckNew.v0.y = ayNew;
	trianglesArrayToCheckNew.v1.x = bxNew;
	trianglesArrayToCheckNew.v1.y = byNew;
	trianglesArrayToCheckNew.v2.x = cxNew;
	trianglesArrayToCheckNew.v2.y = cyNew;

//	TrianglePointers* trianglesArrayToCheck =  (TrianglePointers*)malloc(maxDstSize*sizeof(TrianglePointers)) ;
//	memcpy(trianglesArrayToCheck,srcVertex,srcCount*sizeof(TrianglePointers));
//	TrianglePointers* trianglesArrayToCheckNew = (TrianglePointers*)malloc(maxDstSize*sizeof(TrianglePointers));
	int* triangulationFlags= (int*)malloc(maxDstSize*sizeof(int));

	triangle triangleObject;

	while( currentDstSize <= maxDstSize && checkForFitCount != 0 )
	{
		for(int i = 0; i < maxDstSize; ++i)
		triangulationFlags[i] = 0;

		for(int i = 0; i < checkForFitCount; ++i)
		{
			triangleObject.a.x = trianglesArrayToCheck.v0.x[i];
			triangleObject.a.y = trianglesArrayToCheck.v0.y[i];
//			triangleObject.a.z = trianglesArrayToCheck.v0.z[i];
			triangleObject.b.x = trianglesArrayToCheck.v1.x[i];
			triangleObject.b.y = trianglesArrayToCheck.v1.y[i];
//			triangleObject.b.z = trianglesArrayToCheck.v1.z[i];
			triangleObject.c.x = trianglesArrayToCheck.v2.x[i];
			triangleObject.c.y = trianglesArrayToCheck.v2.y[i];
//			triangleObject.c.z = trianglesArrayToCheck.v2.z[i];

			if( !isFit( triangleObject, maxHeight, maxWidth ) )
				triangulationFlags[i] = 1;
		}
		/*
		printf("Flags:\n");
		for(int j = 0; j < maxDstSize; ++j)
			printf("Triangle %d flag = %d\n", j, triangulationFlags[j]);
		printf("\n");
		*/
		//isFit and partition funcs can be united into one
		for(int i = 0; i < checkForFitCount; i++)
		{	
			triangleObject.a.x = trianglesArrayToCheck.v0.x[i];
			triangleObject.a.y = trianglesArrayToCheck.v0.y[i];
//			triangleObject.a.z = trianglesArrayToCheck.v0.z[i];
			triangleObject.b.x = trianglesArrayToCheck.v1.x[i];
			triangleObject.b.y = trianglesArrayToCheck.v1.y[i];
//			triangleObject.b.z = trianglesArrayToCheck.v1.z[i];
			triangleObject.c.x = trianglesArrayToCheck.v2.x[i];
			triangleObject.c.y = trianglesArrayToCheck.v2.y[i];
//			triangleObject.c.z = trianglesArrayToCheck.v2.z[i];
			if( triangulationFlags[i] )
			{
				partition( triangleObject, &trianglesArrayToCheckNew, checkForFitCountNew);
				(*srcTreatedCount)++;
				checkForFitCountNew += 2;
			}
			else
			{
				addToResultArray( triangleObject, dstVertex, currentDstSize );
				currentDstSize++;
			}
		}
		for(int i = 0; i < checkForFitCountNew; ++i)
		{
			trianglesArrayToCheck.v0.x[i] = trianglesArrayToCheckNew.v0.x[i];
			trianglesArrayToCheck.v0.y[i] = trianglesArrayToCheckNew.v0.y[i];
			trianglesArrayToCheck.v1.x[i] = trianglesArrayToCheckNew.v1.x[i];
			trianglesArrayToCheck.v1.y[i] = trianglesArrayToCheckNew.v1.y[i];
			trianglesArrayToCheck.v2.x[i] = trianglesArrayToCheckNew.v2.x[i];
			trianglesArrayToCheck.v2.y[i] = trianglesArrayToCheckNew.v2.y[i];
		}
		checkForFitCount = checkForFitCountNew;
		checkForFitCountNew = 0;
	}
	
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
	//free(trianglesArrayToCheckNew);
	//free(triangulationFlags);
}

void initTrianglesArray( TrianglePointers* triangleArray, int dim )
{
	for(int i = 0; i < dim; ++i)
	{
		triangleArray->v0.x[i] = i;
		triangleArray->v0.y[i] = i;
		triangleArray->v0.z[i] = i;
		triangleArray->v1.x[i] = i + 3;
		triangleArray->v1.y[i] = i + 1;
		triangleArray->v1.z[i] = i + 1;
		triangleArray->v2.x[i] = i + 2;
		triangleArray->v2.y[i] = i + 3;
		triangleArray->v2.z[i] = i + 2;
	}
}

const int size = 2;
const int maximumDestinationSize = 8;

int main()
{
	//-------------------------------------------------------first-test-try-----------------
	//TrianglePointers (10 float fields and 1 int) x 3
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

	triangulation_C( &testTrianglesArray, size, 2, 2, maximumDestinationSize, &testResultTrianglesArray, &treatedCounter );

	printf("\n\nResult Triangles:");
	for(int i = 0; i < size + treatedCounter; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i]);
	}
	

	return 0;
}

