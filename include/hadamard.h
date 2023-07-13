#ifndef _HADAMARD_H_INCLUDED_
#define _HADAMARD_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif

#include "./nmtype.h"

    /**
    \defgroup 
    \ingroup 
    \brief
        \ru Функция инициализпции матрицы Адамара.
		\~

    \ru Функция инициализирует матрицу Адамара в каноничном виде.
		\~
		\~
    \param H
        \ru Адрес начала матрицы.
		\~
    \param dim
        \ru Количество строк или столбцов квадратной матрицы в элементах.
		\~
    \return \e void

    */
    //! \{
		void nmppsHadamardInit(nm2s* H, int dim);
    //! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        \ru Функция сортировки матрицы Адамара.
		\~

    \ru Функция сортирует матрицу Адамара в зависимости от количества переходов с 1 на -1 и наоборот в строке.
		\~
		\~
    \param srcNaturalOrderdMtr
        \ru Адрес начала матрицы Адамара.
		\~
    \param dstSequencyOrderedMtr
        \ru Адрес начала отсортированной матрицы Адамара (результата).
		\~
	\param dim
        \ru Количество строк или столбцов квадратной матрицы в элементах.
		\~
    \return \e void

    */
    //! \{
		void nmppsHadamardInitSort(nm2s* srcNaturalOrderdMtr, nm2s* dstSequencyOrderedMtr, int dim);
    //! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        \ru Функция преобразования Адамара.
		\~

    \ru Функция умножает преобразуемую матрицу на матрицу Адамара слева и справа.
		\~
		\~
    \param src
        \ru Адрес начала исходной матрицы.
		\~
    \param dst
        \ru Адрес начала результата преобразования.
		\~
	\param H
        \ru Адрес начала матрицы Адамара.
		\~
	\param temp
        \ru Адрес начала временного массива, равного по размеру исходной матрице.
		\~
	\param size
        \ru Количество строк или столбцов квадратной матрицы в элементах.
		\~
    \return \e void

    */
    //! \{
		void nmppsHadamard(nm32s* src, nm32s* dst, nm2s* H, nm32s* temp, int size);
    //! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        \ru Функция обратного преобразования Адамара.
		\~

    \ru Функция получает оригинальную матрицу после преобразования Адамара.
		\~
		\~
    \param src
        \ru Адрес начала исходной матрицы.
		\~
    \param dst
        \ru Адрес начала результата.
		\~
	\param H
        \ru Адрес начала матрицы Адамара.
		\~
	\param temp
        \ru Адрес начала временного массива, равного по размеру исходной матрице.
		\~
	\param size
        \ru Количество строк или столбцов квадратной матрицы в элементах.
		\~
    \return \e void

    */
    //! \{
		void nmppsHadamardInverse(nm32s* src, nm32s* dst, nm2s* H, nm32s* temp, int size);
    //! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        \ru Функция умножение матрицы на матрицу.
		\~

    \ru Функция умножает 2-разрядную матрицу на 32-разрядную.
		\~
		\~
    \param A
        \ru Адрес начала 2-разрядной матрицы.
		\~
    \param H
        \ru Количество строк 2-разрядной матрицы (определяет количество строк результата).
		\~
	\param W1
        \ru Количество столбцов 2-разрядной матрицы (равно количеству строк 32-разрядной).
		\~
	\param B
        \ru Адрес начала 32-рязрядной матрицы.
		\~
	\param C
        \ru Адрес результата.
		\~
	\param W2
        \ru Количество столбцов 32-разрядной матрицы (определяет количество столбцов результата).
		\~
    \return \e void

    */
    //! \{
		void nmppsMulMM_2s32s(nm2s* A, int H, int W1, nm32s* B, nm32s* C, int W2);
    //! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        \ru Функция умножение матрицы на 2 столбца другой матрицы.
		\~

    \ru Функция умножает 2-разрядную матрицу на 2 столбца 32-разрядной.
		\~
		\~
    \param A
        \ru Адрес начала 2-разрядной матрицы.
		\~
    \param H
        \ru Количество строк 2-разрядной матрицы.
		\~
	\param W1
        \ru Количество столбцов 2-разрядной матрицы.
		\~
	\param B
        \ru Адрес начала столбца 32-рязрядной матрицы.
		\~
	\param C
        \ru Адрес результата столбца.
		\~
	\param W2
        \ru Количество столбцов 32-разрядной матрицы (используется для смещения).
		\~
    \return \e void

    */
    //! \{
		void nmppsMulMM_2s32s_2col(nm2s* A, int H, int W1, nm32s* B, nm32s* C, int W2);
    //! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        \ru Функция получения хеш-суммы массива.
		\~

    \ru Функция получает хеш-сумму 64-разрядного массива в виде 32-разрядного числа.
		\~
		\~
    \param a
        \ru Адрес начала массива.
		\~
    \param size
        \ru Количество 64-разрядных элементов в массиве.
		\~
    \return \e unsigned

    */
    //! \{
		unsigned nmppsHash64u(long long * a, int size);
    //! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        \ru Функция транспонирования матрицы.
		\~

    \ru Функция меняет строки на столбцы в матрице.
		\~
		\~
    \param matrica
        \ru Адрес начала исходной матрицы.
		\~
    \param result
        \ru Адрес наачла транспонированной матрицы (результата).
		\~
	\param height
        \ru Количество строк исходной матрицы.
		\~
	\param width
        \ru Количество столбцов исходной матрицы.
		\~
    \return \e void

    */
    //! \{
		void nmppsTranspose(int* matrica, int* result, int height, int width)
    //! \}

#ifdef __cplusplus
	};
#endif
#endif // _HADAMARD_H_INCLUDED_
