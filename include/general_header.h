#ifdef __cplusplus
		extern "C" {
#endif

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        Функция заполнения массива значениями.
		\~

    	Функция заполняет int массив подряд идущими значениями от указанного числа до указанного числа, так что один элемент это два подряд идущих числа short.
		\~
		\~
    \param arrayPointer
        Адрес начала массива.
		\~
    \param first
        Значение с которого будет происходить заполнение.
		\~
	\param last
        Значение до которого будет происходить заполнение.
		\~
    \return \e void

    */
    //! \{
	void makeShortArray (int* arrayPointer, int first, int last);
	//! \}
	
//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        Функция заполнения массива случайными значениями.
		\~

    	Функция заполняет заданное количество элементов указанного массива случайными значениями из следующего диапазона:
	\f[
		\left( -(2^32); (2^32) - 1\right]
	\f]
		\~
		\~
    \param arrayPointer
        Адрес начала массива.
		\~
    \param size
        Количество элементов для заполнения.
		\~
    \return \e void

    */
    //! \{
	void randArray (int* arrayPointer, int size);
	//! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        Функция заполнения массива случайными значениями.
		\~

    	Функция заполняет заданное количество элементов указанного массива случайными значениями из следующего диапазона:
	\f[
		\left( 0.0; 8192.0\right]
	\f]
		\~
		\~
    \param arrayPointer
        Адрес начала массива.
		\~
    \param size
        Количество элементов для заполнения.
		\~
    \return \e void

    */
    //! \{
	void randFloatArray (float* arrayPointer, int size);
	//! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        Функция нахождения модуля.
		\~

    	Функция находит модуль 16-разрядных чисел и расширяет их до 32-разрядных, записывая результат в указанный массив.
		\~
		\~
    \param sourceArray16s
        Адрес начала исходного массива, каждое число которого воспринимается как два 16-разрядных.
		\~
    \param resultArray32s
        Адрес 32-разрядных чисел массива результата.
		\~
	\param dim
        Количество 16-разрядных чисел для обработки, размер массива-результата.
		\~
    \return \e void

    */
    //! \{
	void abs_16s ( int* sourseArray16s, int* resultArray32s, int dim );
	//! \}
	
//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        Функция получения хеш-суммы массива.
		\~

    	Функция считает хэш-сумму значений массива, обращаясь к его элементам как к 32-разрядным числам.
		\~
		\~
    \param sourceArray32s
        Адрес начала массива.
		\~
    \param dim
        Количество 32-разрядных элементов.
		\~
    \return \e int

    */
    //! \{
	int hashRep32 (long long* sourceArray32s, int dim);
	//! \}

//*****************************************************************************
    /**
    \defgroup 
    \ingroup 
    \brief
        Функция нахождения и перераспределения минимумов и максимумов.
		\~

    	Функция попарно обрабатывает элементы двух массивов. Минимальный из пары записывается в первый массив, а максимальный во второй.
		Во избежание некорректных результатов, вызванных переполнением, разница между минимумом и максимумом не должна перевышать следующего значения:
	\f[
		2^31 - 1
	\f]
		\~
		\~
    \param minArray
        Адрес массива где окажутся минимальные значения.
		\~
    \param maxArray
        Адрес массива где окажутся максимальные значения
		\~
	\param dim
        Размер матриц, количество элементов.
		\~
    \return \e void

    */
    //! \{
	void vecMinMaxRep32 ( int* minArray, int* maxArray, int dim );
	//! \}

#ifdef __cplusplus
	};
#endif