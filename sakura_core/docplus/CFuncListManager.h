/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2014, Moca
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "basis/SakuraBasis.h"
#include "_main/global.h"

class CDocLine;
class CDocLineMgr;

//! 行に付加するModified情報
class CLineFuncList{
public:
	CLineFuncList() : m_bFuncList(false) { }
	bool GetFuncListMark() const { return m_bFuncList; }
	CLineFuncList& operator = (bool bSet)
	{
		m_bFuncList = bSet;
		return *this;
	}
private:
	bool m_bFuncList;
};

//! 行全体のFuncList情報アクセサ
class CFuncListManager{
public:
	//状態
	bool IsLineFuncList(const CDocLine* pcDocLine, bool bFlag) const;
	bool GetLineFuncList(const CDocLine* pcDocLine) const;
	void SetLineFuncList(CDocLine* pcDocLine, bool bFlag);
	bool SearchFuncListMark(const CDocLineMgr* pcDocLineMgr, CLogicInt nLineNum,
							ESearchDirection bPrevOrNext, CLogicInt* pnLineNum) const;	//!< 関数リストマーク検索

	//一括操作
	void ResetAllFucListMark(CDocLineMgr* pcDocLineMgr, bool bFlag);	// 関数リストマークをすべてリセット
};
