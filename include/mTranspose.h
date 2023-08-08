#ifdef __cplusplus
		extern "C" {
#endif

#include "./nmtype.h"

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief    Функция транспонирования матрицы
    \param srcMatrix [in]  Исходная матрица
    \param dstMatrix [out] Результирующая траспонированая матрица
	\param height    [in] Высота входной матрицы в элементах. Кратно плотности элементов
	\param width     [in] Ширина входной матрицы в элементах. Кратно плотности элементов
    \return \e void

    */
    //! \{
	void nmppmTranspose_32s(const nm32s* srcMatrix ,nm32s* dstMatrix, int height, int width);
	void nmppmTranspose_16s(const nm16s* srcMatrix, nm16s* dstMatrix, int height, int width);
	void nmppmTranspose_16s_Lines(const nm16s* srcMatrix, nm16s* dstMatrix, int height, int width);
	//! \}

#ifdef __cplusplus
    };
#endif