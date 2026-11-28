/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/

#include "view/CEditView.h" // SColorStrategyInfo
#include "CColor_RegexKeyword.h"

bool CColor_RegexKeyword::BeginColor(CEditView* pcView, std::span<const WCHAR> cStr, int nPos)
{
	if(cStr.size() == 0) return false;

	int		nMatchLen;
	int		nMatchColor;

	//正規表現キーワード
	if( pcView->m_cRegexKeyword->RegexIsKeyword( cStr, nPos, &nMatchLen, &nMatchColor )
	){
		m_nCOMMENTEND = nPos + nMatchLen;  /* キーワード文字列の終端をセットする */
		m_nCOMMENTMODE = ToColorIndexType_RegularExpression(nMatchColor);
		return true;
	}
	return false;
}

bool CColor_RegexKeyword::EndColor([[maybe_unused]] CEditView* pcView, [[maybe_unused]] std::span<const WCHAR> cStr, int nPos)
{
	if( nPos == m_nCOMMENTEND ){
		return true;
	}
	return false;
}

void CColor_RegexKeyword::OnStartScanLogic(CEditView* pcView)
{
	if( m_pTypeData->m_bUseRegexKeyword ){
		pcView->m_cRegexKeyword->RegexKeyLineStart();
	}
}
