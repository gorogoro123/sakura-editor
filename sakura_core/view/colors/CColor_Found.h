/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "view/colors/CColorStrategy.h"

class CColor_Select final : public CColorStrategy{
public:
	EColorIndexType GetStrategyColor() const override{ return COLORIDX_SELECT; }
	//色替え
	void InitStrategyStatus() override{ }
	bool BeginColor(const CStringRef& cStr, int nPos) override;
	bool Disp() const override{ return true; }
	bool EndColor(const CStringRef& cStr, int nPos) override;

	virtual bool BeginColorEx(const CStringRef& cStr, int nPos, CLayoutInt, const CLayout*);

	//イベント
	void OnStartScanLogic() override;

private:
	CLayoutInt		m_nSelectLine;
	CLogicInt		m_nSelectStart;
	CLogicInt		m_nSelectEnd;
};

class CColor_Found final : public CColorStrategy{
public:
	CColor_Found();
	EColorIndexType GetStrategyColor() const override
	{ return m_validColorNum != 0 ? m_highlightColors[ (m_nSearchResult - 1) % m_validColorNum ] : COLORIDX_DEFAULT; }
	//色替え
	void InitStrategyStatus() override{ } //############要検証
	bool BeginColor(const CStringRef& cStr, int nPos) override;
	bool Disp() const override{ return true; }
	bool EndColor(const CStringRef& cStr, int nPos) override;
	//イベント
	void OnStartScanLogic() override;

private:
	int				m_nSearchResult;
	CLogicInt		m_nSearchStart;
	CLogicInt		m_nSearchEnd;
	EColorIndexType m_highlightColors[ COLORIDX_SEARCHTAIL - COLORIDX_SEARCH + 1 ]; ///< チェックが付いている検索文字列色の配列。
	unsigned int	m_validColorNum = 0; ///< highlightColorsの何番目の要素までが有効か。
};
