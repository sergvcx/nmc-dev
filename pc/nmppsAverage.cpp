
extern "C" void nmppsAverage( float* srcVec1, float* srcVec2, float* dstArray, float* nVal, int srcCount )
{
	for(int i = 0; i < srcCount; ++i)
	{
		dstArray[i] = (srcVec1[i] + srcVec2[i]) * (*nVal);
	}
}
