/*!	@file
	@brief 指差しカーソル

	@author Uchi
	@date 2013年1月29日
*/
/*
	Copyright (C) 2013, Uchi
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

inline void SetHandCursor ()
{
	SetCursor( LoadCursor( nullptr, IDC_HAND ) );
}
