extern "C" unsigned nmppsHash64u(long long * a, int size) {
	int s = size;
	long long * t = a;
	long long hash = 0;
	long long h[32];
	for (int i = 0; i < 32; i++) {
		h[i] = 0;
	}
	
	for (; s > 31 ; s -= 32) {
		for (int i = 0; i < 32; i++) {
			h[i] = ((h[i]>>1)&0x7fffffffffffffff) | (h[i]<<63);
			h[i] = t[i] + h[i];
		}
		t += 32;
	}
	
	for (int i = 0; i < 32; i++) {
		hash += h[i];
	}
	
	for (; s > 0 ; s--) {
		hash = ((hash>>1)&0x7fffffffffffffff) | (hash<<63);
		hash = *t + hash;
		t++;
	}
	
	hash = (hash) + (hash>>32);
	return (int) hash;
}