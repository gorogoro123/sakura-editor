/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "doc/CDocListener.h"

class CEditDoc;

class CDocLocker : public CDocListener{
public:
	CDocLocker(CEditDoc& m_cEditDoc);

	//クリア
	void Clear() { m_bIsDocWritable = true; }

	//ロード前後
	void OnAfterLoad(const SLoadInfo& sLoadInfo) override;
	
	//セーブ前後
	void OnBeforeSave(const SSaveInfo& sSaveInfo) override;
	void OnAfterSave(const SSaveInfo& sSaveInfo) override;

	//状態
	bool IsDocWritable() const{ return m_bIsDocWritable; }

	//チェック
	void CheckWritable(bool bMsg);

private:
	CEditDoc& m_cEditDoc;
	bool m_bIsDocWritable = true;
};
