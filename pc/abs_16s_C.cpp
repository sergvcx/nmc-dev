extern "C" void abs_16s(int* sourseArray16s, int* resultArray32s, int dim)
{
	int j = 0;
	for(int i = 0; i < dim; i += 2)
	{
		*(resultArray32s + i) = (((*(sourseArray16s + j)) << 16) >> 16) * (((((*(sourseArray16s + j)) << 16) >> 16) >> 15) | 1);
		*(resultArray32s + i + 1) = ((*(sourseArray16s + j)) >> 16) * ((((*(sourseArray16s + j)) >> 16) >> 15) | 1);
		j++;
	}
}
