/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "view/colors/CColorStrategy.h"

class CColor_Numeric final : public CColorStrategy{
public:
	CColor_Numeric() : m_nCOMMENTEND(0) { }
	EColorIndexType GetStrategyColor() const override{ return COLORIDX_DIGIT; }
	void InitStrategyStatus() override{ m_nCOMMENTEND = 0; }
	bool BeginColor(std::span<const WCHAR> cStr, int nPos) override;
	bool EndColor(std::span<const WCHAR> cStr, int nPos) override;
	bool Disp() const override{ return m_pTypeData->m_ColorInfoArr[COLORIDX_DIGIT].m_bDisp; }

	static int IsNumber( std::span<const WCHAR> cStr, int offset );/* 数値ならその長さを返す */	//@@@ 2001.02.17 by MIK
private:
	int m_nCOMMENTEND;
};
