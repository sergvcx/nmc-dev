#include "stdio.h"

void sourseArray16sbs_16s_C_(int* sourseArray16s, int* resultArray32s, int size)
{
	int j = 0;
	for(int i = 0; i < size; i += 2)
	{
		*(resultArray32s + i) = (((*(sourseArray16s + j)) << 16) >> 16) * (((((*(sourseArray16s + j)) << 16) >> 16) >> 15) | 1);
		*(resultArray32s + i + 1) = ((*(sourseArray16s + j)) >> 16) * ((((*(sourseArray16s + j)) >> 16) >> 15) | 1);
		j++;
	}
	
}


void abs_16s_C16(short* sourseArray16s, int* resultArray32s, int size)
{
	for(int i = 0; i < size; i++)
	{
		
			*(resultArray32s + i) = (((*(sourseArray16s + i)) >> 16) | 1) * (*(sourseArray16s + i));
	}
}
void abs_16s_C(int* sourseArray16s, int* resultArray32s, int size){	
	abs_16s_C16((short*) sourseArray16s, (int*) resultArray32s, size);

}
