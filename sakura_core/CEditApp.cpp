/*! @file */
/*
	Copyright (C) 2007, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/

#include "CEditApp.h"
#include "doc/CEditDoc.h"
#include "window/CEditWnd.h"
#include "agent/CLoadAgent.h"
#include "agent/CSaveAgent.h"
#include "uiparts/CVisualProgress.h"
#include "recent/CMruListener.h"
#include "macro/CSMacroMgr.h"
#include "env/CPropertyManager.h"
#include "agent/CGrepAgent.h"
#include "_main/CAppMode.h"
#include "_main/CCommandLine.h"
#include "util/module.h"
#include "util/shell.h"

CEditApp::CEditApp() = default;

CEditApp::~CEditApp() = default;

void CEditApp::Create(HINSTANCE hInst, int nGroupId)
{
	m_hInst = hInst;

	//ヘルパ作成
	m_cIcons.Create( m_hInst );	//	CreateImage List

	//ドキュメントの作成
	m_pcEditDoc = std::make_unique<CEditDoc>(this);

	//IO管理
	m_pcLoadAgent = std::make_unique<CLoadAgent>();
	m_pcSaveAgent = std::make_unique<CSaveAgent>();
	m_pcVisualProgress = std::make_unique<CVisualProgress>();

	//GREPモード管理
	m_pcGrepAgent = std::make_unique<CGrepAgent>();

	//編集モード
	CAppMode::getInstance();	//ウィンドウよりも前にイベントを受け取るためにここでインスタンス作成

	//マクロ
	m_pcSMacroMgr = std::make_unique<CSMacroMgr>();

	//ドキュメントの作成
	m_pcEditDoc->Create();

	//ウィンドウの作成
	m_pcEditWnd = std::make_unique<CEditWnd>();
	m_pcEditWnd->Create( m_pcEditDoc.get(), &m_cIcons, nGroupId);

	//MRU管理
	m_pcMruListener = std::make_unique<CMruListener>();

	//プロパティ管理
	m_pcPropertyManager = std::make_unique<CPropertyManager>();
	m_pcPropertyManager->Create(
		m_pcEditWnd->GetHwnd(),
		&GetIcons(),
		&m_pcEditWnd->GetMenuDrawer()
	);
}

/*! 共通設定 プロパティシート */
bool CEditApp::OpenPropertySheet( int nPageNum )
{
	/* プロパティシートの作成 */
	bool bRet = m_pcPropertyManager->OpenPropertySheet( m_pcEditWnd->GetHwnd(), nPageNum, false );
	if( bRet ){
		// 2007.10.19 genta マクロ登録変更を反映するため，読み込み済みのマクロを破棄する
		m_pcSMacroMgr->UnloadAll();
	}

	return bRet;
}

/*! タイプ別設定 プロパティシート */
bool CEditApp::OpenPropertySheetTypes( int nPageNum, CTypeConfig nSettingType )
{
	bool bRet = m_pcPropertyManager->OpenPropertySheetTypes( m_pcEditWnd->GetHwnd(), nPageNum, nSettingType );

	return bRet;
}
