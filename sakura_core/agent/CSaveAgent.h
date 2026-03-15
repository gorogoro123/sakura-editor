/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "doc/CDocListener.h"

class CSaveAgent : public CDocListenerEx{
public:
	CSaveAgent();
	ECallbackResult OnCheckSave(SSaveInfo* pSaveInfo) override;
	void OnBeforeSave(const SSaveInfo& sSaveInfo) override;
	void OnSave(const SSaveInfo& sSaveInfo) override;
	void OnAfterSave(const SSaveInfo& sSaveInfo) override;
	void OnFinalSave(ESaveResult eSaveResult) override;
private:
	SSaveInfo	m_sSaveInfoForRollback;
};
