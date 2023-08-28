
extern "C" void sumOfSquares( float * srcVec1, float * srcVec2, float * dstVec, int srcCount )
{
	for(int i = 0; i < srcCount; ++i)
	{
		dstVec[i] = srcVec1[i] * srcVec1[i] + srcVec2[i] * srcVec2[i];
	}
}
