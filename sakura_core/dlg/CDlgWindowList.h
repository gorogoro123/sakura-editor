/*!	@file
	@brief ファイル一覧ダイアログボックス

	@author Moca
	@date 2015.03.07
*/
/*
	Copyright (C) 2015, Moca
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "dlg/CDialog.h"
class CDlgWindowList final : public CDialog
{
public:
	CDlgWindowList();

	int DoModal(HINSTANCE hInstance, HWND hwndParent, LPARAM lParam);
protected:
	BOOL	OnBnClicked(int wID) override;
	LPVOID	GetHelpIdTable() override;
	BOOL OnInitDialog(HWND hwndDlg, WPARAM wParam, LPARAM lParam) override;
	BOOL OnDestroy( ) override;
	BOOL OnSize(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMinMaxInfo( WPARAM wParam, LPARAM lParam ) override;
	BOOL OnActivate(WPARAM wParam, LPARAM lParam) override;

	void SetData() override;
	int  GetData() override;

	void GetDataListView(std::vector<HWND>& aHwndList);
	void CommandClose();
	void CommandSave();
private:
	POINT		m_ptDefaultSize;
	RECT		m_rcItems[5];
};
