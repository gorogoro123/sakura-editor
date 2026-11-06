/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	This source code is designed for sakura editor.
	Please contact the copyright holder to use this code for other purpose.
*/

#pragma once

class CDropTargetHandler
{
public:
	virtual ~CDropTargetHandler() = default;

	virtual HRESULT DragEnter(LPDATAOBJECT pDataObject, DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect) = 0;
	virtual HRESULT DragOver(DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect) = 0;
	virtual HRESULT DragLeave() = 0;
	virtual HRESULT Drop(LPDATAOBJECT pDataObject, DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect) = 0;
};
