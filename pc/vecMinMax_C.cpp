extern "C" void vecMinMaxRep32 (int* minArray, int* maxArray, int dim)
{
	while(dim > 0)
	{
		dim--;
		if(*(minArray + dim) > *(maxArray + dim))
		{
			*(minArray + dim) = *(maxArray + dim) - *(minArray + dim);
			*(maxArray + dim) = *(maxArray + dim) - *(minArray + dim);
			*(minArray + dim) = *(minArray + dim) + *(maxArray + dim);
		}
	}
}