/*! @file

	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CRecentImp.h"
#include "util/StaticType.h"
#include "config/maxdata.h"

using CExcludeFolderString= StaticString<MAX_EXCLUDE_PATH>;

//! Excludeフォルダーの履歴を管理 (RECENT_FOR_Exclude_FOLDER)
class CRecentExcludeFolder final : public CRecentImp<CExcludeFolderString, LPCWSTR>{
public:
	//生成
	CRecentExcludeFolder();

	//オーバーライド
	int				CompareItem( const CExcludeFolderString* p1, LPCWSTR p2 ) const override;
	void			CopyItem( CExcludeFolderString* dst, LPCWSTR src ) const override;
	const WCHAR*	GetItemText( int nIndex ) const override;
	bool			DataToReceiveType( LPCWSTR* dst, const CExcludeFolderString* src ) const override;
	bool			TextToDataType( CExcludeFolderString* dst, LPCWSTR pszText ) const override;
	bool			ValidateReceiveType( LPCWSTR p ) const override;
	size_t			GetTextMaxLength() const override;
};
