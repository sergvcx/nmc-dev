//------------------------------------------------------------------------
//
//
//  Neuro Matrix Performance Primitives
//
//  Copyright (c) RC Module
//
//!
//! \author S.Mushkaev
//! \brief  функции переупорядочивания данных
//!
//!
//------------------------------------------------------------------------
#ifndef _VTRANSFORM_H_INCLUDED_
#define _VTRANSFORM_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif

	/**
	\defgroup VEC_QSort VEC_QSort
	\ingroup vTransform
	\brief
		\ru Сортировка массива по убыванию.
		\en Descending sort of an array.
		\~
	\param	pSrcDstVec
		\ru Входной и результирующий вектор.
		\en Input and result vec.
		\~
	\param	nSize
		\ru Размер вектора в элементах.
		\en Vector size in elements.
		\~
	\return \e void

	\restr
		\ru Функция работает рекурсивно, передавая параметры через стек,
			поэтому размер стека должен быть больше 4*log2(nSize) 32-битных слов
			в лучшем случае (элементы массива расположены беспорядочно)
			и больше 6*nSize 32-битных слов в худшем случае
			(элементы массива уже упорядочены)
		\en The function operates recursively and transfers elements using the stack.
			That is why the stack size should be greater than 4*log2(nSize) 32-bit words
			at best (elements of the array are located at random) and greater than 6*nSize 32-bit words
			at worst (elements of the array are already ordered)
		\~
	\par
	\xmlonly
		<testperf>
			<init>
				nmppsRandUniform_32u((nm32u*)im0,1024);
				nmppsRShiftC_32s((nm32s*)im0, 1, (nm32s*)im0, 1024);
				nmppsRandUniform_32u((nm32u*)im1,1024);
				nmppsRShiftC_32s((nm32s*)im1, 1, (nm32s*)im1, 1024);
			 </init>
			 <param name="pSrcDstVec"> im0 im1 	  	</param>
			 <param name="nSize"> 256 	</param>
		</testperf>
		<testperf>
			<init>
				nmppsRandUniform_32u((nm32u*)im1,1024);
				nmppsRShiftC_32s((nm32s*)im1, 1, (nm32s*)im1, 1024);
			 </init>
			 <param name="pSrcDstVec"> im1 </param>
			 <param name="nSize"> 8 128 256 </param>
		</testperf>
	\endxmlonly

	*/
	//! \{
void nmppsQSort_32s(nm32s* pSrcDstVec, int nSize);
	//! \}

//*****************************************************************************

	/**
	\defgroup nmppsRemap_ nmppsRemap_
	\ingroup vTransform
	\brief
		\ru Переупорядочивание элементов вектора по таблице.
		\en Reodering of vector eements by table .

		\~

	\f[
		pDstVec[i]=pSrcVec[pRemapTable[i]],
	\f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

		\~
	\param pSrcVec
		\ru Входной вектор.
		\en Input vec.
		\~
	\param pRemapTable
		\ru Таблица новых индексов для переупорядочивания.
		\en Index reordering table.
		\~
	\param nDstVecSize
		\ru Размер результирующего вектора в элементах.
		\en Size in elements for destination vec.
		\~
	\param pTmpBuf1
		\ru Временный массив nm32u pTmpBuf1[nSrcVecSize].
		\en Temporary buffer nm32u pTmpBuf1[nSrcVecSize].
		\~
	\param pTmpBuf2
		\ru Временный массив nm32u pTmpBuf2[nDstVecSize].
		\en Temporary buffer nm32u pTmpBuf2[nDstVecSize].


	\retval pDstVec
		\ru Результирующий вектор nm8u pDstVec[nDstVecSize].
		\en Result vec nm8u pDstVec[nDstVecSize].

		\~
	\return \e void

	\code
		// Функция
		// void nmppsRemap_8u(nm8u* pSrcVec, nm8u* pDstVec, nm32s* pRemapTable, int nSrcVecSize, int nDstVecSize, void* pTmpBuf1, void* pTmpBuf2);
		// выполняет следющие действия:
		nmppsConvert_8u((nm8u*) pSrcVec, (nm32u*)pTmpBuf1,nSrcVecSize);
		nmppsRemap_32u((nm32u*)pTmpBuf1,(nm32u*)pTmpBuf2,RemapTable,DstVecSize);
		nmppsConvert_32s((nm32s*)pTmpBuf2,(nm8s*) pDstVec, DstVecSize);
	\endcode

	\note
		\ru Возможность использования inplace параметров определяется исходя из
			последовательности процессов чтения/записи: \n
		\en Possible using of in place parameters can be determined from
		\~
			the folowing sequence of actions : \n
		\~ - pSrcVec => pTmpBuf1 - \ru inplace запрещен; \n
								   \en inplace is not valid; \n
		\~ - pTmpBuf1=>pTmpBuf2 -  \ru inplace запрещен; \n
								   \en inplce is not valid; \n
		\~ - pTmpBuf2=>pDstVec  -  \ru inplace разрешен; \n
								   \en inplace is not valid; \n


	\par
	\xmlonly
		<testperf>
			 <param name="pSrcVec"> im0 im1  </param>
			 <param name="pDstVec"> im0 im1  </param>
			 <param name="pRemapTable"> im2 im3  </param>
			 <param name="nDstVecSize"> 2048 </param>
		</testperf>
		<testperf>
			 <param name="pSrcVec"> im0 </param>
			 <param name="pDstVec"> im1 </param>
			 <param name="pRemapTable"> im2 </param>
			 <param name="nDstVecSize"> 8 128 1024 2048 </param>
		</testperf>
	\endxmlonly
	*/
	//! \{
void nmppsRemap_32u(nm32u* pSrcVec, nm32u* pDstVec, nm32s* pRemapTable, int nDstVecSize);
void nmppsRemap_8u(nm8u* pSrcVec, nm8u* pDstVec, nm32s* pRemapTable, int nSrcVecSize, int nDstVecSize, void* pTmpBuf1, void* pTmpBuf2);
	//! \}




	/**
	\internal
	\defgroup Manipulation Manipulation
	\ingroup vTransform
	\brief
		\ru Расщепление массива на несколько отдельных массивов
		\en Array splitting to several arrays

		\~

	\f[ pDst4Vec[i][j]=pSrcVec[j][i] \f]
	\~
	\param pSrcVec
		\ru Входной вектор.
		\en Input vec.
		\~
	\param pDst4Vec
		\ru Массив из 4 указателей на отдельные массивы
		\en Array of 4 pointers to separeted arrays
		\~
	\param nSize
		\ru Размер массивов
		\en Size of arrays

		\~
	\par
	\xmlonly
		<testperf>
			<param name="pSrcVec"> im0 im1 	</param>
			<param name="pDstVec"> im0 im1 	</param>
			<param name="nSize"> 1024 4096 </param>
		</testperf>
	\endxmlonly

	\todo 	Impelenment NM versin of nmppsSplit_(v4nm16s* pSrcVec, nm16s** pDst4Vec, int nSize);

	*/
	//! \{
void nmppsSplit_(v4nm16s* pSrcVec, nm16s** pDst4Vec, int nSize);
	//! \}


	/**
		\defgroup nmppSplitTmp nmppSplitTmp
		\ingroup vTransform

	 *  \brief Расщепляет массив на два, группируя по четным и нечетным элементам
	 *
	 *  \param [in]  src  Входной массив
	 *  \param [out] dst1 Выходной массив размера size/2
	 *  \param [out] dst2 Выходной массив размера size/2
	 *  \param [in]  size Размер исходного массива в элементах. Кратность параметра size должна соответствовать двум длинным 64-р. словам.
	 *  \param [in]  tmpSizeOfDst Временный массив размера size/2
	 *  \return
	 *
	 *  \details Details
	 *  Максимальная производительность достигается при размещении входных, выходных и временных массивов в разных банках памяти. Массивы dst1 и dst2 могут находится в одном банке.
	 *  Макс  производительность  на 64-р. слово результата = 2.1 такта (при size=10240 байт) и 2.5 такта (при size=4096 байт)
	 */
	 //! \{
	void nmppsSplitTmp_8s(const nm8s* src, nm8s* dst1, nm8s* dst2, int size, nm8s* tmpSizeOfDst);
	 //! \}
   /**
		\defgroup nmppSplit nmppSplit
		\ingroup vTransform

	 *  \brief Расщепляет массив на два массива, группируя по четным и нечетным элементам
	 *
	 *  \param [in]  src  Входной массив
	 *  \param [out] dst1 Выходной массив размера sizeSrc/2
	 *  \param [out] dst2 Выходной массив размера sizeSrc/2
	 *  \param [in]  sizeSrc Размер входного массива в элементах. Кратность параметра sizeSrc должна быть равна плотности элементов в 64-р. слове.
	 *  \return
	 *
	 *  \details Details
	 *  Максимальная производительность достигается при размещении входных, выходных массивов в разных банках памяти. Массивы dst1 и dst2 могут находится в одном банке.
	 *  Макс  производительность  на 64-р. слово результата = 2.14 такта (при sizeSrc=10240 байт) и 2.6 такта (при sizeSrc=4096 байт)
	 */
	 //! \{
	void nmppsSplit_8s (const nm8s* src,  nm8s*  dst1, nm8s*  dst2, int sizeSrc);
	void nmppsSplit_16s(const nm16s* src, nm16s* dst1, nm16s* dst2, int sizeSrc);
	void nmppsSplit_32s(const nm32s* src, nm32s* dst1, nm32s* dst2, int sizeSrc);
	 //! \}
   /**
		\defgroup nmppMerge nmppMerge
		\ingroup vTransform

	 *  \brief Собирает массив из двух, чередуя элементы из каждого. Функция обратная nmppsSplit
	 *
	 *  \param [in]  src0 Входной массив  размера sizeSrc
	 *  \param [in]  src1 Входной массив  размера sizeSrc
	 *  \param [out] dst  Выходной массив размера 2*sizeSrc
	 *  \param [in]  sizeSrc Размер входного массива в элементах. Должен быть кратен плотности элементов.
	 *  \return
	 *
	 *  \details Details
	 */
	 //! \{
	void nmppsMerge_8s (const nm8s*  src0, const nm8s*  src1, nm8s*  dst, int sizeSrc);
	void nmppsMerge_16s(const nm16s* src0, const nm16s* src1, nm16s* dst, int sizeSrc);
	void nmppsMerge_32s(const nm32s* src0, const nm32s* src1, nm32s* dst, int sizeSrc);
	 //! \}

	/**
		\defgroup nmppMerge4to1 nmppMerge
		\ingroup vTransform

	 *  \brief Собирает массив из четырех массивов, чередуя элементы от каждого. Функция обратная nmppsSplit1to4
	 *
	 *  \param [in]  src0 Входной массив  размера sizeSrc
	 *  \param [in]  src1 Входной массив  размера sizeSrc
	 *  \param [in]  src2 Входной массив  размера sizeSrc
	 *  \param [in]  src3 Входной массив  размера sizeSrc
	 *  \param [out] dst  Выходной массив размера 4*sizeSrc
	 *  \param [in]  sizeSrc Размер входного массива в элементах. Должен быть кратен плотности элементов.
	 *  \return
	 *
	 *  \details Details
	 */
	 //! \{
	//void nmppsMerge4_8s (const nm8s*  src0, const nm8s*  src1,const nm8s*  src2, const nm8s*  src3, nm8s*  dst, int sizeSrc);
	void nmppsMerge4_16s(const nm16s* src0, const nm16s* src1, const nm16s* src2, const nm16s* src3, nm16s* dst, int sizeSrc);
	//void nmppsMerge4_32s(const nm32s* src0, const nm32s* src1,const nm32s* src2, const nm32s* src3, nm32s* dst, int sizeSrc);
	 //! \}



	/**
		\defgroup nmppSplit_32fcr nmppSplit_32fcr
		\ingroup vTransform

	 *  \brief Расщепляет массив на два, группируя по четным и нечетным элементам
	 *
	 *  \param [in]  pSrcVec  Входной массив
	 *  \param [out] pDstVec1 Выходной массив размера size/2
	 *  \param [out] pDstVec2 Выходной массив размера size/2
	 *  \param [in]  sizeSrc Размер исходного массива в элементах (должен быть четным)
	 *  \return
	 *
	 *  \details Details
	 *  Максимальная производительность достигается при размещении входных, выходных массивов в разных банках памяти. Массивы dst1 и dst2 могут находится в одном банке.
	 *  Макс  производительность  на 64-р. слово результата = 1 такт
	 */
	 //! \{
	void nmppsSplit_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec1, nm32fcr* pDstVec, int sizeSrc);
	 //! \}
	/**
		\defgroup nmppsDecimate nmppsDecimate
		\ingroup vTransform

	 *  \brief Производит выборку элементов из массива c некоторым шагом
	 *
	 *  \param [in]  pSrc  Входной массив
	 *  \param [in]  startPos Положение начального элемента в первом 64-р. слове исходного массива с которого начнется выборка
	 *  \param [out] step Шаг выборки. Должен быть кратен плотности элементов.
	 *  \param [out] pDst Выходной массив
	 *  \param [in]  nSizeDst Размер результирующего массива в элементах. Должен быть кратен плотности элементов.
	 *  \return
	 *
	 *  \details Details
	 *  Максимальная производительность достигается при размещении входных, выходных массивов в разных банках памяти.
	 */
	 //! \{
	void nmppsDecimate_16s(nm16s* pSrc, int startPos, int step, nm16s* pDst, int nSizeDst);
	void nmppsDecimate_32s(nm32s* pSrc, int startPos, int step, nm32s* pDst, int nSizeDst);
	 //! \}

#ifdef __cplusplus
		};
#endif

#endif //_VTRANSFORM_H_INCLUDED_
