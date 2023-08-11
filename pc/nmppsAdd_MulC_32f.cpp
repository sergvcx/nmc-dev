
extern "C" void nmppsAdd_MulC_32f( float* srcVec1, float* srcVec2, float* dstVec, float* nVal, int srcCount )
{
	for(int i = 0; i < srcCount / 2; ++i)
	{
		dstVec[i * 2] = (srcVec1[i * 2] + srcVec2[i * 2]) * nVal[0];
		dstVec[i * 2 + 1] = (srcVec1[i * 2 + 1] + srcVec2[i * 2 + 1]) * nVal[1];
	}
	if(srcCount % 2 != 0)
	{
		dstVec[srcCount - 1] = (srcVec1[srcCount - 1] + srcVec2[srcCount - 1]) * nVal[0];
	}
}
