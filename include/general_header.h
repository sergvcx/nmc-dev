#ifdef __cplusplus
		extern "C" {
#endif

//-------------------------------------------------------------------------------------------------data-init------------------------
void makeShortArray (int* arrayPointer, int first, int last);
void fillArray (int* arrayPointer, int start, int end);
void randArray (int* arrayPointer, int size);
void initMatrices (int* initMatrix, int* nullResultMatrix, int* nullResultMatrix_C, int height, int width);

void transpose_C (int* matrica, int* result, int height, int width);
bool testTransposeCorrect (int* given_mtr, int* res_mtr, int* res_mtr_C, int height, int width);
bool testTransposeSizes (int* given_mtr, int* res_mtr, int* res_mtr_C, int height, int width);

//-----------------------------------------------------------------------------------------------Abs-Hash---------------------------
int abs_16s ( int* sourseArray16s, int* resultArray32s, int dim );
int hashRep32 (long long* sourceArray32s, int dim);

//-------------------------------------------------------------------------------------------------MinMax---------------------------
void minMaxMas_C ( int* a, int* b, int size );
int vecMinMaxRep32 ( int* a, int* b, int size );

//-----------------------------------------------------------------------------------------------Transpose--------------------------
int nmppsTranspose ( int* FirstMatrix, int* SecondMatrix, int Height, int Width );

#ifdef __cplusplus
	};
#endif