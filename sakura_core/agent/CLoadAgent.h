/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "doc/CDocListener.h"

class CLoadAgent : public CDocListenerEx{
public:
	ECallbackResult OnCheckLoad(SLoadInfo* pLoadInfo) override;
	void OnBeforeLoad(SLoadInfo* sLoadInfo) override;
	ELoadResult OnLoad(const SLoadInfo& sLoadInfo) override;
	void OnAfterLoad(const SLoadInfo& sLoadInfo) override;
	void OnFinalLoad(ELoadResult eLoadResult) override;
};
