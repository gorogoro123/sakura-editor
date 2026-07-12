/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/

#include "types/CTypeSupport.h"
#include "doc/CEditDoc.h"
#include "view/CEditView.h"
#include "view/CViewFont.h"
#include "view/colors/CColorStrategy.h"

CTypeSupport::CTypeSupport(const CEditView* pEditView, EColorIndexType eColorIdx)
{
	m_pFontset = &pEditView->GetFontset();
	m_pTypes = &pEditView->m_pcEditDoc->m_cDocType.GetDocumentAttribute();
	m_nColorIdx = ToColorInfoArrIndex(eColorIdx);
	assert(0 <= m_nColorIdx);
	m_pColorInfoArr = &m_pTypes->m_ColorInfoArr[m_nColorIdx];
}

CTypeSupport::~CTypeSupport()
{
	if(m_gr){
		RewindGraphicsState(*m_gr);
	}
}

SFONT CTypeSupport::GetTypeFont()
{
	SFONT sFont;
	sFont.m_sFontAttr = m_pColorInfoArr->m_sFontAttr;
	sFont.m_hFont = m_pFontset->ChooseFontHandle( 0, m_pColorInfoArr->m_sFontAttr );
	return sFont;
}

void CTypeSupport::FillBack(CGraphics& gr,const RECT& rc)
{
	gr.FillSolidMyRect(rc, m_pColorInfoArr->m_sColorAttr.m_cBACK);
}

void CTypeSupport::SetGraphicsState_WhileThisObj(CGraphics& gr)
{
	if(m_gr){
		RewindGraphicsState(*m_gr);
	}

	m_gr = &gr;

	//テキスト色
	gr.PushTextBackColor(GetBackColor());
	gr.PushTextForeColor(GetTextColor());

	//フォント
	gr.PushMyFont(GetTypeFont());
}

void CTypeSupport::RewindGraphicsState(CGraphics& gr)
{
	if(m_gr){
		gr.PopTextBackColor();
		gr.PopTextForeColor();
		gr.PopMyFont();
		m_gr = nullptr;
	}
}
