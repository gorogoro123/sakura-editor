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
	const wchar_t* GetFirstLinrStr( CLogicInt* pnLineLen );	/* 順アクセスモード：先頭行を得る */
	const wchar_t* GetNextLinrStr( CLogicInt* pnLineLen );	/* 順アクセスモード：次の行を得る */

private:
	const CDocLineMgr* m_pcDocLineMgr;
};
