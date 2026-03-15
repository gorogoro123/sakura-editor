/*! @file */
/*
	Copyright (C) 2015, syat
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "view/figures/CFigureStrategy.h"

//! カンマ描画（CSVモード）
class CFigure_Comma final : public CFigureSpace{
public:
	//traits
	bool Match(const wchar_t* pText, int nTextLen) const override;
	bool Disp() const override;

	//action
	void DispSpace(CGraphics& gr, DispPos* pDispPos, CEditView* pcView, bool bTrans) const override;
	EColorIndexType GetColorIdx() const override { return COLORIDX_TAB; }
};
