/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <string>

class CEditDoc;
class CEditWnd;

struct CPrintParam {
	std::wstring m_szCurPageNum;	/* 現在のページ */
	std::wstring m_szAllPageNum;	/* 全ページ数 */
};

class CSakuraEnvironment{
public:
	static CEditWnd* GetMainWindow();
	static void ExpandParameter(CEditDoc* pcDoc, const wchar_t* pszSource, std::span<wchar_t> szBuffer, const CPrintParam* pcPrintParam = nullptr);
	static std::wstring GetDlgInitialDir(CEditDoc* pcDoc, bool bControlProcess = false);

	static void ResolvePath(WCHAR* pszPath); //!< ショートカットの解決とロングファイル名へ変換を行う。
private:
	static const wchar_t* _ExParam_SkipCond(const wchar_t* pszSource, int part); // Mar. 31, 2003 genta ExpandParameter補助関数
	static int _ExParam_Evaluate(CEditDoc* pcDoc, const wchar_t* pCond );
};

//ウィンドウ管理
/* 指定ウィンドウが、編集ウィンドウのフレームウィンドウかどうか調べる */
BOOL IsSakuraMainWindow( HWND hWnd );
