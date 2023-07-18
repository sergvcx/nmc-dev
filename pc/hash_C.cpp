extern "C" int hashRep32( long long* sourceArray32s, int dim)
{
	long long Array[32];
	for(int i = 0; i < 32; i++)
	{
		Array[i] = 0;
	}
	int Sum = 0;
	long long mask = (long long)1 << 63;
	int long_size = dim / 2;
	int pointer = 0;
	for(int i = 0; i < long_size / 32; i++)
	{
		for(int j = 0; j < 32; j++)
		{
			Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + (*(sourceArray32s + pointer));
			pointer++;
		}
	}
	for(int j = 0; j < 16; j++)
	{
		Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + Array[j + 16];
	}
	for(int j = 0; j < 8; j++)
	{
		Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + Array[j + 8];
	}
	for(int j = 0; j < 4; j++)
	{
		Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + Array[j + 4];
	}
	for(int j = 0; j < 2; j++)
	{
		Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + Array[j + 2];
	}
	Array[0] = (((Array[0] << 63) & mask) | ((Array[0] >> 1) & (mask - 1))) + Array[1];
	for(int i = 0; i < long_size % 32; i++)
	{
		Array[0] = (((Array[0] << 63) & mask) | ((Array[0] >> 1) & (mask - 1))) + (*(sourceArray32s + pointer));
		pointer++;
	}
	mask = (long long)1 << 32;
	Sum = ((Array[0] >> 32) & (mask - 1)) + (Array[0] & (mask - 1));
	return Sum;
}