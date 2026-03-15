/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "view/colors/CColorStrategy.h"

class CColor_RegexKeyword final : public CColorStrategy{
public:
	CColor_RegexKeyword() : m_nCOMMENTEND(0), m_nCOMMENTMODE(ToColorIndexType_RegularExpression(0)) { }
	EColorIndexType GetStrategyColor() const override{ return m_nCOMMENTMODE; }
	void InitStrategyStatus() override{ m_nCOMMENTEND = 0; m_nCOMMENTMODE = ToColorIndexType_RegularExpression(0); }
	bool BeginColor(const CStringRef& cStr, int nPos) override;
	bool EndColor(const CStringRef& cStr, int nPos) override;
	bool Disp() const override{ return m_pTypeData->m_bUseRegexKeyword; }
	void OnStartScanLogic() override;
private:
	int m_nCOMMENTEND;
	EColorIndexType m_nCOMMENTMODE;
};
