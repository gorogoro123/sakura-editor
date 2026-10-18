/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "doc/CDocListener.h"
#include "util/design_template.h"

class CEditWnd;

class CCodeChecker final : public CDocListener{
public:
	CCodeChecker(CEditDoc& cEditDoc, CEditWnd& cEditWnd)
	:m_cEditDoc(cEditDoc),
	m_cEditWnd(cEditWnd)
	{}

public:
	//セーブ時チェック
	ECallbackResult OnCheckSave(SSaveInfo* pSaveInfo) override;
	void OnFinalSave(ESaveResult eSaveResult) override;

	//ロード時チェック
	void OnFinalLoad(ELoadResult eLoadResult) override;
private:
	CEditDoc& m_cEditDoc;
	CEditWnd& m_cEditWnd;
};
