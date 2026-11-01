/*! @file */
/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#include "DispPos.h"
#include "doc/CEditDoc.h"
#include "doc/layout/CLayout.h"

DispPos::DispPos(int nDx,int nDy)
: m_nDx(nDx)
, m_nDy(nDy)
{
	m_ptDrawOrigin.x=0;
	m_ptDrawOrigin.y=0;
	m_ptDrawLayout.x=CLayoutInt(0);
	m_ptDrawLayout.y=CLayoutInt(0);
	m_nLineRef=CLayoutInt(0);
	//キャッシュ
	m_pcLayoutRef = GetDocument()->m_cLayoutMgr.GetTopLayout();
}

void DispPos::SetLayoutLineRef(CLayoutInt nOffsetLine)
{
	m_nLineRef = nOffsetLine;
	//キャッシュ更新
	m_pcLayoutRef = GetDocument()->m_cLayoutMgr.SearchLineByLayoutY( m_nLineRef );
}

//$$$高速化
void DispPos::ForwardLayoutLineRef(int nOffsetLine)
{
	m_nLineRef += CLayoutInt(nOffsetLine);
	//キャッシュ更新
	int n = nOffsetLine;
	if(m_pcLayoutRef){
		while(n>0 && m_pcLayoutRef){
			m_pcLayoutRef = m_pcLayoutRef->GetNextLayout();
			n--;
		}
		while(n<0 && m_pcLayoutRef){
			m_pcLayoutRef = m_pcLayoutRef->GetPrevLayout();
			n++;
		}
	}
	else{
		m_pcLayoutRef = GetDocument()->m_cLayoutMgr.SearchLineByLayoutY( m_nLineRef );
	}
}
