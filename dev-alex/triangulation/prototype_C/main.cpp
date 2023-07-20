#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "../../../include/primitive.h"
#include "../../../include/nmtype.h"

struct point
{
	nm32f x;
	nm32f y;
	nm32f z;

	point () { x = 0; y = 0; z = 0; }
};

struct edge
{
	
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
	edge2 = pow(( triangleToPart.b.x - triangleToPart.c.x ), 2) + pow(( triangleToPart.b.y - triangleToPart.c.y ), 2);
	edge3 = pow(( triangleToPart.a.x - triangleToPart.c.x ), 2) + pow(( triangleToPart.a.y - triangleToPart.c.y ), 2);
	
	maximumEdge = maxEdge( edge1, edge2, edge3 );

	if( maximumEdge == 1 )
	{
		newVertex.x = abs(triangleToPart.a.x - triangleToPart.b.x);
		newVertex.y = abs(triangleToPart.a.y - triangleToPart.b.y);
		newVertex.z = abs(triangleToPart.a.z - triangleToPart.b.z);

		newTriangles->v0.x[newTrianglesIndex] = triangleToPart.a.x;
		newTriangles->v0.y[newTrianglesIndex] = triangleToPart.a.y;
		newTriangles->v0.z[newTrianglesIndex] = triangleToPart.a.z;
		newTriangles->v1.x[newTrianglesIndex] = triangleToPart.c.x;
		newTriangles->v1.y[newTrianglesIndex] = triangleToPart.c.y;
		newTriangles->v1.z[newTrianglesIndex] = triangleToPart.c.z;
		newTriangles->v2.x[newTrianglesIndex] = newVertex.x;
		newTriangles->v2.y[newTrianglesIndex] = newVertex.y;
		newTriangles->v2.z[newTrianglesIndex] = newVertex.z;

		newTriangles->v0.x[newTrianglesIndex + 1] = triangleToPart.b.x;
		newTriangles->v0.y[newTrianglesIndex + 1] = triangleToPart.b.y;
		newTriangles->v0.z[newTrianglesIndex + 1] = triangleToPart.b.z;
		newTriangles->v1.x[newTrianglesIndex + 1] = triangleToPart.c.x;
		newTriangles->v1.y[newTrianglesIndex + 1] = triangleToPart.c.y;
		newTriangles->v1.z[newTrianglesIndex + 1] = triangleToPart.c.z;
		newTriangles->v2.x[newTrianglesIndex + 1] = newVertex.x;
		newTriangles->v2.y[newTrianglesIndex + 1] = newVertex.y;
		newTriangles->v2.z[newTrianglesIndex + 1] = newVertex.z;
	}
	else if ( maximumEdge == 2 )
	{
		newVertex.x = abs(triangleToPart.c.x - triangleToPart.b.x);
		newVertex.y = abs(triangleToPart.c.y - triangleToPart.b.y);
		newVertex.z = abs(triangleToPart.c.z - triangleToPart.b.z);
		
		newTriangles->v0.x[newTrianglesIndex] = triangleToPart.a.x;
		newTriangles->v0.y[newTrianglesIndex] = triangleToPart.a.y;
		newTriangles->v0.z[newTrianglesIndex] = triangleToPart.a.z;
		newTriangles->v1.x[newTrianglesIndex] = triangleToPart.b.x;
		newTriangles->v1.y[newTrianglesIndex] = triangleToPart.b.y;
		newTriangles->v1.z[newTrianglesIndex] = triangleToPart.b.z;
		newTriangles->v2.x[newTrianglesIndex] = newVertex.x;
		newTriangles->v2.y[newTrianglesIndex] = newVertex.y;
		newTriangles->v2.z[newTrianglesIndex] = newVertex.z;

		newTriangles->v0.x[newTrianglesIndex + 1] = triangleToPart.a.x;
		newTriangles->v0.y[newTrianglesIndex + 1] = triangleToPart.a.y;
		newTriangles->v0.z[newTrianglesIndex + 1] = triangleToPart.a.z;
		newTriangles->v1.x[newTrianglesIndex + 1] = triangleToPart.c.x;
		newTriangles->v1.y[newTrianglesIndex + 1] = triangleToPart.c.y;
		newTriangles->v1.z[newTrianglesIndex + 1] = triangleToPart.c.z;
		newTriangles->v2.x[newTrianglesIndex + 1] = newVertex.x;
		newTriangles->v2.y[newTrianglesIndex + 1] = newVertex.y;
		newTriangles->v2.z[newTrianglesIndex + 1] = newVertex.z;
	}
	else //maximumEdge == 3
	{
		newVertex.x = abs(triangleToPart.c.x - triangleToPart.a.x);
		newVertex.y = abs(triangleToPart.c.y - triangleToPart.a.y);
		newVertex.z = abs(triangleToPart.c.z - triangleToPart.a.z);
		
		newTriangles->v0.x[newTrianglesIndex] = triangleToPart.a.x;
		newTriangles->v0.y[newTrianglesIndex] = triangleToPart.a.y;
		newTriangles->v0.z[newTrianglesIndex] = triangleToPart.a.z;
		newTriangles->v1.x[newTrianglesIndex] = triangleToPart.b.x;
		newTriangles->v1.y[newTrianglesIndex] = triangleToPart.b.y;
		newTriangles->v1.z[newTrianglesIndex] = triangleToPart.b.z;
		newTriangles->v2.x[newTrianglesIndex] = newVertex.x;
		newTriangles->v2.y[newTrianglesIndex] = newVertex.y;
		newTriangles->v2.z[newTrianglesIndex] = newVertex.z;

		newTriangles->v0.x[newTrianglesIndex + 1] = triangleToPart.b.x;
		newTriangles->v0.y[newTrianglesIndex + 1] = triangleToPart.b.y;
		newTriangles->v0.z[newTrianglesIndex + 1] = triangleToPart.b.z;
		newTriangles->v1.x[newTrianglesIndex + 1] = triangleToPart.c.x;
		newTriangles->v1.y[newTrianglesIndex + 1] = triangleToPart.c.y;
		newTriangles->v1.z[newTrianglesIndex + 1] = triangleToPart.c.z;
		newTriangles->v2.x[newTrianglesIndex + 1] = newVertex.x;
		newTriangles->v2.y[newTrianglesIndex + 1] = newVertex.y;
		newTriangles->v2.z[newTrianglesIndex + 1] = newVertex.z;
	}
}

void addToResultArray( triangle fitTriangle, TrianglePointers* resultArray, int resultIndex )
{
	resultArray->v0.x[resultIndex] = fitTriangle.a.x;
	resultArray->v0.y[resultIndex] = fitTriangle.a.y;
	resultArray->v0.z[resultIndex] = fitTriangle.a.z;
	resultArray->v1.x[resultIndex] = fitTriangle.b.x;
	resultArray->v1.y[resultIndex] = fitTriangle.b.y;
	resultArray->v1.z[resultIndex] = fitTriangle.b.z;
	resultArray->v2.x[resultIndex] = fitTriangle.c.x;
	resultArray->v2.y[resultIndex] = fitTriangle.c.y;
	resultArray->v2.z[resultIndex] = fitTriangle.c.z;
}

void triangulation_C(	TrianglePointers* srcVertex, int srcCount,
						int maxWidth, int maxHeight,
						int maxDstSize, TrianglePointers* dstVertex,
						int* srcTreatedCount)
{
	int currentDstSize = 0;
	int checkForFitCount = srcCount;
	int checkForFitCountNew = 0;
	TrianglePointers* trianglesArrayToCheck = srcVertex;
	TrianglePointers* trianglesArrayToCheckNew;
	int triangulationFlags[maxDstSize];

	for(int i = 0; i < maxDstSize; ++i)
		triangulationFlags[i] = 0;

	triangle triangleObject;

	//algorithm prototype without real functions
	while( currentDstSize <= maxDstSize )
	{
		for(int i = 0; i < checkForFitCount; ++i)
		{
			triangleObject.a.x = trianglesArrayToCheck->v0.x[i];
			triangleObject.a.y = trianglesArrayToCheck->v0.y[i];
			triangleObject.a.z = trianglesArrayToCheck->v0.z[i];
			triangleObject.b.x = trianglesArrayToCheck->v1.x[i];
			triangleObject.b.y = trianglesArrayToCheck->v1.y[i];
			triangleObject.b.z = trianglesArrayToCheck->v1.z[i];
			triangleObject.c.x = trianglesArrayToCheck->v2.x[i];
			triangleObject.c.y = trianglesArrayToCheck->v2.y[i];
			triangleObject.c.z = trianglesArrayToCheck->v2.z[i];

			if( !isFit( triangleObject, maxHeight, maxWidth ) )
				triangulationFlags[i] = 1;
			printf("\n\n%d\n\n", triangulationFlags[0]);
		}
		//isFit and partition funcs can be united into one
		for(int i = 0; i < checkForFitCount; i++)
		{	
			triangleObject.a.x = trianglesArrayToCheck->v0.x[i];
			triangleObject.a.y = trianglesArrayToCheck->v0.y[i];
			triangleObject.a.z = trianglesArrayToCheck->v0.z[i];
			triangleObject.b.x = trianglesArrayToCheck->v1.x[i];
			triangleObject.b.y = trianglesArrayToCheck->v1.y[i];
			triangleObject.b.z = trianglesArrayToCheck->v1.z[i];
			triangleObject.c.x = trianglesArrayToCheck->v2.x[i];
			triangleObject.c.y = trianglesArrayToCheck->v2.y[i];
			triangleObject.c.z = trianglesArrayToCheck->v2.z[i];
			if( triangulationFlags[i] )
			{
				partition( triangleObject, trianglesArrayToCheckNew, checkForFitCountNew);
				printf("\nsrcTreatedCount[0] = %d\n", srcTreatedCount[0]);
				printf("\nsrcTreatedCount addr = %p\n", srcTreatedCount);
				++srcTreatedCount;
				printf("\nsrcTreatedCount[0] = %d\n", srcTreatedCount[0]);
				printf("\nsrcTreatedCount addr = %p\n", srcTreatedCount);
				checkForFitCountNew += 2;
			}
			else
			{
				addToResultArray( triangleObject, dstVertex, currentDstSize );
				++currentDstSize;
			}
		}
		checkForFitCount = checkForFitCountNew;
		trianglesArrayToCheck = trianglesArrayToCheckNew;
		for(int i = 0; i < maxDstSize; ++i)
			triangulationFlags[i] = 0;
	}
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

const int size = 1;
const int maximumDestinationSize = 6;

int main()
{
	//---------------------------------------------------------------first-test-try-----------------
	//TrianglePointers (10 float fields and 1 int) x 3
	TrianglePointers testTrianglesArray[size];
	TrianglePointers testResultTrianglesArray[maximumDestinationSize];
	int treatedCounter = 0;

	testTrianglesArray[0] = TrianglePointers();

	//initTrianglesArray(testTrianglesArray, size);
	testTrianglesArray->v0.x[0] = 0;
	testTrianglesArray->v0.y[0] = 0;
	testTrianglesArray->v0.z[0] = 0;
	testTrianglesArray->v1.x[0] = 3;
	testTrianglesArray->v1.y[0] = 1;
	testTrianglesArray->v1.z[0] = 1;
	testTrianglesArray->v2.x[0] = 2;
	testTrianglesArray->v2.y[0] = 3;
	testTrianglesArray->v2.z[0] = 2;

	printf("\nTriangle point a: ( %f; %f )", testTrianglesArray->v0.x[0], testTrianglesArray->v0.y[0]);
	printf("\nTriangle point b: ( %f; %f )", testTrianglesArray->v1.x[0], testTrianglesArray->v1.y[0]);
	printf("\nTriangle point c: ( %f; %f )\n", testTrianglesArray->v2.x[0], testTrianglesArray->v2.y[0]);

	triangulation_C(testTrianglesArray, size, 2, 2, maximumDestinationSize, testResultTrianglesArray, &treatedCounter);
	
	for(int i = 0; i < size + treatedCounter; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testResultTrianglesArray->v0.x, testResultTrianglesArray->v0.y);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testResultTrianglesArray->v1.x, testResultTrianglesArray->v1.y);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testResultTrianglesArray->v2.x, testResultTrianglesArray->v2.y);
	}
	

	return 0;
}

