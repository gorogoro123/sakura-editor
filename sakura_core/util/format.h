/*! @file */
// 2007.10.20 kobake 書式関連
/*
	Copyright (C) 2007, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <string>
#include <string_view>

// 20051121 aroka
std::wstring GetDateTimeFormat( std::wstring_view format, const SYSTEMTIME& systime );
UINT32 ParseVersion( const WCHAR* ver );	//バージョン番号の解析
int CompareVersion( const WCHAR* verA, const WCHAR* verB );	//バージョン番号の比較
