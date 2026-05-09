/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "util/design_template.h"
#include "doc/CDocTypeSetting.h" // ColorInfo !!

class CViewFont{
public:
	CViewFont(const LOGFONT *plf, bool bMiniMap = false)
	{
		m_bMiniMap = bMiniMap;
		CreateFonts(plf);
	}
	virtual ~CViewFont()
	{
		DeleteFonts();
	}

	void UpdateFont(const LOGFONT *plf)
	{
		DeleteFonts();
		CreateFonts(plf);
	}

	HFONT ChooseFontHandle( int fontNo, SFontAttr sFontAttr ) const;		/* フォントを選ぶ */

	HFONT GetFontHan() const
	{
		return m_hFont_HAN;
	}

	const LOGFONT& GetLogfont([[maybe_unused]] int FontNo = 0) const
	{
		return m_LogFont;
	}

private:
	void CreateFonts( const LOGFONT *plf );
	void DeleteFonts( );

	HFONT	m_hFont_HAN;			/* 現在のフォントハンドル */
	HFONT	m_hFont_HAN_BOLD;		/* 現在のフォントハンドル(太字) */
	HFONT	m_hFont_HAN_UL;			/* 現在のフォントハンドル(下線) */
	HFONT	m_hFont_HAN_BOLD_UL;	/* 現在のフォントハンドル(太字、下線) */

	LOGFONT	m_LogFont;
	bool	m_bMiniMap;

	DISALLOW_COPY_AND_ASSIGN(CViewFont);
};

CViewFont* GetViewFont(bool isMiniMap);
