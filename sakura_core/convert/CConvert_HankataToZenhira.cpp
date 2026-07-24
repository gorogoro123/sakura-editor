/*! @file */
/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#include "CConvert_HankataToZenhira.h"
#include "convert_util.h"
#include "mem/CNativeW.h"

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                     インターフェース                        //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //

//!半角カナ→全角ひらがな
bool CConvert_HankataToZenhira::DoConvert(CNativeW* pcData)
{
	//半角カナ→全角ひらがな
	std::vector<wchar_t> vBuf(static_cast<size_t>(pcData->GetStringLength()) + 1); //文字数が減ることはあっても増えることは無いので、これでＯＫ
	int nDstLen = 0;
	Convert_HankataToZenhira(pcData->GetStringPtr(), pcData->GetStringLength(), vBuf.data(), &nDstLen);
	pcData->SetString(vBuf.data(), nDstLen);

	return true;
}
