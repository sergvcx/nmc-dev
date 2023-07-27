#ifdef __cplusplus
		extern "C" {
#endif

#include "./nmtype.h"

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        Функция транспонирования матрицы.
		\~

    	Функция транспонирует матрицу заданных четных размеров, состоящую из 32-разрядных чисел.
		\~
		\~
    \param srcMatrix
        Адрес исходной матрицы.
		\~
    \param dstMatrix
        Адрес матрицы-результата, куда запишется транспонированная исходная матрица.
		\~
	\param height
        Высота изначальной матрицы в элементах. Четное число.
		\~
	\param width
        Ширина изначальной матрицы в элементах. Четное число.
		\~
    \return \e void

    */
    //! \{
	void nmppmTranspose_32s (const nm32s* srcMatrix , int* dstMatrix, int height, int width );
	//! \}

#ifdef __cplusplus
    };
#endif