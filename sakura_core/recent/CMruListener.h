/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "doc/CDocListener.h"

class CMruListener : public CDocListenerEx{
public:
	//ロード前後
//	ECallbackResult OnCheckLoad(SLoadInfo* pLoadInfo) override;
	void OnBeforeLoad(SLoadInfo* sLoadInfo) override;
	void OnAfterLoad(const SLoadInfo& sLoadInfo) override;

	//セーブ前後
	void OnAfterSave(const SSaveInfo& sSaveInfo) override;

	//クローズ前後
	ECallbackResult OnBeforeClose() override;

protected:
	//ヘルパ
	void _HoldBookmarks_And_AddToMRU(); // Mar. 30, 2003 genta
};
