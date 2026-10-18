/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "doc/CDocListener.h" // CProgressSubject
#include "charset/CCodeBase.h" // EConvertResult
#include "io/CFileLoad.h"
#include <atomic>

class CDocLineMgr;
struct SFileInfo; // doc/CDocFile.h
class CEditWnd;

class CReadManager : public CProgressSubject{
public:
	CReadManager(CEditWnd& cEditWnd)
	:m_cEditWnd(cEditWnd)
	{}
	//	Jul. 26, 2003 ryoji BOM引数追加
	EConvertResult ReadFile_To_CDocLineMgr(
		CDocLineMgr*		pcDocLineMgr,
		const SLoadInfo&	sLoadInfo,
		SFileInfo*			pFileInfo
	);

private:
	CEditWnd& m_cEditWnd;
	EConvertResult ReadLines(
		bool				bRunInMainThread,
		CFileLoad&			cFileLoad,
		CDocLineMgr&		cDocLineMgr,
		std::atomic<bool>&	bCanceled
	);
};
