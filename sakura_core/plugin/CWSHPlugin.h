/*!	@file
	@brief WSHプラグインクラス

*/
/*
	Copyright (C) 2009, syat
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "util/design_template.h"
#include "plugin/CPlugin.h"
#include "macro/CWSHManager.h"

#define PII_WSH						L"Wsh"			//WSHセクション
#define PII_WSH_USECACHE			L"UseCache"		//読み込んだスクリプトを再利用する

class CWSHPlug final :
	public CPlug
{
public:
	CWSHPlug( CPlugin& plugin, PlugId id, std::wstring sJack, std::wstring sHandler, std::wstring sLabel ) :
		CPlug( plugin, id, sJack, sHandler, sLabel )
	{
		m_Wsh = nullptr;
	}
	virtual ~CWSHPlug() {
		if( m_Wsh ){
			delete m_Wsh;
			m_Wsh = nullptr;
		}
	}
	CWSHMacroManager* m_Wsh;

	DISALLOW_COPY_AND_ASSIGN(CWSHPlug);
};

class CWSHPlugin final :
	public CPlugin
{
	//コンストラクタ
public:
	CWSHPlugin( const std::wstring& sBaseDir ) : CPlugin( sBaseDir ) {
		m_bUseCache = false;
	}

	//デストラクタ
public:
	~CWSHPlugin();

	//操作
	//CPlugインスタンスの作成。ReadPluginDefPlug/Command から呼ばれる。
	CPlug* CreatePlug( CPlugin& plugin, PlugId id, std::wstring sJack, std::wstring sHandler, std::wstring sLabel ) override
	{
		return new CWSHPlug( plugin, id, sJack, sHandler, sLabel );
	}

	//実装
public:
	bool ReadPluginDef( CDataProfile *cProfile, CDataProfile *cProfileMlang ) override;
	bool ReadPluginOption( CDataProfile *cProfile ) override;
	CPlug::Array GetPlugs() const override{
		return m_plugs;
	}
	bool InvokePlug( CEditView* view, CPlug& plug, CWSHIfObj::List& params ) override;

	//メンバ変数
private:
	bool m_bUseCache;

	DISALLOW_COPY_AND_ASSIGN(CWSHPlugin);
};
