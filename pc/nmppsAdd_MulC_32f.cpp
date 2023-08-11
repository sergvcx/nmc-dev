
extern "C" void nmppsAdd_MulC_32f( float* srcVec1, float* srcVec2, float* dstVec, float* nVal, int srcCount )
{
	for(int i = 0; i < srcCount; ++i)
	{
		dstVec[i] = (srcVec1[i] + srcVec2[i]) * (*nVal);
	}
}
