/*! @file */
/*
	Copyright (C) 2012, Moca
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "view/CEditView.h"

class CEditWnd;

/*!
	ミニマップ

	編集ビューのコードを流用して縮小ビューを表示する
 */
class CMiniMapView : public CEditView
{
public:
	CMiniMapView(CEditWnd& cEditWnd)
	: CEditView(cEditWnd)
	{
	}
	BOOL Create( HWND hWndParent );
};
