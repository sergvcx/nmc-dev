
extern "C" void nmppsSub_Abs_Even_32f( float* srcVec1, float* srcVec2, float* dstVec, int srcCount )
{
	for(int i = 0; i < srcCount / 2; ++i)
	{
		dstVec[i] = abs( srcVec1[i * 2] - srcVec2[i * 2] );
	}
}
