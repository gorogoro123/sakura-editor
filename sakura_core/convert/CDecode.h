/*!	@file
	@brief デコーダーのインターフェース

	@author
*/
/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CSelectLang.h"
#include "mem/CNativeW.h"

class CDecode {
public:
	virtual ~CDecode() { }

	//インターフェース
	bool CallDecode( const CNativeW& pcData, CMemory* pDest )
	{
		bool bRet=DoDecode(pcData, pDest);
		if(!bRet){
			ErrorMessage(nullptr,LS(STR_CONVERT_ERR));
			pDest->SetRawData( "", 0 );
			return false;
		}
		return true;
	}

	//実装
	virtual bool DoDecode( const CNativeW& pcData, CMemory* pDest )=0;
};
