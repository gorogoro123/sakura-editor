/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "doc/CDocListener.h"

class CEditDoc;
class CEditWnd;

class CLoadAgent : public CDocListener{
public:
	explicit CLoadAgent(CEditDoc& cEditDoc, CEditWnd& cEditWnd)
	:m_cEditDoc(cEditDoc),
	m_cEditWnd(cEditWnd)
	{
	}
	ECallbackResult OnCheckLoad(SLoadInfo* pLoadInfo) override;
	void OnBeforeLoad(SLoadInfo* sLoadInfo) override;
	ELoadResult OnLoad(const SLoadInfo& sLoadInfo) override;
	void OnAfterLoad(const SLoadInfo& sLoadInfo) override;
	void OnFinalLoad(ELoadResult eLoadResult) override;

private:
	CEditDoc& m_cEditDoc;
	CEditWnd& m_cEditWnd;
};
