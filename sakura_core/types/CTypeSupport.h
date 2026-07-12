/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "util/design_template.h"
#include "uiparts/CGraphics.h"
#include "doc/CDocTypeSetting.h"

enum EColorIndexType : int;
class CEditView;
class CViewFont;
struct STypeConfig;

//2007.08.28 kobake 追加
/*!タイプサポートクラス
	今のところタイプ別設定の色情報取得の補助
*/
class CTypeSupport final {
	static constexpr COLORREF INVALID_COLOR=0xFFFFFFFF; //無効な色定数

public:
	CTypeSupport(const CEditView* pEditView, EColorIndexType eColorIdx);
	~CTypeSupport();

	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
	//                           取得                              //
	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
	//!前景色(文字色)
	COLORREF GetTextColor() const
	{
		return m_pColorInfoArr->m_sColorAttr.m_cTEXT;
	}

	//!背景色
	COLORREF GetBackColor() const
	{
		return m_pColorInfoArr->m_sColorAttr.m_cBACK;
	}

	//!表示するかどうか
	bool IsDisp() const
	{
		return m_pColorInfoArr->m_bDisp;
	}

	//!太字かどうか
	bool IsBoldFont() const
	{
		return m_pColorInfoArr->m_sFontAttr.m_bBoldFont;
	}

	//!下線を持つかどうか
	bool HasUnderLine() const
	{
		return m_pColorInfoArr->m_sFontAttr.m_bUnderLine;
	}

	const ColorInfo& GetColorInfo() const
	{
		return *m_pColorInfoArr;
	}

	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
	//                           描画                              //
	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
	void FillBack(CGraphics& gr,const RECT& rc);

	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
	//                           設定                              //
	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
	SFONT GetTypeFont();
	void SetGraphicsState_WhileThisObj(CGraphics& gr);
	void RewindGraphicsState(CGraphics& gr);

private:
	const CViewFont*		m_pFontset = nullptr;
	const STypeConfig*		m_pTypes = nullptr;
	int						m_nColorIdx = 0;
	const ColorInfo*		m_pColorInfoArr = nullptr;

	CGraphics* 				m_gr = nullptr;        //設定を変更したHDC

	DISALLOW_COPY_AND_ASSIGN(CTypeSupport);
};
