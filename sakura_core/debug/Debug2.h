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

#ifdef _DEBUG

	void warning_point();

	#define assert_warning(exp) \
		if(!(exp)){ \
			TRACE( "!warning: " #exp, nullptr ); \
			warning_point(); \
		} \
		((void)0)

#else
	#define assert_warning(exp)	((void)0)
#endif
