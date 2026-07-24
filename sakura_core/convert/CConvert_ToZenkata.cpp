/*! @file */
/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#include "CConvert_ToZenkata.h"
#include "convert_util.h"
#include "mem/CNativeW.h"

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                     インターフェース                        //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //

//!できる限り全角カタカナにする
bool CConvert_ToZenkata::DoConvert(CNativeW* pcData)
{
	//半角カナ→全角カナ
	std::vector<wchar_t> vBuf(static_cast<size_t>(pcData->GetStringLength())+1); //文字数が減ることはあっても増えることは無いので、これでＯＫ
	int nBufLen = 0;
	Convert_HankataToZenkata(pcData->GetStringPtr(), pcData->GetStringLength(), vBuf.data(), &nBufLen);

	//全角ひら→全角カナ
	Convert_ZenhiraToZenkata(vBuf.data(), nBufLen);

	//半角英数→全角英数
	Convert_HaneisuToZeneisu(vBuf.data(), nBufLen);

	//設定
	pcData->SetString(vBuf.data(), nBufLen);

	return true;
}
