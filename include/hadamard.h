#ifndef _HADAMARD_H_INCLUDED_
#define _HADAMARD_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif

#include "./nmtype.h"

/**
    \defgroup Hadamard
    \brief Функции преобразования Адамара
*/

/**
    \defgroup MulMM
    \brief Функции перемножения матриц
*/

/**
    \defgroup Hash64
    \brief Функция вычисления контрольной суммы
*/

    /**
    \ingroup Hadamard
    \brief
        Функция инициализпции матрицы Адамара.
		\~

    Функция инициализирует матрицу Адамара в каноничном виде.

	\f[
		H_{2^{k}} =\begin{bmatrix}
		H_{2^{k-1}} & H_{2^{k-1}}\\
		H_{2^{k-1}} & -H_{2^{k-1}}
		\end{bmatrix}
	\f]
		\~
		\~
    \param H
        Адрес начала матрицы.
		\~
    \param dim
        Количество строк или столбцов квадратной матрицы в элементах.
		\~
    \return \e void

    */
    //! \{
		void nmppsHadamardInit(nm2s* H, int dim);
    //! \}

//*****************************************************************************
    /**
    \ingroup Hadamard
    \brief
        Функция сортировки матрицы Адамара.
		\~

    Функция сортирует матрицу Адамара в зависимости от количества переходов с 1 на -1 и наоборот в строке.
		\~
		\~
    \param srcNaturalOrderdMtr
        Адрес начала матрицы Адамара.
		\~
    \param dstSequencyOrderedMtr
        Адрес начала отсортированной матрицы Адамара (результата).
		\~
	\param dim
        Количество строк или столбцов квадратной матрицы в элементах.
		\~
    \return \e int код ошибки

    */
    //! \{
		int nmppsHadamardInitSort(const nm2s* srcNaturalOrderdMtr, nm2s* dstSequencyOrderedMtr, int dim);
    //! \}

//*****************************************************************************
    /**
    \ingroup MulMM
    \brief
        Функция умножения матрицы на матрицу.
		\~

    Функция умножает 2-разрядную матрицу на 32-разрядную.
		\~
		\~
    \param A
        Адрес начала 2-разрядной матрицы.
		\~
    \param H
        Количество строк 2-разрядной матрицы (определяет количество строк результата).
		\~
	\param W1
        Количество столбцов 2-разрядной матрицы (равно количеству строк 32-разрядной).
		\~
	\param B
        Адрес начала 32-рязрядной матрицы.
		\~
	\param C
        Адрес результата.
		\~
	\param W2
        Количество столбцов 32-разрядной матрицы (определяет количество столбцов результата).
		\~
    \return \e void

    */
    //! \{
		void nmppsMulMM_2s32s(nm2s* A, int H, int W1, nm32s* B, nm32s* C, int W2);
		void nmppsMulMM_2s16s(nm2s* A, int H, int W1, nm16s* B, nm16s* C, int W2);
    //! \}

//*****************************************************************************
    /**
    \ingroup MulMM
    \brief
        Функция умножения матрицы на 2 столбца другой матрицы.
		\~

    Функция умножает 2-разрядную матрицу на 2 столбца 32-разрядной.
		\~
		\~
    \param A
        Адрес начала 2-разрядной матрицы.
		\~
    \param H
        Количество строк 2-разрядной матрицы.
		\~
	\param W1
        Количество столбцов 2-разрядной матрицы.
		\~
	\param B
        Адрес начала столбца 32-рязрядной матрицы.
		\~
	\param C
        Адрес результата столбца.
		\~
	\param W2
        Количество столбцов 32-разрядной матрицы (используется для смещения).
		\~
    \return \e void

    */
    //! \{
		void nmppsMulMM_2s32s_2col(nm2s* A, int H, int W1, nm32s* B, nm32s* C, int W2);
		void nmppsMulMM_2s16s_4col(nm2s* A, int H, int W1, nm16s* B, nm16s* C, int W2);
    //! \}

//*****************************************************************************
    /**
    \ingroup Hash64
    \brief
        Функция получения хеш-суммы массива.
		\~

    Функция получает хеш-сумму 64-разрядного массива в виде 32-разрядного числа. Учитывает порядок элементов.
		\~
		\~
    \param a
        Адрес начала массива.
		\~
    \param size
        Количество 64-разрядных элементов в массиве.
		\~
    \return \e unsigned

    */
    //! \{
		unsigned nmppsHash64u(long long * a, int size);
    //! \}

//*****************************************************************************
    /**
    \ingroup Hadamard
    \brief
        Функция преобразования Адамара.
		\~

    Функция умножает преобразуемую матрицу на матрицу Адамара слева и справа.
		\~
		\~
    \param src
        Адрес начала исходной матрицы.
		\~
    \param dst
        Адрес начала результата преобразования.
		\~
	\param H
        Адрес начала матрицы Адамара.
		\~
	\param temp
        Адрес начала временного массива, равного по размеру исходной матрице.
		\~
	\param size
        Количество строк или столбцов квадратной матрицы в элементах.
		\~
    \return \e void

    */
    //! \{
		void nmppsHadamard(nm32s* src, nm32s* dst, nm2s* H, nm32s* temp, int size);
		void nmppsHadamard_16s(nm16s* src, nm16s* dst, nm2s* H, nm16s* temp, int size);
    //! \}

//*****************************************************************************
    /**
    \ingroup Hadamard
    \brief
        Функция обратного преобразования Адамара.
		\~

    Функция получает оригинальную матрицу после преобразования Адамара.

	\f[
		dst=H\cdotp src\cdotp H
	\f]
		\~
		\~
    \param src
        Адрес начала исходной матрицы.
		\~
    \param dst
        Адрес начала результата.
		\~
	\param H
        Адрес начала матрицы Адамара.
		\~
	\param temp
        Адрес начала временного массива, равного по размеру исходной матрице.
		\~
	\param size
        Количество строк или столбцов квадратной матрицы в элементах.
		\~
    \return \e void

    */
    //! \{
		void nmppsHadamardInverse(nm32s* src, nm32s* dst, nm2s* H, nm32s* temp, int size);
		void nmppsHadamardInverse_16s(nm16s* src, nm16s* dst, nm2s* H, nm16s* temp, int size);
    //! \}

//*****************************************************************************
	/**
    \defgroup nmppsAbs2 nmppsAbs2
    \ingroup vArithmetics
    \brief
        \ru Функция вычисления абсолютных элементов вектора.
        \en Calculation of absolute values for vec elements.

		\~

	\f[
        b[ i] =\begin{cases}
			a[ i] , & if\ a[ i] \geq 0\\
			-a[ i] , & if\ 0 >a[ i]  >-2^{n-1}\\
			2^{n-1} -1, & if\ a[ i] =-2^{n-1}
		\end{cases}
    \f]

	\f[ i = \overline{0 \ldots size-1} \f]

	n - разрядность элементов.

    \param a
        \ru Входной вектор.
        \en Input vec.
		\~
    \param size
        \ru Размер векторов в элементах.
        \en Vector size in elements.
		\~
    \retval b
        \ru Результирующий вектор.
        \en The result vec.
		\~
    \return \e void
    */
    //! \{
void nmppsAbs2_8s( nm8s *srcA, nm8s *dstB, int size);
void nmppsAbs2_16s( nm16s *srcA, nm16s *dstB, int size);
void nmppsAbs2_32s( nm32s *srcA, nm32s *dstB, int size);
void nmppsAbs2_64s( nm64s *srcA, nm64s *dstB, int size);
    //! \}
	
//*****************************************************************************
	/**
    \defgroup nmppsMinMax nmppsMinMax
    \ingroup vArithmetics
    \brief
        Функция для выделения минимумов и максимумов среду пар в отдельные массивы.
		\~
	
	Во избежание некорректных результатов, вызванных переполнением, рекомендуется использовать числа из следующего диапазона:

	\f[
		\left( 2^{n-1} ;-2^{n-1}\right]
	\f]

	n - разрядность чисел

    \param srcA
        Первый входной вектор.
		\~
	\param srcВ
        Второй входной вектор.
		\~
    \retval dstMin
        Результирующий вектор для минимумов.
		\~
	\retval dstMax
        Результирующий вектор для максимумов.
		\~
    \param size
        Размер векторов в элементах.
		\~
    \return \e void
    */
    //! \{
void nmppsMinMax_8s( nm8s *srcA, nm8s *srcB, nm8s *dstMin, nm8s *dstMax, int size);
void nmppsMinMax_16s( nm16s *srcA, nm16s *srcB, nm16s *dstMin, nm16s *dstMax, int size);
void nmppsMinMax_32s( nm32s *srcA, nm32s *srcB, nm32s *dstMin, nm32s *dstMax, int size);
void nmppsMinMax_64s( nm64s *srcA, nm64s *srcB, nm64s *dstMin, nm64s *dstMax, int size);
    //! \}

#ifdef __cplusplus
	};
#endif
#endif // _HADAMARD_H_INCLUDED_
