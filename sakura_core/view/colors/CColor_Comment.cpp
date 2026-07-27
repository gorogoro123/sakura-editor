/*! @file */
/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#include "view/CEditView.h" // SColorStrategyInfo
#include "CColor_Comment.h"
#include "doc/layout/CLayout.h"

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                        行コメント                           //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //

bool CColor_LineComment::BeginColor(std::span<const WCHAR> cStr, int nPos)
{
	if(cStr.size() == 0) return false;

	// 行コメント
	if( m_pTypeData->m_cLineComment.Match( nPos, cStr )	//@@@ 2002.09.22 YAZAKI
	){
		return true;
	}
	return false;
}

bool CColor_LineComment::EndColor(std::span<const WCHAR> cStr, int nPos)
{
	//文字列終端
	if( nPos >= cStr.size() ){
		return true;
	}

	//改行
	if( WCODE::IsLineDelimiter(cStr[nPos], GetDllShareData().m_Common.m_sEdit.m_bEnableExtEol) ){
		return true;
	}

	return false;
}

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                    ブロックコメント１                       //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //

bool CColor_BlockComment::BeginColor(std::span<const WCHAR> cStr, int nPos)
{
	if(cStr.size() == 0) return false;

	// ブロックコメント
	if( m_pcBlockComment->Match_CommentFrom( nPos, cStr )	//@@@ 2002.09.22 YAZAKI
	){
		/* この物理行にブロックコメントの終端があるか */	//@@@ 2002.09.22 YAZAKI
		m_nCOMMENTEND = m_pcBlockComment->Match_CommentTo(
			nPos + m_pcBlockComment->getBlockFromLen(),
			cStr
		);

		return true;
	}
	return false;
}

bool CColor_BlockComment::EndColor(std::span<const WCHAR> cStr, int nPos)
{
	if( 0 == m_nCOMMENTEND ){
		/* この物理行にブロックコメントの終端があるか */
		m_nCOMMENTEND = m_pcBlockComment->Match_CommentTo(
			nPos,
			cStr
		);
	}
	else if( nPos == m_nCOMMENTEND ){
		return true;
	}
	return false;
}
