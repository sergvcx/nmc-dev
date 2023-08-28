#include "math.h"

extern "C" void nmppsAbs_32f( float * srcVec, float * dstVec, int srcCount )
{
	for(int i = 0; i < srcCount; ++i)
	{
		dstVec[i] = fabs(srcVec[i]);
	}
}
