
void minMax_C(int* a, int* b)
{
	if(*a > *b)
	{
		*a = *b - *a;
		*b = *b - *a;
		*a = *a + *b;	
	}
}

void minMaxMas_C(int* a, int* b, int size) // 36  max 29  min 
{
	while(size > 0)
	{
		size--;
		if(*(a + size) > *(b + size))
		{
			*(a + size) = *(b + size) - *(a + size);
			*(b + size) = *(b + size) - *(a + size);
			*(a + size) = *(a + size) + *(b + size);
		}
	}
}