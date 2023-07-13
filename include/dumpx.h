extern "C"{

int dump_8u  ( const char* format,void* m, int height, int width, int stride, int mode);
int dump_16u ( const char* format,void* m, int height, int width, int stride, int mode);
int dump_32u ( const char* format,void* m, int height, int width, int stride, int mode);
int dump_64u ( const char* format,void* m, int height, int width, int stride, int mode);
																			
int dump_8s  ( const char* format,void* m, int height, int width, int stride, int mode);
int dump_16s ( const char* format,void* m, int height, int width, int stride, int mode);
int dump_32s ( const char* format,void* m, int height, int width, int stride, int mode);
int dump_64s ( const char* format,void* m, int height, int width, int stride, int mode);

int dump_32f ( const char* format,float* m,int height, int width, int stride, int mode);
int dump_64f ( const char* format,void* m, int height, int width, int stride, int mode);
};
