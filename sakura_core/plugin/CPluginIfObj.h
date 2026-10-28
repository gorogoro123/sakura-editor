/*!	@file
	@brief Pluginオブジェクト

*/
/*
	Copyright (C) 2009, syat
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "macro/CWSHIfObj.h"
#include "_os/OleTypes.h"
#include "util/ole_convert.h"

class CPlugin;
class CEditView;

class CPluginIfObj : public CWSHIfObj {
	// 型定義
	enum FuncId {
		F_PL_COMMAND_FIRST = 0,					//↓コマンドは以下に追加する
		F_PL_SETOPTION,							//オプションファイルに値を書く
		F_PL_ADDCOMMAND,						//コマンドを追加する
		F_PL_FUNCTION_FIRST = F_FUNCTION_FIRST,	//↓関数は以下に追加する
		F_PL_GETPLUGINDIR,						//プラグインフォルダーパスを取得する
		F_PL_GETDEF,							//設定ファイルから値を読む
		F_PL_GETOPTION,							//オプションファイルから値を読む
		F_PL_GETCOMMANDNO,						//実行中プラグの番号を取得する
		F_PL_GETSTRING,							//設定ファイルから文字列を読みだす(多言語対応)
	};

public:
	// コンストラクタ
	CPluginIfObj( CPlugin& cPlugin );

	// デストラクタ
	~CPluginIfObj(){}

	// 操作
	void SetPlugIndex(int nIndex) { m_nPlugIndex = nIndex; }
	// 実装
	//コマンド情報を取得する
	MacroFuncInfoArray GetMacroCommandInfo() const
	{
		return m_MacroFuncInfoCommandArr;
	}
	//関数情報を取得する
	MacroFuncInfoArray GetMacroFuncInfo() const
	{
		return m_MacroFuncInfoArr;
	}
	//関数を処理する
	bool HandleFunction(CEditView* View, EFunctionCode ID, VARIANT *Arguments, const int ArgSize, VARIANT &Result) override;
	//コマンドを処理する
	bool HandleCommand(CEditView* View, EFunctionCode ID, LPCWSTR* Arguments, const int* ArgLengths, const int ArgSize) override;

	// メンバ変数
private:
	CPlugin& m_cPlugin;
	static MacroFuncInfo m_MacroFuncInfoCommandArr[];	// コマンド情報(戻り値なし)
	static MacroFuncInfo m_MacroFuncInfoArr[];	// 関数情報(戻り値あり)
	int m_nPlugIndex;	//実行中プラグの番号
};
