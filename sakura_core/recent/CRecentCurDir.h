/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2013, Moca
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CRecentImp.h"
#include "util/StaticType.h"

using CCurDirString = StaticString<_MAX_PATH>;

//! コマンドの履歴を管理 (RECENT_FOR_CUR_DIR)
class CRecentCurDir final : public CRecentImp<CCurDirString, LPCWSTR>{
public:
	//生成
	CRecentCurDir();

	//オーバーライド
	int				CompareItem( const CCurDirString* p1, LPCWSTR p2 ) const override;
	void			CopyItem( CCurDirString* dst, LPCWSTR src ) const override;
	const WCHAR*	GetItemText( int nIndex ) const override;
	bool			DataToReceiveType( LPCWSTR* dst, const CCurDirString* src ) const override;
	bool			TextToDataType( CCurDirString* dst, LPCWSTR pszText ) const override;
	bool			ValidateReceiveType( LPCWSTR p ) const override;
	size_t			GetTextMaxLength() const override;
};
