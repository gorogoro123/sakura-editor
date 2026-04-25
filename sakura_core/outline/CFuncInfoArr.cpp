/*!	@file
	@brief アウトライン解析 データ配列

	@author Norio Nakatani
	@date	1998/06/23 作成
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani
	Copyright (C) 2002, YAZAKI, aroka
	Copyright (C) 2018-2022, Sakura Editor Organization

	This source code is designed for sakura editor.
	Please contact the copyright holder to use this code for other purpose.
*/

#include "outline/CFuncInfoArr.h"
#include "outline/CFuncInfo.h"

/* CFuncInfoArrクラス構築 */
CFuncInfoArr::CFuncInfoArr()
{
	return;
}

/* CFuncInfoArrクラス消滅 */
CFuncInfoArr::~CFuncInfoArr()
{
	Empty();
	return;
}

void CFuncInfoArr::Empty( )
{
	for(auto& pcFuncInfo : m_pcFuncInfoArr) {
		delete pcFuncInfo;
		pcFuncInfo = nullptr;
	}
	m_pcFuncInfoArr.clear();
	m_AppendTextArr.clear();
	return;
}

/* 0<=の指定番号のデータを返す */
/* データがない場合はNULLを返す */
CFuncInfo* CFuncInfoArr::GetAt(size_t nIdx) noexcept
{
	if (m_pcFuncInfoArr.size() <= nIdx) {
		return nullptr;
	}
	return m_pcFuncInfoArr[nIdx];
}

/*! 配列の最後にデータを追加する

	@date 2002.04.01 YAZAKI 深さ導入
*/
void CFuncInfoArr::AppendData(
	CLogicInt		nFuncLineCRLF,		//!< 関数のある行(CRLF単位)
	CLogicInt		nFuncColCRLF,		//!< 関数のある桁(CRLF単位)
	CLayoutInt		nFuncLineLAYOUT,	//!< 関数のある行(折り返し単位)
	CLayoutInt		nFuncColLAYOUT,		//!< 関数のある桁(折り返し単位)
	const WCHAR*	pszFuncName,		//!< 関数名
	const WCHAR*	pszFileName,		//!< ファイル名
	int				nInfo,				//!< 付加情報
	int				nDepth				//!< 深さ
)
{
	CFuncInfo* pcFuncInfo = new CFuncInfo( nFuncLineCRLF, nFuncColCRLF, nFuncLineLAYOUT, nFuncColLAYOUT,
		pszFuncName, pszFileName, nInfo );
	pcFuncInfo->m_nDepth = nDepth;
	m_pcFuncInfoArr.emplace_back(pcFuncInfo);
	return;
}

void CFuncInfoArr::AppendData(
	CLogicInt		nFuncLineCRLF,		//!< 関数のある行(CRLF単位)
	CLayoutInt		nFuncLineLAYOUT,	//!< 関数のある行(折り返し単位)
	const WCHAR*	pszFuncName,		//!< 関数名
	int				nInfo,				//!< 付加情報
	int				nDepth				//!< 深さ
)
{
	AppendData(nFuncLineCRLF,CLogicInt(1),nFuncLineLAYOUT,CLayoutInt(1),pszFuncName,nullptr,nInfo,nDepth);
	return;
}

void CFuncInfoArr::DUMP( )
{
#ifdef _DEBUG
	MYTRACE( L"=============================\n" );
	for(int i = 0; const auto& pcFuncInfo : m_pcFuncInfoArr){
		MYTRACE( L"[%d]------------------\n", i );
		MYTRACE( L"m_nFuncLineCRLF	=%d\n", pcFuncInfo->m_nFuncLineCRLF );
		MYTRACE( L"m_nFuncLineLAYOUT	=%d\n", pcFuncInfo->m_nFuncLineLAYOUT );
		MYTRACE( L"m_cmemFuncName	=[%s]\n", pcFuncInfo->m_cmemFuncName.GetStringPtr() );
		MYTRACE( L"m_cmemFileName	=[%s]\n",
			(pcFuncInfo->m_cmemFileName.GetStringPtr() ? pcFuncInfo->m_cmemFileName.GetStringPtr() : L"NULL") );
		MYTRACE( L"m_nInfo			=%d\n", pcFuncInfo->m_nInfo );
		i++;
	}
	MYTRACE( L"=============================\n" );
#endif
}

void CFuncInfoArr::SetAppendText( int info, std::wstring s, bool overwrite )
{
	if( m_AppendTextArr.find( info ) == m_AppendTextArr.end() ){
		// キーが存在しない場合、追加する
		std::pair<int, std::wstring> pair(info, s);
		m_AppendTextArr.insert( pair );
	}else{
		// キーが存在する場合、値を書き換える
		if( overwrite ){
			m_AppendTextArr[ info ] = std::move(s);
		}
	}
}

std::wstring CFuncInfoArr::GetAppendText( int info )
{
	// キーが存在する場合、値を返す
	if( m_AppendTextArr.find( info ) != m_AppendTextArr.end() ){
		return m_AppendTextArr[info];
	}
	// キーが存在しない場合、空文字列を返す
	return {};
}
