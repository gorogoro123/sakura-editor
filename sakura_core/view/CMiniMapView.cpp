/*! @file */
/*
	Copyright (C) 2012, Moca
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/

#include "view/CMiniMapView.h"
#include "doc/CEditDoc.h"

BOOL CMiniMapView::Create( HWND hWndParent )
{
	return CEditView::Create( hWndParent, -1, FALSE, true );
}
