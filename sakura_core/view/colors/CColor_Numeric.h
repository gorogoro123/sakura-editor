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
	bool BeginColor(const CStringRef& cStr, int nPos) override;
	bool EndColor(const CStringRef& cStr, int nPos) override;
	bool Disp() const override{ return m_pTypeData->m_ColorInfoArr[COLORIDX_DIGIT].m_bDisp; }
private:
	int m_nCOMMENTEND;
};
