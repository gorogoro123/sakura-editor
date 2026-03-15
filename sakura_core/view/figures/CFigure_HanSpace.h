/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "view/figures/CFigureStrategy.h"

//! 半角スペース描画
class CFigure_HanSpace final : public CFigureSpace{
public:
	//traits
	bool Match(const wchar_t* pText, int nTextLen) const override;

	//action
	void DispSpace(CGraphics& gr, DispPos* pDispPos, CEditView* pcView, bool trans) const override;
	EColorIndexType GetColorIdx() const override { return COLORIDX_SPACE; }
};
