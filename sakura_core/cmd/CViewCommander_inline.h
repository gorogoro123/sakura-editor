/*! @file */
/*
	Copyright (C) 2013, novice
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "view/CEditView.h"
#include "doc/CEditDoc.h"
#include "window/CEditWnd.h"
#include "cmd/COpeBlk.h"

//外部依存
inline CEditDoc* CViewCommander::GetDocument()
{
	return m_pCommanderView->m_pcEditDoc;
}
inline CEditWnd* CViewCommander::GetEditWindow()
{
	return &GetEditWnd();
}
inline HWND CViewCommander::GetMainWindow()
{
	return ::GetParent( m_pCommanderView->m_hwndParent );
}
inline COpeBlk* CViewCommander::GetOpeBlk()
{
	return GetDocument()->m_cDocEditor.m_pcOpeBlk;
}
inline void CViewCommander::SetOpeBlk(COpeBlk* p)
{
	GetDocument()->m_cDocEditor.m_pcOpeBlk = p;
	GetDocument()->m_cDocEditor.m_nOpeBlkRedawCount = 0;
}
inline CLayoutRange& CViewCommander::GetSelect()
{
	return m_pCommanderView->GetSelectionInfo().m_sSelect;
}
inline CCaret& CViewCommander::GetCaret()
{
	return m_pCommanderView->GetCaret();
}
