//------------------------------------------------------------------------
//
//  $Workfile:: pcConvert.cp $
//
//  Neuro Matrix Performance Primitives
//
//  Copyright (c) RC Module
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   pcConvert.cpp
//! \author S.Mushkaev
//! \brief  Функции для преобразования запакованных данных.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpp.h"


void nmppsMerge_8s(const nm8s* src0, const nm8s* src1, nm8s* dst, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc;i++){
		dst[2*i]  =src0[i];
		dst[2*i+1]=src1[i];
	}
}
void nmppsMerge_16s(const nm16s* src0, const nm16s* src1, nm16s* dst, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc;i++){
		dst[2*i]  =src0[i];
		dst[2*i+1]=src1[i];
	}
}

void nmppsMerge_32s(const nm32s* src0, const nm32s* src1, nm32s* dst, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc;i++){
		dst[2*i]  =src0[i];
		dst[2*i+1]=src1[i];
	}
}


void nmppsMerge4_8s(const nm8s* src0, const nm8s* src1,const nm8s* src2, const nm8s* src3, nm8s* dst, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc;i++){
		dst[4*i]  =src0[i];
		dst[4*i+1]=src1[i];
		dst[4*i+2]=src2[i];
		dst[4*i+3]=src3[i];
	}
}
void nmppsMerge4_16s(const nm16s* src0, const nm16s* src1,const nm16s* src2, const nm16s* src3, nm16s* dst, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc;i++){
		dst[4*i]  =src0[i];
		dst[4*i+1]=src1[i];
		dst[4*i+2]=src2[i];
		dst[4*i+3]=src3[i];
	}
}



