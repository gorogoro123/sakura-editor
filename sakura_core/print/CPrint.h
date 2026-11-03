/*!	@file
	@brief 印刷関連

	@author Norio Nakatani
	@date 1998/06/09 新規作成
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani
	Copyright (C) 2003, かろと
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <WinSpool.h>
#include <CommDlg.h> // PRINTDLG
#include "basis/primitive.h"
#include "basis/CMyString.h"
#include "util/design_template.h"
#include "PrintSetting.h"


/*-----------------------------------------------------------------------
クラスの宣言
-----------------------------------------------------------------------*/
/*!
	@brief 印刷関連機能

	オブジェクト指向でないクラス
*/
class CPrint
{
public:
	static std::span<const PAPER_INFO> GetPaperInfo(); //!< 用紙情報一覧取得

	/*
	||	static関数群
	*/
	static void SettingInitialize( PRINTSETTING&, const WCHAR* settingName );

	static void GetPaperName( int , std::wstring& );	/* 用紙の名前を取得 */
	/* 用紙の幅、高さ */
	static BOOL GetPaperSize(
		short*		pnPaperAllWidth,
		short*		pnPaperAllHeight,
		MYDEVMODE*	pDEVMODE
	);
	/* 印字可能桁・行の計算 */
	static int CalculatePrintableColumns( PRINTSETTING*, int width, int nLineNumberColumns );
	static int CalculatePrintableLines( PRINTSETTING*, int height );

	/* ヘッダー・フッターの高さ計算 */
	static int CalcHeaderHeight( PRINTSETTING* );
	static int CalcFooterHeight( PRINTSETTING* );
public:
	/*
	||  Constructors
	*/
	CPrint();
	~CPrint();

	/*
	||  Attributes & Operations
	*/
	BOOL GetDefaultPrinter( MYDEVMODE *pMYDEVMODE );		/* デフォルトのプリンター情報を取得 */
	BOOL PrintDlg( PRINTDLG *pd, MYDEVMODE *pMYDEVMODE );				/* プリンター情報を取得 */
	/* 印刷/プレビューに必要な情報を取得 */
	BOOL GetPrintMetrics(
		MYDEVMODE*	pMYDEVMODE,
		short*		pnPaperAllWidth,	/* 用紙幅 */
		short*		pnPaperAllHeight,	/* 用紙高さ */
		short*		pnPaperWidth,		/* 用紙印刷可能幅 */
		short*		pnPaperHeight,		/* 用紙印刷可能高さ */
		short*		pnPaperOffsetLeft,	/* 用紙余白左端 */
		short*		pnPaperOffsetTop,	/* 用紙余白上端 */
		std::span<WCHAR>	szErrMsg	/* エラーメッセージ格納場所 */
	);

	/* 印刷 ジョブ開始 */
	BOOL PrintOpen(
		WCHAR*		pszJobName,
		MYDEVMODE*	pMYDEVMODE,
		HDC*		phdc,
		std::span<WCHAR>	szErrMsg	/* エラーメッセージ格納場所 */
	);
	void PrintStartPage(HDC hdc);	/* 印刷 ページ開始 */
	void PrintEndPage(HDC hdc);	/* 印刷 ページ終了 */
	void PrintClose(HDC hdc);		/* 印刷 ジョブ終了 */ // 2003.05.02 かろと 不要なhPrinter削除

protected:
	/*
	||  実装ヘルパ関数
	*/
	// DC作成する(処理をまとめた) 2003.05.02 かろと
	HDC CreateDC( MYDEVMODE *pMYDEVMODE, std::span<WCHAR> szErrMsg);
	
	static const PAPER_INFO* FindPaperInfo( int id );
private:
	/*
	||  メンバ変数
	*/
	HGLOBAL	m_hDevMode = nullptr;				//!< 現在プリンターのDEVMODEへのメモリハンドル
	HGLOBAL	m_hDevNames = nullptr;				//!< 現在プリンターのDEVNAMESへのメモリハンドル

	DISALLOW_COPY_AND_ASSIGN(CPrint);
};
