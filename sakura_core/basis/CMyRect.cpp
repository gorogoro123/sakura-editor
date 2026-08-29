/*! @file */
/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#include "CMyRect.h"
#include "util/std_macro.h"

CMyRect MergeRect(const CMyRect& rc1, const CMyRect& rc2)
{
	return CMyRect(
		(std::min)(rc1.left  , rc2.left),
		(std::min)(rc1.top   , rc2.top),
		(std::max)(rc1.right , rc2.right),
		(std::max)(rc1.bottom, rc2.bottom)
	);
}
