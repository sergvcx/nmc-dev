
//---------------------------------------------------------Abs-Hash-NM----------------------
extern "C" int mod ( int* x, int* y );
extern "C" int abs_16s ( int* x, int* y , int size );
extern "C" int hash ( int* x, int size );
extern "C" int hashRep32 ( int* x, int size );

void abs_16s_C(int* a, int* b, int size);
void compareAbs(int* A, int* B, int* C, long* D);
bool testAbsSizes(int* sourceArray16s, int* resultArray32s, int* resultArray32s_C);

int sumArray(int* a, int size);
bool tupoCompare(int* a, int* b, int size);
int hash_C(int* a, int size);
int hashMimic(long* a, int size);
int sumHash();
void testHash();
void printIntegerLikeTwoShort(int a);

//-------------------------------------------------------------------------------------------------Abs-Hash-x86---------------------
void abs_16s_C(int* a, int* b, int size);
//int Hash_C(int* a, int size);
int hash_C(long long* a, int size);

//-------------------------------------------------------------------------------------------------fill-array-----------------------
void makeShortArray(int* a, int first, int last);
void fillArray(int* a, int start, int end);
void randArray(int* a, int size);

//-------------------------------------------------------------------------------------------------MinMax---------------------------
extern "C" int minMax ( int* a, int* b );
extern "C" int minMaxMas ( int* a, int* b, int size );
extern "C" int logMinMaxMas ( int* a, int* b, int size );

void minMax_C ( int* a, int* b );
void minMaxMas_C ( int* a, int* b, int size );

extern "C" int vecMinMaxMas ( int* a, int* b, int size );
extern "C" int vecMinMaxRep32 ( int* a, int* b, int size );

//-----------------------------------------------------------------------------------------------Transpose--------------------------
extern "C" int transpose_2x2 ( int* FirstMatrix, int* SecondMatrix );
extern "C" int transpose_3x3_32s ( int* FirstMatrix, int* SecondMatrix );
extern "C" int transpose_3x3_RISC_32s ( int* FirstMatrix, int* SecondMatrix );
extern "C" int transpose_4x4 ( int* FirstMatrix, int* SecondMatrix );
extern "C" int transpose_64x64 ( int* FirstMatrix, int* SecondMatrix );
extern "C" int transpose_64x64_Mask_bL ( int* FirstMatrix, int* SecondMatrix );
extern "C" int transpose_64x64_Mask_bC ( int* FirstMatrix, int* SecondMatrix );
extern "C" int transposeEvenSizes_32s ( int* FirstMatrix, int* SecondMatrix, int Height, int Width );

void initMatrices(int* initMatrix, int* nullResultMatrix, int* nullResultMatrix_C, int height, int width);
void transpose_C(int* matrica, int* result, int height, int width);
bool testTransposeCorrect(int* given_mtr, int* res_mtr, int* res_mtr_C, int height, int width);
bool testTransposeSizes(int* given_mtr, int* res_mtr, int* res_mtr_C, int height, int width);
