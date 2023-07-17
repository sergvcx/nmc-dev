#include "stdio.h"
#include "stdlib.h"
#include "../../../include/primitive.h"

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

	//algorithm prototype without real functions
	while( currentDstSize <= maxDstSize )
	{
		for(int i = 0; i < checkForFitCount; ++i)
			if( !isFit( trianglesArrayToCheck[i] ) )
				triangulationFlags[i] = 1;
		//mb unite isFit and partition funcs into one
		for(int i = 0; i < checkForFitCount; i++)
			if( triangulationFlags[i] )
			{
				partition( trianglesArrayToCheck[i], trianglesArrayToCheckNew);
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

