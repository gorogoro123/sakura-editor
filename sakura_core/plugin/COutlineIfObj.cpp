/*!	@file
	@brief プラグイン基本クラス

*/
/*
	Copyright (C) 2009, syat
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#include "COutlineIfObj.h"
#include "doc/CEditDoc.h"
#include "view/CEditView.h"
#include "outline/CFuncInfoArr.h"


VARTYPE g_OutlineIfObj_MacroArgEx_s[] = {VT_BSTR};
MacroFuncInfoEx g_OutlineIfObj_FuncInfoEx_s = {5, 5, g_OutlineIfObj_MacroArgEx_s};

//コマンド情報
MacroFuncInfo COutlineIfObj::m_MacroFuncInfoCommandArr[] = 
{
	//ID									関数名							引数										戻り値の型	m_pszData
	{EFunctionCode(F_OL_ADDFUNCINFO),		L"AddFuncInfo",				{VT_I4, VT_I4, VT_BSTR, VT_I4},				VT_EMPTY,	nullptr }, //アウトライン解析に追加する
	{EFunctionCode(F_OL_ADDFUNCINFO2),		L"AddFuncInfo2",			{VT_I4, VT_I4, VT_BSTR, VT_I4},				VT_EMPTY,	nullptr }, //アウトライン解析に追加する（深さ指定）
	{EFunctionCode(F_OL_SETTITLE),			L"SetTitle",				{VT_BSTR, VT_EMPTY, VT_EMPTY, VT_EMPTY},	VT_EMPTY,	nullptr },	//アウトラインダイアログタイトルを指定
	{EFunctionCode(F_OL_SETLISTTYPE),		L"SetListType",				{VT_I4, VT_EMPTY, VT_EMPTY, VT_EMPTY},		VT_EMPTY,	nullptr }, //アウトラインリスト種別を指定
	{EFunctionCode(F_OL_SETLABEL),			L"SetLabel",				{VT_I4, VT_BSTR, VT_EMPTY, VT_EMPTY},		VT_EMPTY,	nullptr }, //ラベル文字列を指定
	{EFunctionCode(F_OL_ADDFUNCINFO3),		L"AddFuncInfo3",			{VT_I4, VT_I4, VT_BSTR, VT_I4},				VT_EMPTY,	&g_OutlineIfObj_FuncInfoEx_s }, //アウトライン解析に追加する（ファイル名）
	{EFunctionCode(F_OL_ADDFUNCINFO4),		L"AddFuncInfo4",			{VT_I4, VT_I4, VT_BSTR, VT_I4},				VT_EMPTY,	&g_OutlineIfObj_FuncInfoEx_s }, //アウトライン解析に追加する（ファイル名、深さ指定）

	//	終端
	{F_INVALID,	nullptr, {VT_EMPTY, VT_EMPTY, VT_EMPTY, VT_EMPTY},	VT_EMPTY,	nullptr}
};

//関数情報
MacroFuncInfo COutlineIfObj::m_MacroFuncInfoArr[] = 
{
	//ID									関数名							引数										戻り値の型	m_pszData
	//	終端
	{F_INVALID,	nullptr, {VT_EMPTY, VT_EMPTY, VT_EMPTY, VT_EMPTY},	VT_EMPTY,	nullptr}
};

bool COutlineIfObj::HandleCommand(CEditView* View, EFunctionCode ID, LPCWSTR* Arguments, const int* ArgLengths, const int ArgSize)
{
	switch ( LOWORD(ID) ) 
	{
	case F_OL_ADDFUNCINFO:			//アウトライン解析に追加する
	case F_OL_ADDFUNCINFO2:			//アウトライン解析に追加する（深さ指定）
	case F_OL_ADDFUNCINFO3:			//アウトライン解析に追加する（ファイル名）
	case F_OL_ADDFUNCINFO4:			//アウトライン解析に追加する（ファイル名/深さ指定）
		{
			if( Arguments[0] == nullptr )return false;
			if( Arguments[1] == nullptr )return false;
			if( Arguments[2] == nullptr )return false;
			if( Arguments[3] == nullptr )return false;
			CLogicPoint ptLogic( _wtoi(Arguments[1])-1, _wtoi(Arguments[0])-1 );
			CLayoutPoint ptLayout;
			if( ptLogic.x < 0 || ptLogic.y < 0 ){
				ptLayout.x = (Int)ptLogic.x;
				ptLayout.y = (Int)ptLogic.y;
			}else{
				View->GetDocument()->m_cLayoutMgr.LogicToLayout( ptLogic, &ptLayout );
			}
			int nParam = _wtoi(Arguments[3]);
			if( LOWORD(ID) == F_OL_ADDFUNCINFO ){
				m_cFuncInfoArr.AppendData( ptLogic.GetY()+1, ptLogic.GetX()+1, ptLayout.GetY()+1, ptLayout.GetX()+1, Arguments[2], nullptr, nParam );
			}else if( LOWORD(ID) == F_OL_ADDFUNCINFO2 ){
				int nDepth = nParam & FUNCINFO_INFOMASK;
				nParam -= nDepth;
				m_cFuncInfoArr.AppendData( ptLogic.GetY()+1, ptLogic.GetX()+1, ptLayout.GetY()+1, ptLayout.GetX()+1, Arguments[2], nullptr, nParam, nDepth );
			}else if( LOWORD(ID) == F_OL_ADDFUNCINFO3 ){
				if( ArgSize < 5 || Arguments[4] == nullptr ){ return false; }
				m_cFuncInfoArr.AppendData( ptLogic.GetY()+1, ptLogic.GetX()+1, ptLayout.GetY()+1, ptLayout.GetX()+1, Arguments[2], Arguments[4], nParam );
			}else if( LOWORD(ID) == F_OL_ADDFUNCINFO4 ){
				if( ArgSize < 5 || Arguments[4] == nullptr ){ return false; }
				int nDepth = nParam & FUNCINFO_INFOMASK;
				nParam -= nDepth;
				m_cFuncInfoArr.AppendData( ptLogic.GetY()+1, ptLogic.GetX()+1, ptLayout.GetY()+1, ptLayout.GetX()+1, Arguments[2], Arguments[4], nParam, nDepth );
			}
		}
		break;
	case F_OL_SETTITLE:				//アウトラインダイアログタイトルを指定
		if( Arguments[0] == nullptr )return false;
		m_sOutlineTitle = Arguments[0];
		break;
	case F_OL_SETLISTTYPE:			//アウトラインリスト種別を指定
		if( Arguments[0] == nullptr )return false;
		m_nListType = (EOutlineType)_wtol(Arguments[0]);
		break;
	case F_OL_SETLABEL:				//ラベル文字列を指定
		if( Arguments[0] == nullptr || Arguments[1] == nullptr ) return false;
		{
			std::wstring sLabel = Arguments[1];
			m_cFuncInfoArr.SetAppendText( _wtol(Arguments[0]), sLabel, true );
		}
		break;
	default:
		return CWSHIfObj::HandleCommand(View, ID, Arguments, ArgLengths, ArgSize);
	}
	return true;
}
