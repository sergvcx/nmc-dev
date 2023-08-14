#include "./primitive.h"
#include "./nmtype.h"

#ifdef __cplusplus
		extern "C" {
#endif

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief  Поэлементное сложение векторов с умножением на константу
    \~
            dstVec[i * 2] = (srcVec1[i * 2] + srcVec2[i * 2]) * nVal[0];
		    dstVec[i * 2 + 1] = (srcVec1[i * 2 + 1] + srcVec2[i * 2 + 1]) * nVal[1];  
    \param srcVec1  [in]  Входной вектор
    \param srcVec2  [in]  Входной вектор
    \param dstVec   [out] Результирующий вектор
	\param nVal     [in]  Указатель на константу-множитель
	\param srcCount [in]  Размер векторов в элементах. Четное число
    \return \e void
    */
    //! \{
    void nmppsAdd_MulC_32f( float* srcVec1, float* srcVec2, float* dstVec, float* nVal, int srcCount );
	//! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief  Формирование флагов вместимости для треугольников
    \param srcTriangles [in]  Указатель на входную структуру треугольников
    \param srcCount     [in]  Количество треугольников
    \param maxWidth     [in]  Ограничение по ширине
	\param maxHeight    [in]  Ограничение по высоте
	\param flags        [out] Массив флагов. Каждый элемент принимает значение 0 или 1
    \return \e void
    */
    //! \{
    void masks( TrianglePointers * srcTriangles, int srcCount, int maxWidth, int maxHeight, int * flags );
	//! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief  Сортировка треугольников в соответствии с флагами вместимости
    \param srcTriangles             [in]  Указатель на входную структуру треугольников
    \param srcCount                 [in]  Количество треугольников на вход
    \param toSplitTriangles         [out] Указатель на структуру треугольников для разбития
	\param toSplitTrianglesCount    [out] Указатель на количество треугольников для разбития
	\param resultTriangles          [out] Указатель на структуру выходных треугольников
	\param resultCount              [out] Указатель на количество выходных треугольников
	\param maxDstSize               [in]  Ограничение на максимальное количество выходных треугольников  
	\param flags                    [in]  Массив флагов вместимости для входных треугольников
    \return \e void
    */
    //! \{
    void sort( 	TrianglePointers * srcTriangles, int srcCount,
			    TrianglePointers * toSplitTriangles, int * toSplitTrianglesCount,
			    TrianglePointers * resultTriangles, int * resultCount,
			    int maxDstSize, int * flags );
	//! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief  Поэлементная сумма квадратов двух векторов 
    \param edgeArray    [out] Результирующий вектор
    \param dX           [in]  Входной вектор
    \param dY           [in]  Входной вектор
	\param edgeCount    [in]  Размер векторов в элементах
    \return \e void
    */
    //! \{
    void squareSum( float * edgeArray, float * dX, float * dY, int edgeCount );
	//! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief  Нахождение максимального значения из трех 
    \~
            Поэлементное нахождение максимального значения из трех векторов. Соответствующий номер вектора записывается в результат.
    \param maxEdgeArray [out] Результирующий вектор
    \param edge1        [in]  Входной вектор
    \param edge2        [in]  Входной вектор
	\param edge3        [in]  Входной вектор
	\param edgeCount    [in]  Размер векторов в элементах
    \return \e void
    */
    //! \{
    void maxEdge( int * maxEdgeArray, float * edge1, float * edge2, float * edge3, int edgeCount );
	//! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief  Разбиение треугольников на два
    \~
            Разбиение треугольников на два по середине наибольшей стороны и противолежащей вершине.
    \param toSplitTriangles         [in]  Указатель на входную структуру треугольников
    \param toSplitTrianglesCount    [in]  Количество входных треугольников
    \param splittedTriangles        [out] Указатель на структуру полученных треугольников
	\param splittedTrianglesCount   [out] Указатель на количество полученных треугольников
	\param srcTreatedCount          [in]  Указатель на количество разбитых треугольников
    \return \e void
    */
    //! \{
    void split( TrianglePointers * toSplitTriangles, int toSplitTrianglesCount,
                TrianglePointers * splittedTriangles, int * splittedTrianglesCount,
                int * srcTreatedCount );
	//! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief  Триангуляция массива треугольников 
    \param srcVertex        [in]  Указатель на входную структуру треугольников
    \param srcCount         [in]  Количество входных треугольников
    \param maxWidth         [in]  Ограничение по ширине
	\param maxHeight        [in]  Ограничение по высоте
	\param maxDstSize       [in]  Ограничение по выходному количеству треугольников
	\param dstVertex        [out] Указатель на выходную структуру треугольников
	\param srcTreatedCount  [out] Указатель на число разбитых треугольников
    \return \e void
    */
    //! \{
    void triangulation(	TrianglePointers* srcVertex, int srcCount,
						int maxWidth, int maxHeight,
						int maxDstSize, TrianglePointers* dstVertex,
						int* srcTreatedCount );
	//! \}

#ifdef __cplusplus
	};
#endif