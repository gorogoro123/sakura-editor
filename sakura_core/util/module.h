/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

void GetAppVersionInfo( DWORD* pdwProductVersionMS, DWORD* pdwProductVersionLS );	/* リソースから製品バージョンの取得 */

HICON GetAppIcon( HINSTANCE hInst, int nResource, const WCHAR* szFile, bool bSmall = false);

DWORD GetDllVersion( LPCWSTR lpszDllName );	// シェルやコモンコントロール DLL のバージョン番号を取得	// 2006.06.17 ryoji

void ChangeCurrentDirectoryToExeDir();

//! カレントディレクトリ移動機能付LoadLibrary
HMODULE LoadLibraryExedir( LPCWSTR pszDll);
