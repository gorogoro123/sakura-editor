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

class CReadManager : public CProgressSubject{
public:
	//	Nov. 12, 2000 genta 引数追加
	//	Jul. 26, 2003 ryoji BOM引数追加
	EConvertResult ReadFile_To_CDocLineMgr(
		CDocLineMgr*		pcDocLineMgr,
		const SLoadInfo&	sLoadInfo,
		SFileInfo*			pFileInfo
	);

private:
	EConvertResult ReadLines(
		bool				bRunInMainThread,
		CFileLoad&			cFileLoad,
		CDocLineMgr&		cDocLineMgr,
		std::atomic<bool>&	bCanceled
	);
};
