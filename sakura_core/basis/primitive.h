/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <Windows.h>
#include "config/build_config.h"

// -- -- -- -- 文字 -- -- -- -- //

//char,wchar_t の変わりに、別名の ACHAR,WCHAR を使うと、ソース整形がしやすいケースがある。
using ACHAR = char;

//文字コード別、文字型
using uchar_t = unsigned char;		//  unsigned char の別名．
using uchar16_t = unsigned short;	//  UTF-16 用．
using uchar32_t = unsigned long;	//  UTF-32 用．
using wchar32_t = long;

// -- -- -- -- その他 -- -- -- -- //

using KEYCODE = char;

//int互換
#ifdef USE_STRICT_INT
	#include "CLaxInteger.h"
	using Int = CLaxInteger;
#else
	using Int = int;
#endif
