/*!	@file
	@brief DLLプラグインクラス

*/
/*
	Copyright (C) 2009, syat
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CPlugin.h"

#define	PII_DLL							L"Dll"			//DLL情報
#define	PII_DLL_NAME					L"Name"			//名前

typedef void (*DllPlugHandler)();

class CDllPlug final
	: public CPlug
{
public:
	CDllPlug( CPlugin& plugin, PlugId id, std::wstring sJack, std::wstring sHandler, std::wstring sLabel )
		: CPlug( plugin, id, sJack, sHandler, sLabel )
		, m_handler( nullptr )
	{
	}
public:
	DllPlugHandler m_handler;
};

class CDllPlugin final
	: public CPlugin, public CDllImp
{
	//コンストラクタ
public:
	CDllPlugin( const std::wstring& sBaseDir ) : CPlugin( sBaseDir ), CDllImp() {
	}

	//デストラクタ
public:
	~CDllPlugin();

	//実装
public:
	bool ReadPluginDef( CDataProfile *cProfile, CDataProfile *cProfileMlang ) override;
	bool ReadPluginOption( [[maybe_unused]] CDataProfile *cProfile ) override{
		return true;
	}
	CPlug* CreatePlug( CPlugin& plugin, PlugId id, std::wstring sJack, std::wstring sHandler, std::wstring sLabel ) override;
	CPlug::Array GetPlugs() const override{
		return m_plugs;
	}
	bool InvokePlug( CEditView* view, CPlug& plug, CWSHIfObj::List& params ) override;

	bool InitDllImp() override {
		return true;
	}
	LPCWSTR GetDllNameImp([[maybe_unused]] int nIndex) override {
		return L"";
	}

	//メンバ変数
private:
	std::wstring m_sDllName;
};
