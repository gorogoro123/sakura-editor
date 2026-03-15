/*!	@file
	@brief ファイルプロパティダイアログ

	@author Norio Nakatani
	@date 1999/02/31 新規作成
	@date 1999/12/05 再作成
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

class CDlgProperty;

#include "dlg/CDialog.h"
/*-----------------------------------------------------------------------
クラスの宣言
-----------------------------------------------------------------------*/
class CDlgProperty final : public CDialog
{
public:
	int DoModal(HINSTANCE hInstance, HWND hwndParent, LPARAM lParam);	/* モーダルダイアログの表示 */
protected:
	/*
	||  実装ヘルパ関数
	*/
	BOOL OnBnClicked(int wID) override;
	void SetData( ) override;	/* ダイアログデータの設定 */
	LPVOID GetHelpIdTable() override;	//@@@ 2002.01.18 add
};
