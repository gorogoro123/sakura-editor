/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "view/colors/CColorStrategy.h"

class CColor_KeywordSet final : public CColorStrategy{
public:
	CColor_KeywordSet();
	EColorIndexType GetStrategyColor() const override{ return (EColorIndexType)(COLORIDX_KEYWORD1 + m_nKeywordIndex); }
	void InitStrategyStatus() override{ m_nCOMMENTEND = 0; }
	bool BeginColor(const CStringRef& cStr, int nPos) override;
	bool EndColor(const CStringRef& cStr, int nPos) override;
	bool Disp() const override{ return true; }
private:
	int m_nKeywordIndex;
	int m_nCOMMENTEND;
};
