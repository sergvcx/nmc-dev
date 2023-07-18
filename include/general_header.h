#ifdef __cplusplus
		extern "C" {
#endif

//-------------------------------------------------------------------------------------------------data-init------------------------
void makeShortArray (int* arrayPointer, int first, int last);
void fillArray (int* arrayPointer, int start, int end);
void randArray (int* arrayPointer, int size);
void initMatrices (int* initMatrix, int* nullResultMatrix, int* nullResultMatrix_C, int height, int width);

//-----------------------------------------------------------------------------------------------Abs-Hash---------------------------
void abs_16s ( int* sourseArray16s, int* resultArray32s, int dim );
int hashRep32 (long long* sourceArray32s, int dim);

//-----------------------------------------------------------------------------------------------Transpose--------------------------
void nmppsTranspose ( int* FirstMatrix, int* SecondMatrix, int Height, int Width );

//-------------------------------------------------------------------------------------------------MinMax---------------------------
void vecMinMaxRep32 ( int* minArray, int* maxArray, int dim );

#ifdef __cplusplus
	};
#endif