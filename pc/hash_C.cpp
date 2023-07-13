
int hash_C( long long* sourceArray32s, int dim)
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
/*
int Hash_C(int* a, int dim)
{
	int Array[64];
	for(int i = 0; i < 64; i++)
	{
		Array[i] = 0;
	}
	int Sum = 0;
	int mask = 1 << 31;
	int pointer = 0;
	for(int i = 0; i < dim / 64; i++)
	{
		for(int j = 0; j < 64; j += 2)
		{
			Array[j] = (((Array[j + 1] & 1) << 31) | ((Array[j] >> 1) & (mask - 1)));
			Array[j + 1] = (((Array[j] & 1) << 31) | ((Array[j + 1] >> 1) & (mask - 1)));
			Array[j] += *(a + pointer);
			Array[j + 1] += *(a + pointer + 1);
			pointer += 2;
		}
	}
	for(int j = 0; j < 32; j += 2)
	{
		Array[j] = (((Array[j + 1] & 1) << 31) | ((Array[j] >> 1) & (mask - 1)));
		Array[j + 1] = (((Array[j] & 1) << 31) | ((Array[j + 1] >> 1) & (mask - 1)));
		Array[j] += Array[j + 32];
		Array[j + 1] += Array[j + 33];
	}
	for(int j = 0; j < 16; j += 2)
	{
		Array[j] = (((Array[j + 1] & 1) << 31) | ((Array[j] >> 1) & (mask - 1)));
		Array[j + 1] = (((Array[j] & 1) << 31) | ((Array[j + 1] >> 1) & (mask - 1)));
		Array[j] += Array[j + 16];
		Array[j + 1] += Array[j + 17];
	}
	for(int j = 0; j < 8; j += 2)
	{
		Array[j] = (((Array[j + 1] & 1) << 31) | ((Array[j] >> 1) & (mask - 1)));
		Array[j + 1] = (((Array[j] & 1) << 31) | ((Array[j + 1] >> 1) & (mask - 1)));
		Array[j] += Array[j + 8];
		Array[j + 1] += Array[j + 9];
	}
	for(int j = 0; j < 4; j += 2)
	{
		Array[j] = (((Array[j + 1] & 1) << 31) | ((Array[j] >> 1) & (mask - 1)));
		Array[j + 1] = (((Array[j] & 1) << 31) | ((Array[j + 1] >> 1) & (mask - 1)));
		Array[j] += Array[j + 4];
		Array[j + 1] += Array[j + 5];
	}
	Array[0] = (((Array[1] & 1) << 31) | ((Array[0] >> 1) & (mask - 1)));
	Array[1] = (((Array[0] & 1) << 31) | ((Array[1] >> 1) & (mask - 1)));
	Array[0] += Array[2];
	Array[1] += Array[3];
	for(int i = 0; i < dim % 64; i += 2)
	{
		Array[0] = (((Array[1] & 1) << 31) | ((Array[0] >> 1) & (mask - 1)));
		Array[1] = (((Array[0] & 1) << 31) | ((Array[1] >> 1) & (mask - 1)));
		Array[0] += *(a + pointer);
		Array[1] += *(a + pointer + 1);
		pointer += 2;
	}
	Sum = Array[0] + Array[1];
	return Sum;

}
*/