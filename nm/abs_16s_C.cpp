#include "../include/general_header.h"
#include "stdio.h"

void abs_16s_C(int* sourceArray16s, int* resultArray32s, int dim)
{
	int j = 0;
	for(int i = 0; i < dim; i += 2)
	{
		*(resultArray32s + i) = (((*(sourceArray16s + j)) << 16) >> 16) * (((((*(sourceArray16s + j)) << 16) >> 16) >> 15) | 1);
		*(resultArray32s + i + 1) = ((*(sourceArray16s + j)) >> 16) * ((((*(sourceArray16s + j)) >> 16) >> 15) | 1);
		j++;
	}
}
