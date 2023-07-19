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
	*/
	//это тоже самое что модуль разности
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
		return true;
	
	return false;
}

int maxEdge( float edge1, float edge2, float edge3 )
{
	
}

void partition( triangle triangleToPart, TrianglePointers* newTriangles, int newTrianglesNumber )
{
	float edge1 = 0;
	float edge2 = 0;
	float edge3 = 0;
	int maxEdge = 0;
	point newVertex;

	edge1 = pow(( triangleToPart.a.x - triangleToPart.b.x ), 2) + pow(( triangleToPart.a.y - triangleToPart.b.y ), 2);
	edge2 = pow(( triangleToPart.b.x - triangleToPart.c.x ), 2) + pow(( triangleToPart.b.y - triangleToPart.c.y ), 2);
	edge3 = pow(( triangleToPart.a.x - triangleToPart.c.x ), 2) + pow(( triangleToPart.a.y - triangleToPart.c.y ), 2);
	
	//maxEdge = maxEdge( edge1, edge2, edge3 );

	if( maxEdge == 1 )
	{
		newVertex.x = abs(triangleToPart.a.x - triangleToPart.b.x);
		newVertex.y = abs(triangleToPart.a.y - triangleToPart.b.y);
		newVertex.x = abs(triangleToPart.a.z - triangleToPart.b.z);

		newTriangles->v0.x[newTrianglesNumber] = triangleToPart.a.x;
		newTriangles->v0.y[newTrianglesNumber] = triangleToPart.a.y;
		newTriangles->v0.z[newTrianglesNumber] = triangleToPart.a.z;
		newTriangles->v1.x[newTrianglesNumber] = triangleToPart.c.x;
		newTriangles->v1.y[newTrianglesNumber] = triangleToPart.c.y;
		newTriangles->v1.z[newTrianglesNumber] = triangleToPart.c.z;
		newTriangles->v2.x[newTrianglesNumber] = newVertex.x;
		newTriangles->v2.y[newTrianglesNumber] = newVertex.y;
		newTriangles->v2.z[newTrianglesNumber] = newVertex.z;

		newTriangles->v0.x[newTrianglesNumber + 1] = triangleToPart.b.x;
		newTriangles->v0.y[newTrianglesNumber + 1] = triangleToPart.b.y;
		newTriangles->v0.z[newTrianglesNumber + 1] = triangleToPart.b.z;
		newTriangles->v1.x[newTrianglesNumber + 1] = triangleToPart.c.x;
		newTriangles->v1.y[newTrianglesNumber + 1] = triangleToPart.c.y;
		newTriangles->v1.z[newTrianglesNumber + 1] = triangleToPart.c.z;
		newTriangles->v2.x[newTrianglesNumber + 1] = newVertex.x;
		newTriangles->v2.y[newTrianglesNumber + 1] = newVertex.y;
		newTriangles->v2.z[newTrianglesNumber + 1] = newVertex.z;
	}
	else if ( maxEdge == 2 )
	{
		newVertex.x = abs(triangleToPart.c.x - triangleToPart.b.x);
		newVertex.y = abs(triangleToPart.c.y - triangleToPart.b.y);
		newVertex.x = abs(triangleToPart.c.z - triangleToPart.b.z);
		
		newTriangles->v0.x[newTrianglesNumber] = triangleToPart.a.x;
		newTriangles->v0.y[newTrianglesNumber] = triangleToPart.a.y;
		newTriangles->v0.z[newTrianglesNumber] = triangleToPart.a.z;
		newTriangles->v1.x[newTrianglesNumber] = triangleToPart.b.x;
		newTriangles->v1.y[newTrianglesNumber] = triangleToPart.b.y;
		newTriangles->v1.z[newTrianglesNumber] = triangleToPart.b.z;
		newTriangles->v2.x[newTrianglesNumber] = newVertex.x;
		newTriangles->v2.y[newTrianglesNumber] = newVertex.y;
		newTriangles->v2.z[newTrianglesNumber] = newVertex.z;

		newTriangles->v0.x[newTrianglesNumber + 1] = triangleToPart.a.x;
		newTriangles->v0.y[newTrianglesNumber + 1] = triangleToPart.a.y;
		newTriangles->v0.z[newTrianglesNumber + 1] = triangleToPart.a.z;
		newTriangles->v1.x[newTrianglesNumber + 1] = triangleToPart.c.x;
		newTriangles->v1.y[newTrianglesNumber + 1] = triangleToPart.c.y;
		newTriangles->v1.z[newTrianglesNumber + 1] = triangleToPart.c.z;
		newTriangles->v2.x[newTrianglesNumber + 1] = newVertex.x;
		newTriangles->v2.y[newTrianglesNumber + 1] = newVertex.y;
		newTriangles->v2.z[newTrianglesNumber + 1] = newVertex.z;
	}
	else //maxEdge == 3
	{
		newVertex.x = abs(triangleToPart.c.x - triangleToPart.a.x);
		newVertex.y = abs(triangleToPart.c.y - triangleToPart.a.y);
		newVertex.x = abs(triangleToPart.c.z - triangleToPart.a.z);
		
		newTriangles->v0.x[newTrianglesNumber] = triangleToPart.a.x;
		newTriangles->v0.y[newTrianglesNumber] = triangleToPart.a.y;
		newTriangles->v0.z[newTrianglesNumber] = triangleToPart.a.z;
		newTriangles->v1.x[newTrianglesNumber] = triangleToPart.b.x;
		newTriangles->v1.y[newTrianglesNumber] = triangleToPart.b.y;
		newTriangles->v1.z[newTrianglesNumber] = triangleToPart.b.z;
		newTriangles->v2.x[newTrianglesNumber] = newVertex.x;
		newTriangles->v2.y[newTrianglesNumber] = newVertex.y;
		newTriangles->v2.z[newTrianglesNumber] = newVertex.z;

		newTriangles->v0.x[newTrianglesNumber + 1] = triangleToPart.b.x;
		newTriangles->v0.y[newTrianglesNumber + 1] = triangleToPart.b.y;
		newTriangles->v0.z[newTrianglesNumber + 1] = triangleToPart.b.z;
		newTriangles->v1.x[newTrianglesNumber + 1] = triangleToPart.c.x;
		newTriangles->v1.y[newTrianglesNumber + 1] = triangleToPart.c.y;
		newTriangles->v1.z[newTrianglesNumber + 1] = triangleToPart.c.z;
		newTriangles->v2.x[newTrianglesNumber + 1] = newVertex.x;
		newTriangles->v2.y[newTrianglesNumber + 1] = newVertex.y;
		newTriangles->v2.z[newTrianglesNumber + 1] = newVertex.z;
	}

	
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
			//triangleObject.a.z = trianglesArrayToCheck->v0.z[i];
			triangleObject.b.x = trianglesArrayToCheck->v1.x[i];
			triangleObject.b.y = trianglesArrayToCheck->v1.y[i];
			//triangleObject.b.z = trianglesArrayToCheck->v1.z[i];
			triangleObject.c.x = trianglesArrayToCheck->v2.x[i];
			triangleObject.c.y = trianglesArrayToCheck->v2.y[i];
			//triangleObject.c.z = trianglesArrayToCheck->v2.z[i];

			if( !isFit( triangleObject, maxHeight, maxWidth ) )
				triangulationFlags[i] = 1;
		}
		//isFit and partition funcs can be united into one
		for(int i = 0; i < checkForFitCount; i++)
			if( triangulationFlags[i] )
			{
				triangleObject.a.x = trianglesArrayToCheck->v0.x[i];
				triangleObject.a.y = trianglesArrayToCheck->v0.y[i];
				//triangleObject.a.z = trianglesArrayToCheck->v0.z[i];
				triangleObject.b.x = trianglesArrayToCheck->v1.x[i];
				triangleObject.b.y = trianglesArrayToCheck->v1.y[i];
				//triangleObject.b.z = trianglesArrayToCheck->v1.z[i];
				triangleObject.c.x = trianglesArrayToCheck->v2.x[i];
				triangleObject.c.y = trianglesArrayToCheck->v2.y[i];
				//triangleObject.c.z = trianglesArrayToCheck->v2.z[i];

				partition( triangleObject, trianglesArrayToCheckNew, checkForFitCountNew);
				++srcTreatedCount;
				checkForFitCountNew += 2;
			}
			else
			{
				addToResultArray( dstVertex );
				++currentDstSize;
			}
		checkForFitCount = checkForFitCountNew;
		trianglesArrayToCheck = trianglesArrayToCheckNew;
		for(int i = 0; i < maxDstSize; ++i)
			triangulationFlags[i] = 0;
	}
}

int main()
{
	
	return 0;
}

