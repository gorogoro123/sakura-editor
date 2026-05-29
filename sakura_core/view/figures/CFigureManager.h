/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <vector>
#include "util/design_template.h"
#include "CFigureStrategy.h"

class CFigureManager final : public TSingleton<CFigureManager>{
	friend TSingleton<CFigureManager>;
	CFigureManager();
	virtual ~CFigureManager();

public:
	//! 描画するCFigureを取得
	//	@param	pText	対象文字列の先頭
	//	@param	nTextLen	pTextから行末までの長さ(ただしCRLF==2)
	CFigure& GetFigure(const wchar_t* pText, int nTextLen);

	// 設定変更
	void OnChangeSetting();

private:
	std::vector<std::unique_ptr<CFigure>>	m_vFigures;
	std::vector<CFigure*>	m_vFiguresDisp;	//!< 色分け表示対象
};
