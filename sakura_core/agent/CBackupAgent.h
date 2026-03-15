/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "doc/CDocListener.h"

class CBackupAgent : public CDocListenerEx{
public:
	ECallbackResult OnPreBeforeSave(SSaveInfo* pSaveInfo) override;

protected:
	int MakeBackUp( const WCHAR* target_file );								//!< バックアップの作成
	bool FormatBackUpPath( WCHAR*, size_t, const WCHAR* );	//!< バックアップパスの作成 2005.11.21 aroka
};
