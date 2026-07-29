/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/

#include "CFigureManager.h"
#include "CFigure_Tab.h"
#include "CFigure_Comma.h"
#include "CFigure_HanSpace.h"
#include "CFigure_ZenSpace.h"
#include "CFigure_Eol.h"
#include "CFigure_CtrlCode.h"

CFigureManager::CFigureManager()
{
	m_vFigures.emplace_back(std::make_unique<CFigure_Tab>());
	m_vFigures.emplace_back(std::make_unique<CFigure_Comma>());
	m_vFigures.emplace_back(std::make_unique<CFigure_HanSpace>());
	m_vFigures.emplace_back(std::make_unique<CFigure_ZenSpace>());
	m_vFigures.emplace_back(std::make_unique<CFigure_Eol>());
	m_vFigures.emplace_back(std::make_unique<CFigure_CtrlCode>());
	m_vFigures.emplace_back(std::make_unique<CFigure_Text>());

	OnChangeSetting();
}

CFigureManager::~CFigureManager() = default;

//$$ 高速化可能
CFigure& CFigureManager::GetFigure(const wchar_t* pText, int nTextLen)
{
	for(auto& figureDisp : m_vFiguresDisp){
		if(figureDisp->Match(pText, nTextLen)){
			return *figureDisp;
		}
	}

	assert(0);
	return *m_vFiguresDisp.back();
}

/*! 設定更新
*/
void CFigureManager::OnChangeSetting()
{
	m_vFiguresDisp.clear();

	for(auto& figure : m_vFigures){
		figure->Update();
		// 色分け表示対象のみを登録
		if( figure->Disp() ){
			m_vFiguresDisp.push_back(figure.get());
		}
	}
}
