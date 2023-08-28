#include "math.h"

extern "C" void nmppsAbsDiff_32f( float * srcVec1, float * srcVec2, float * dstVec, int srcCount )
{
	for(int i = 0; i < srcCount; ++i)
	{
		dstVec[i] = fabs(srcVec1[i] - srcVec2[i]);
	}
}
