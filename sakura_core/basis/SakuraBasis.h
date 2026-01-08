/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <Windows.h> //POINT,LONG

#include "basis/primitive.h" // for Int

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                      １次元型の定義                         //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//
#ifdef USE_STRICT_INT
	// -- -- 厳格なintで単位型を定義 -- -- //

	#include "CStrictInteger.h"

	//ロジック単位
	using CLogicInt = CStrictInteger <
		0,		//!< 型を分けるための数値。
		true,	//!< intとの比較を許すかどうか
		true,	//!< intとの加減算を許すかどうか
		true,	//!< intへの暗黙の変換を許すかどうか
		true	//!< intの代入を許すかどうか
	>;

	//レイアウト単位
	using CLayoutInt = CStrictInteger <
		1,		//!< 型を分けるための数値。
		true,	//!< intとの比較を許すかどうか
		true,	//!< intとの加減算を許すかどうか
		false,	//!< intへの暗黙の変換を許すかどうか
		true	//!< intの代入を許すかどうか
	>;

#else
	// -- -- 通常のintで単位型を定義

	//ロジック単位
	using CLogicInt = int;

	//レイアウト単位
	using CLayoutInt = int;

#endif

using CLogicXInt = CLogicInt;
using CLogicYInt = CLogicInt;
using CLayoutXInt = CLayoutInt;
using CLayoutYInt = CLayoutInt;
using CPixelYInt = int;
using CPixelXInt = int;

using CHabaXInt = CLayoutXInt;
using CKetaXInt = int;

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                      ２次元型の定義                         //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//
#include "CStrictRange.h"
#include "CStrictPoint.h"
#include "CStrictRect.h"

//ロジック単位
struct SLogicPoint{ CLogicInt x; CLogicInt y; }; //基底構造体
using CLogicPoint = CStrictPoint<SLogicPoint, CLogicInt>;
using CLogicRange = CRangeBase<CLogicPoint>	;
using CLogicRect = CStrictRect<CLogicInt, CLogicPoint>;

//レイアウト単位
struct SLayoutPoint{ CLayoutInt x; CLayoutInt y; }; //基底構造体
using CLayoutPoint = CStrictPoint<SLayoutPoint, CLayoutInt>;
using CLayoutRange = CRangeBase<CLayoutPoint>;
using CLayoutRect = CStrictRect<CLayoutInt, CLayoutPoint>;

//ゆるい単位
#include "CMyPoint.h"
using SelectionRange = CRangeBase<CMyPoint>;

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                          ツール                             //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
#include "CMyRect.h"

//変換関数
template <class POINT_T>
inline void TwoPointToRange(
	CRangeBase<POINT_T>* prangeDst,
	POINT_T pt1,
	POINT_T pt2
)
{
	CMyRect rc;
	TwoPointToRect(&rc,pt1,pt2);
	prangeDst->SetFrom(POINT_T(rc.UpperLeft()));
	prangeDst->SetTo(POINT_T(rc.LowerRight()));
}

//! 2点を対角とする矩形を求める
template <class T, class INT_TYPE>
inline void TwoPointToRect(
	CStrictRect<INT_TYPE, CStrictPoint<T,INT_TYPE> >*	prcRect,
	CStrictPoint<T,INT_TYPE>							pt1,
	CStrictPoint<T,INT_TYPE>							pt2
)
{
	if( pt1.y < pt2.y ){
		prcRect->top	= pt1.GetY2();
		prcRect->bottom	= pt2.GetY2();
	}else{
		prcRect->top	= pt2.GetY2();
		prcRect->bottom	= pt1.GetY2();
	}
	if( pt1.x < pt2.x ){
		prcRect->left	= pt1.GetX2();
		prcRect->right	= pt2.GetX2();
	}else{
		prcRect->left	= pt2.GetX2();
		prcRect->right	= pt1.GetX2();
	}
}
