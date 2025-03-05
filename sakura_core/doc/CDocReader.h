/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "basis/SakuraBasis.h"

class CDocLineMgr;

//as decorator
class CDocReader{
public:
	CDocReader(const CDocLineMgr& pcDocLineMgr) : m_pcDocLineMgr(&pcDocLineMgr) { }

	wchar_t* GetAllData(int* pnDataLen);	/* 全行データを返す */
	const wchar_t* GetLineStr( CLogicInt nLine, CLogicInt* pnLineLen );
	const wchar_t* GetLineStrWithoutEOL( CLogicInt nLine, int* pnLineLen ); // 2003.06.22 Moca

private:
	const CDocLineMgr* m_pcDocLineMgr;
};
