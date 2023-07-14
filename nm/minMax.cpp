void minMaxMas_C(int* a, int* b, int size)
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