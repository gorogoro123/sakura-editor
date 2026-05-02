/*!	@file
	@brief タグファイル作成ダイアログボックス

	@author MIK
	@date 2003.5.12
*/
/*
	Copyright (C) 2003, MIK
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "dlg/CDialog.h"
#include "basis/CMyString.h"

/*!
	@brief タグファイル作成ダイアログボックス
*/
class CDlgTagsMake final : public CDialog
{
public:
	/*
	||  Constructors
	*/
	CDlgTagsMake() = default;

	/*
	||  Attributes & Operations
	*/
	int DoModal( HINSTANCE hInstance, HWND hwndParent, LPARAM lParam, const WCHAR* pszPath );	/* モーダルダイアログの表示 */

	SFilePath	m_szPath;	/* フォルダー */
	StaticString<_MAX_PATH> 	m_szTagsCmdLine;	/* コマンドラインオプション(個別) */
	int		m_nTagsOpt = 0;				/* CTAGSオプション(チェック) */

protected:
	/*
	||  実装ヘルパ関数
	*/
	BOOL	OnBnClicked(int wID) override;
	LPVOID	GetHelpIdTable() override;

	void	SetData( ) override;	/* ダイアログデータの設定 */
	int		GetData( ) override;	/* ダイアログデータの取得 */

private:
	void SelectFolder( HWND hwndDlg );
};
