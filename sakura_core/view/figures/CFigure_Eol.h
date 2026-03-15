/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "view/figures/CFigureStrategy.h"

//! 改行描画
class CFigure_Eol final : public CFigureSpace{
	using Me = CFigure_Eol;

public:
	CFigure_Eol() noexcept = default;
	CFigure_Eol(const Me&) = delete;
	Me& operator = (const Me&) = delete;
	CFigure_Eol(Me&&) noexcept = delete;
	Me& operator = (Me&&) noexcept = delete;
	~CFigure_Eol()
	{
		if (m_hPen) {
			::DeleteObject(m_hPen);
		}
	}
	//traits
	bool Match(const wchar_t* pText, int nTextLen) const override;
	bool Disp() const override
	{
		return true;
	}

	//action
	bool DrawImp(SColorStrategyInfo* pInfo) override;
	void DispSpace([[maybe_unused]] CGraphics& gr, [[maybe_unused]] DispPos* pDispPos, [[maybe_unused]] CEditView* pcView, [[maybe_unused]] bool bTrans) const  override
	{
	}
	EColorIndexType GetColorIdx() const override { return COLORIDX_EOL; }

private:
	HPEN m_hPen = nullptr;
	COLORREF m_clrPen;
};
