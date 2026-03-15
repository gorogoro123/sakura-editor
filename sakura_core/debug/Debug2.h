/*!	@file
	@brief assert関数

*/
/*
	Copyright (C) 2007, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <cassert>

#include "debug/Debug1.h"
#include "util/MessageBoxF.h"

// C Runtime の定義をundefして独自定義に差し替える
#undef assert

#ifdef _DEBUG

	void debug_exit();
	void warning_point();

	#define assert(exp) \
		if(!(exp)){ \
			TRACE( "!assert: " #exp, nullptr ); \
			ErrorMessage( nullptr, L"!assert\n%hs(%d):\n%hs", __FILE__, __LINE__, #exp ); \
			debug_exit(); \
		} \
		((void)0)

	#define assert_warning(exp) \
		if(!(exp)){ \
			TRACE( "!warning: " #exp, nullptr ); \
			warning_point(); \
		} \
		((void)0)

#else
	#define assert(exp)			((void)0)
	#define assert_warning(exp)	((void)0)
#endif
