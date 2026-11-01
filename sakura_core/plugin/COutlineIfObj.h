/*!	@file
	@brief Outlineオブジェクト

*/
/*
	Copyright (C) 2009, syat
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "macro/CWSHIfObj.h"
#include "outline/CFuncInfo.h"	// FUNCINFO_INFOMASK

class CEditView;
class CFuncInfoArr;

class COutlineIfObj : public CWSHIfObj {
	// 型定義
	enum FuncId {
		F_OL_COMMAND_FIRST = 0,					//↓コマンドは以下に追加する
		F_OL_ADDFUNCINFO,						//アウトライン解析に追加する
		F_OL_ADDFUNCINFO2,						//アウトライン解析に追加する（深さ指定）
		F_OL_SETTITLE,							//アウトラインダイアログタイトルを指定
		F_OL_SETLISTTYPE,						//アウトラインリスト種別を指定
		F_OL_SETLABEL,							//ラベル文字列を指定
		F_OL_ADDFUNCINFO3,						//アウトライン解析に追加する（ファイル名）
		F_OL_ADDFUNCINFO4,						//アウトライン解析に追加する（深さ指定、ファイル名）
		F_OL_FUNCTION_FIRST = F_FUNCTION_FIRST	//↓関数は以下に追加する
	};

	// コンストラクタ
public:
	COutlineIfObj( CFuncInfoArr& cFuncInfoArr )
		: CWSHIfObj( L"Outline", false )
		, m_nListType( OUTLINE_PLUGIN )
		, m_cFuncInfoArr( cFuncInfoArr )
	{
	}

	// デストラクタ
public:
	~COutlineIfObj(){}

	// 実装
public:
	//コマンド情報を取得する
	MacroFuncInfoArray GetMacroCommandInfo() const{ return m_MacroFuncInfoCommandArr; }
	//関数情報を取得する
	MacroFuncInfoArray GetMacroFuncInfo() const{ return m_MacroFuncInfoArr; }

	//コマンドを処理する
	bool HandleCommand(CEditView* View, EFunctionCode ID, LPCWSTR* Arguments, const int* ArgLengths, const int ArgSize) override;

	// メンバ変数
public:
	std::wstring m_sOutlineTitle;
	EOutlineType m_nListType;
private:
	CFuncInfoArr& m_cFuncInfoArr;
	static MacroFuncInfo m_MacroFuncInfoCommandArr[];	// コマンド情報(戻り値なし)
	static MacroFuncInfo m_MacroFuncInfoArr[];	// 関数情報(戻り値あり)
};
