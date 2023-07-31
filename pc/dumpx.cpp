#include "stdio.h"
#include "stdlib.h"
#include "string.h"
extern "C"{
	
unsigned getval_xu(void* p, int index,int sizeOf){
	//                  0 1 2 3,4 
	static int shift[]={0,2,1,0,0};
	unsigned * pp=(unsigned*)p;
	unsigned sh=shift[sizeOf];
	unsigned index_hi= index>>sh;
	unsigned index_lo= index-(index_hi<<sh);
	unsigned val=pp[index_hi];
	val<<=(32-((index_lo+1)*(sizeOf*8)));
	val>>=(32-(1*(sizeOf*8)));
	return val;
}
int getval_xs(void* p, int index,int sizeOf){
	//                  0 1 2 3,4 
	static int shift[]={0,2,1,0,0};
	int * pp=(int*)p;
	int sh=shift[sizeOf];
	int index_hi= index>>sh;
	int index_lo= index-(index_hi<<sh);
	int val=pp[index_hi];
	val<<=(32-((index_lo+1)*(sizeOf*8)));
	val>>=(32-(1*(sizeOf*8)));
	return val;
}

// convert int (0..99) to string
char* itoa99(int val, char* buffer){
	if (val<10)
		*buffer++='0'+val;
	else {
		int v=val/10;
		*buffer++='0'+v;
		*buffer++='0'+val-v*10;
	}
	
	*buffer=0;
	return buffer;
}

int min_len(char* format){
	int minlen=0;
	char* p=format;
	char c;
	while (*p!=0){
		if (*p++=='%')
			break;
		minlen++;
	}
	while ((c=*p++)!=0){
		if (c=='d' || c=='x' ||  c=='X' || c=='e' || c=='f')
			break;
	}
	while (*p++!=0){
		minlen++;
	}
	return minlen;
}

// modify format string to make aligned
void align_format(char * format, char* new_format, int maxlen){
	char *f=format;
	char *maxf=new_format;
	do{
		*maxf++=*f;
		if (*f++=='%'){
			if (*f=='0'){
				*maxf++=*f++;
				if (*f>='1' && *f<='9'){
					strcpy(new_format,format);
					return;
				}
			}
			maxf=itoa99(maxlen,maxf);
		}
	}
	while (*(f-1)!=0);
	//printf("new_format=%s\n",new_format);
			
}

int dump_xs(char* format,void* m, int height, int width, int stride, int mode, int sizeOf){
	int maxlen=0;
	int minlen=min_len(format);
	char str[32];
	char max_format[32];

	// search for longest string
	int* row=(int*)m;
	if (sizeOf==1)
		stride>>2;
	else if (sizeOf==2)
		stride>>=1;
	else if (sizeOf==4)
		;
	else 
		printf("error: sizeOf must be 1,2 or 4\n") ;
	for(int i=0; i<height; i++,row+=stride){
		for(int j=0; j<width; j++){
			int val=getval_xs(row,j,sizeOf);
			sprintf(str,format,val);
			int len = strlen(str);
			if (len>maxlen) maxlen=len;
		}
	}
	maxlen-=minlen;
	align_format(format,max_format,maxlen);
	
	// print matrix with aligned format string
	row=(int*)m;
	for(int i=0; i<height; i++,row+=stride){
		if (mode==1)
			printf("%p: ",row);
		else if (mode==2)
			printf("%4d: ",i);
		for(int j=0; j<width; j++){
			int val=getval_xs(m,j,sizeOf);
			printf(max_format,val);
		}
		printf("\n");
	}
	return maxlen;
}

int dump_xu(char* format,void* m, int height, int width, int stride, int mode, int sizeOf){
	int maxlen=0;
	int minlen=min_len(format);
	char str[32];
	char max_format[32];

	// search for longest string
	unsigned* row=(unsigned*)m;
	if (sizeOf==1)
		stride>>2;
	else if (sizeOf==2)
		stride>>=1;
	else if (sizeOf==4)
		;
	else 
		printf("error: sizeOf must be 1,2 or 4\n") ;
	
	for(int i=0; i<height; i++,row+=stride){
		for(int j=0; j<width; j++){
			unsigned val=getval_xu(row,j,sizeOf);
			sprintf(str,format,val);
			int len = strlen(str);
			if (len>maxlen) maxlen=len;
		}
	}
	maxlen-=minlen;
	align_format(format,max_format,maxlen);
	
	// print matrix with aligned format string
	row=(unsigned*)m;
	for(int i=0; i<height; i++, row+=stride){
		if (mode==1)
			printf("%p: ",row);
		else if (mode==2)
			printf("%4d: ",i);
		for(int j=0; j<width; j++){
			unsigned val=getval_xu(m,i*stride+j,sizeOf);
			printf(max_format,val);
		}
		printf("\n");
	}
	return maxlen;
}


	
int dump_8u(char* format, void* m, int height, int width, int stride, int mode){
	return dump_xu(format, m, height, width, stride, mode, 1);
}
int dump_8s(char* format, void* m, int height, int width, int stride, int mode){
	return dump_xs(format, m, height, width, stride, mode, 1);
}

int dump_16u(char* format,void* m, int height, int width, int stride, int mode){
	return dump_xu(format,m, height, width, stride, mode ,2);
}
int dump_16s(char* format,void* m, int height, int width, int stride, int mode){
	return dump_xs(format,m, height, width, stride, mode, 2);
}

int dump_32s(char* format, void* m, int height, int width, int stride, int mode){
	return dump_xu(format, m, height, width, stride,  mode, 4);
}
int dump_32u(char* format, void* m, int height, int width, int stride, int mode){
	return dump_xs(format, m, height, width, stride,  mode, 4);
}

int dump_64u(char* format,void* m, int height, int width, int stride, int mode){
	int maxlen=0;
	int minlen=min_len(format);
	char str[32];
	char max_format[32];

	// search for longest string
	unsigned long long* row=(unsigned long long*)m;
	for(int i=0; i<height; i++, row+=stride){
		for(int j=0; j<width; j++){
			sprintf(str,format,row[j]);
			int len = strlen(str);
			if (len>maxlen) maxlen=len;
		}
	}
	maxlen-=minlen;
	align_format(format,max_format,maxlen);
	
	// print matrix with aligned format string
	row=(unsigned long long*)m;
	for(int i=0; i<height; i++,row+=stride){
		if (mode==1)
			printf("%p: ",row);
		else if (mode==2)
			printf("%4d: ",i);
		for(int j=0; j<width; j++)
			printf(max_format,row[j]);
		printf("\n");
	}
	return maxlen;
}
int dump_64s(char* format,void* m, int height, int width, int stride, int mode){
	int maxlen=0;
	int minlen=min_len(format);
	char str[32];
	char max_format[32];

	// search for longest string
	long long* row=(long long*)m;
	for(int i=0; i<height; i++, row+=stride){
		for(int j=0; j<width; j++){
			sprintf(str,format,row[j]);
			int len = strlen(str);
			if (len>maxlen) maxlen=len;
		}
	}
	maxlen-=minlen;
	align_format(format,max_format,maxlen);
	
	// print matrix with aligned format string
	row=(long long*)m;
	for(int i=0; i<height; i++,row+=stride){
		if (mode==1)
			printf("%p: ",row);
		else if (mode==2)
			printf("%4d: ",i);
		for(int j=0; j<width; j++)
			printf(max_format,row[j]);
		printf("\n");
	}
	return maxlen;
}

int dump_32f(char* format, float* m, int height, int width, int stride,int mode){
	int maxlen=0;
	int minlen=min_len(format);
	char str[32];
	char max_format[32];

	// search for longest string
	float* row=(float*)m;
	for(int i=0; i<height; i++,row+=stride){
		for(int j=0; j<width; j++){
			sprintf(str,format,row[j]);
			int len = strlen(str);
			if (len>maxlen) maxlen=len;
		}
	}
	maxlen-=minlen;
	align_format(format,max_format,maxlen);
	
	// print matrix with aligned format string
	row=(float*)m;
	for(int i=0; i<height; i++,row+=stride){
		if (mode==1)
			printf("%p: ",row);
		else if (mode==2)
			printf("%4d: ",i);
		for(int j=0; j<width; j++)
			printf(max_format,row[j]);
		printf("\n");
	}
	return maxlen;
}
};
