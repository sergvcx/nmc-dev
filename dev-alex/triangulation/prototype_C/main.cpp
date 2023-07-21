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
		newVertex.z = (triangleToPart.a.z + triangleToPart.b.z) / 2;

		//newTriangles[newTrianglesIndex] = TrianglePointers();

		newTriangles[newTrianglesIndex].v0.x[0] = triangleToPart.a.x;
		newTriangles[newTrianglesIndex].v0.y[0] = triangleToPart.a.y;
		newTriangles[newTrianglesIndex].v0.z[0] = triangleToPart.a.z;
		newTriangles[newTrianglesIndex].v1.x[0] = triangleToPart.c.x;
		newTriangles[newTrianglesIndex].v1.y[0] = triangleToPart.c.y;
		newTriangles[newTrianglesIndex].v1.z[0] = triangleToPart.c.z;
		newTriangles[newTrianglesIndex].v2.x[0] = newVertex.x;
		newTriangles[newTrianglesIndex].v2.y[0] = newVertex.y;
		newTriangles[newTrianglesIndex].v2.z[0] = newVertex.z;

		//newTriangles[newTrianglesIndex + 1] = TrianglePointers();

		newTriangles[newTrianglesIndex + 1].v0.x[0] = triangleToPart.b.x;
		newTriangles[newTrianglesIndex + 1].v0.y[0] = triangleToPart.b.y;
		newTriangles[newTrianglesIndex + 1].v0.z[0] = triangleToPart.b.z;
		newTriangles[newTrianglesIndex + 1].v1.x[0] = triangleToPart.c.x;
		newTriangles[newTrianglesIndex + 1].v1.y[0] = triangleToPart.c.y;
		newTriangles[newTrianglesIndex + 1].v1.z[0] = triangleToPart.c.z;
		newTriangles[newTrianglesIndex + 1].v2.x[0] = newVertex.x;
		newTriangles[newTrianglesIndex + 1].v2.y[0] = newVertex.y;
		newTriangles[newTrianglesIndex + 1].v2.z[0] = newVertex.z;
	}
	else if ( maximumEdge == 2 )
	{
		newVertex.x = (triangleToPart.c.x + triangleToPart.b.x) / 2;
		newVertex.y = (triangleToPart.c.y + triangleToPart.b.y) / 2;
		newVertex.z = (triangleToPart.c.z + triangleToPart.b.z) / 2;
		
		newTriangles[newTrianglesIndex] = TrianglePointers();

		newTriangles[newTrianglesIndex].v0.x[0] = triangleToPart.a.x;
		newTriangles[newTrianglesIndex].v0.y[0] = triangleToPart.a.y;
		newTriangles[newTrianglesIndex].v0.z[0] = triangleToPart.a.z;
		newTriangles[newTrianglesIndex].v1.x[0] = triangleToPart.b.x;
		newTriangles[newTrianglesIndex].v1.y[0] = triangleToPart.b.y;
		newTriangles[newTrianglesIndex].v1.z[0] = triangleToPart.b.z;
		newTriangles[newTrianglesIndex].v2.x[0] = newVertex.x;
		newTriangles[newTrianglesIndex].v2.y[0] = newVertex.y;
		newTriangles[newTrianglesIndex].v2.z[0] = newVertex.z;

		newTriangles[newTrianglesIndex + 1] = TrianglePointers();

		newTriangles[newTrianglesIndex + 1].v0.x[0] = triangleToPart.a.x;
		newTriangles[newTrianglesIndex + 1].v0.y[0] = triangleToPart.a.y;
		newTriangles[newTrianglesIndex + 1].v0.z[0] = triangleToPart.a.z;
		newTriangles[newTrianglesIndex + 1].v1.x[0] = triangleToPart.c.x;
		newTriangles[newTrianglesIndex + 1].v1.y[0] = triangleToPart.c.y;
		newTriangles[newTrianglesIndex + 1].v1.z[0] = triangleToPart.c.z;
		newTriangles[newTrianglesIndex + 1].v2.x[0] = newVertex.x;
		newTriangles[newTrianglesIndex + 1].v2.y[0] = newVertex.y;
		newTriangles[newTrianglesIndex + 1].v2.z[0] = newVertex.z;
	}
	else //maximumEdge == 3
	{
		newVertex.x = (triangleToPart.c.x + triangleToPart.a.x) / 2;
		newVertex.y = (triangleToPart.c.y + triangleToPart.a.y) / 2;
		newVertex.z = (triangleToPart.c.z + triangleToPart.a.z) / 2;
		
		newTriangles[newTrianglesIndex] = TrianglePointers();

		newTriangles[newTrianglesIndex].v0.x[0] = triangleToPart.a.x;
		newTriangles[newTrianglesIndex].v0.y[0] = triangleToPart.a.y;
		newTriangles[newTrianglesIndex].v0.z[0] = triangleToPart.a.z;
		newTriangles[newTrianglesIndex].v1.x[0] = triangleToPart.b.x;
		newTriangles[newTrianglesIndex].v1.y[0] = triangleToPart.b.y;
		newTriangles[newTrianglesIndex].v1.z[0] = triangleToPart.b.z;
		newTriangles[newTrianglesIndex].v2.x[0] = newVertex.x;
		newTriangles[newTrianglesIndex].v2.y[0] = newVertex.y;
		newTriangles[newTrianglesIndex].v2.z[0] = newVertex.z;

		newTriangles[newTrianglesIndex + 1] = TrianglePointers();

		newTriangles[newTrianglesIndex + 1].v0.x[0] = triangleToPart.b.x;
		newTriangles[newTrianglesIndex + 1].v0.y[0] = triangleToPart.b.y;
		newTriangles[newTrianglesIndex + 1].v0.z[0] = triangleToPart.b.z;
		newTriangles[newTrianglesIndex + 1].v1.x[0] = triangleToPart.c.x;
		newTriangles[newTrianglesIndex + 1].v1.y[0] = triangleToPart.c.y;
		newTriangles[newTrianglesIndex + 1].v1.z[0] = triangleToPart.c.z;
		newTriangles[newTrianglesIndex + 1].v2.x[0] = newVertex.x;
		newTriangles[newTrianglesIndex + 1].v2.y[0] = newVertex.y;
		newTriangles[newTrianglesIndex + 1].v2.z[0] = newVertex.z;
	}
}

void addToResultArray( triangle fitTriangle, TrianglePointers* resultArray, int resultIndex )
{
	//resultArray[resultIndex] = TrianglePointers();
	/*
	printf("\nTriangle point a: ( %f; %f )", fitTriangle.a.x, fitTriangle.a.y);
	printf("\nTriangle point b: ( %f; %f )", fitTriangle.b.x, fitTriangle.b.y);
	printf("\nTriangle point c: ( %f; %f )\n", fitTriangle.c.x, fitTriangle.c.y);
	*/
	resultArray[resultIndex].v0.x[0] = fitTriangle.a.x;
	resultArray[resultIndex].v0.y[0] = fitTriangle.a.y;
	resultArray[resultIndex].v0.z[0] = fitTriangle.a.z;
	resultArray[resultIndex].v1.x[0] = fitTriangle.b.x;
	resultArray[resultIndex].v1.y[0] = fitTriangle.b.y;
	resultArray[resultIndex].v1.z[0] = fitTriangle.b.z;
	resultArray[resultIndex].v2.x[0] = fitTriangle.c.x;
	resultArray[resultIndex].v2.y[0] = fitTriangle.c.y;
	resultArray[resultIndex].v2.z[0] = fitTriangle.c.z;
}

void triangulation_C(	TrianglePointers* srcVertex, int srcCount,
						int maxWidth, int maxHeight,
						int maxDstSize, TrianglePointers* dstVertex,
						int* srcTreatedCount)
{
	int currentDstSize = 0;
	int checkForFitCount = srcCount;
	int checkForFitCountNew = 0;
	TrianglePointers* trianglesArrayToCheck =  (TrianglePointers*)malloc(maxDstSize*sizeof(TrianglePointers)) ;
	memcpy(trianglesArrayToCheck,srcVertex,srcCount*sizeof(TrianglePointers));
	TrianglePointers* trianglesArrayToCheckNew = (TrianglePointers*)malloc(maxDstSize*sizeof(TrianglePointers));
	//int triangulationFlags[maxDstSize];
	int* triangulationFlags= (int*)malloc(maxDstSize*sizeof(int));

	triangle triangleObject;

	//algorithm prototype without real functions
	while( currentDstSize <= maxDstSize && checkForFitCount != 0 )
	{
		for(int i = 0; i < maxDstSize; ++i)
		triangulationFlags[i] = 0;

		for(int i = 0; i < checkForFitCount; ++i)
		{
			triangleObject.a.x = trianglesArrayToCheck[i].v0.x[0];
			triangleObject.a.y = trianglesArrayToCheck[i].v0.y[0];
			triangleObject.a.z = trianglesArrayToCheck[i].v0.z[0];
			triangleObject.b.x = trianglesArrayToCheck[i].v1.x[0];
			triangleObject.b.y = trianglesArrayToCheck[i].v1.y[0];
			triangleObject.b.z = trianglesArrayToCheck[i].v1.z[0];
			triangleObject.c.x = trianglesArrayToCheck[i].v2.x[0];
			triangleObject.c.y = trianglesArrayToCheck[i].v2.y[0];
			triangleObject.c.z = trianglesArrayToCheck[i].v2.z[0];

			if( !isFit( triangleObject, maxHeight, maxWidth ) )
				triangulationFlags[i] = 1;
		}
		/*
		for(int j = 0; j < maxDstSize; ++j)
			printf("%d\n", triangulationFlags[j]);
		printf("\n");
		*/
		//isFit and partition funcs can be united into one
		for(int i = 0; i < checkForFitCount; i++)
		{	
			triangleObject.a.x = trianglesArrayToCheck[i].v0.x[0];
			triangleObject.a.y = trianglesArrayToCheck[i].v0.y[0];
			triangleObject.a.z = trianglesArrayToCheck[i].v0.z[0];
			triangleObject.b.x = trianglesArrayToCheck[i].v1.x[0];
			triangleObject.b.y = trianglesArrayToCheck[i].v1.y[0];
			triangleObject.b.z = trianglesArrayToCheck[i].v1.z[0];
			triangleObject.c.x = trianglesArrayToCheck[i].v2.x[0];
			triangleObject.c.y = trianglesArrayToCheck[i].v2.y[0];
			triangleObject.c.z = trianglesArrayToCheck[i].v2.z[0];
			if( triangulationFlags[i] )
			{
				partition( triangleObject, trianglesArrayToCheckNew, checkForFitCountNew);
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
			//trianglesArrayToCheck[i] = TrianglePointers();
			trianglesArrayToCheck[i] = trianglesArrayToCheckNew[i];
		}
		checkForFitCount = checkForFitCountNew;
		checkForFitCountNew = 0;
	}
	
	free(trianglesArrayToCheckNew);
	free(triangulationFlags);
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
	//-------------------------------------------------------first-test-try-----------------
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

	printf("\nGiven Triangle:");
	printf("\nTriangle point a: ( %f; %f )", testTrianglesArray[0].v0.x[0], testTrianglesArray[0].v0.y[0]);
	printf("\nTriangle point b: ( %f; %f )", testTrianglesArray[0].v1.x[0], testTrianglesArray[0].v1.y[0]);
	printf("\nTriangle point c: ( %f; %f )\n", testTrianglesArray[0].v2.x[0], testTrianglesArray[0].v2.y[0]);

	triangulation_C(testTrianglesArray, size, 2, 2, maximumDestinationSize, testResultTrianglesArray, &treatedCounter);

	printf("\n\nResult Triangles:");
	for(int i = 0; i < size + treatedCounter; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testResultTrianglesArray[i].v0.x[0], testResultTrianglesArray[i].v0.y[0]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testResultTrianglesArray[i].v1.x[0], testResultTrianglesArray[i].v1.y[0]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testResultTrianglesArray[i].v2.x[0], testResultTrianglesArray[i].v2.y[0]);
	}
	

	return 0;
}

