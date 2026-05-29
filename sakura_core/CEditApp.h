/*! @file */
/*
	Copyright (C) 2007, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

//2007.10.23 kobake 作成

#include "util/design_template.h"
#include "uiparts/CSoundSet.h"
#include "uiparts/CImageListMgr.h"
#include "types/CType.h"

class CEditDoc;
class CEditWnd;
class CLoadAgent;
class CSaveAgent;
class CVisualProgress;
class CMruListener;
class CSMacroMgr;
class CPropertyManager;
class CGrepAgent;

//!エディタ部分アプリケーションクラス。CNormalProcess1個につき、1個存在。
class CEditApp final : public TSingleton<CEditApp>{
	friend TSingleton<CEditApp>;
	CEditApp();
	virtual ~CEditApp();

public:
	void Create(HINSTANCE hInst, int);

	bool OpenPropertySheet( int nPageNum );
	bool OpenPropertySheetTypes( int nPageNum, CTypeConfig nSettingType );

	HINSTANCE GetAppInstance() const { return m_hInst; }

	CEditDoc* GetDocument() { return m_pcEditDoc.get(); }

	CEditWnd* GetEditWindow() { return m_pcEditWnd.get(); }

	CLoadAgent* GetLoadAgent() { return m_pcLoadAgent.get(); }
	CSaveAgent* GetSaveAgent() { return m_pcSaveAgent.get(); }
	CVisualProgress* GetVisualProgress() { return m_pcVisualProgress.get(); }

	CMruListener* GetMruListener() { return m_pcMruListener.get(); }
	CSMacroMgr* GetMacroMgr() { return m_pcSMacroMgr.get(); }

	CPropertyManager* GetPropertyManager() { return m_pcPropertyManager.get(); }

	CGrepAgent* GetGrepAgent() { return m_pcGrepAgent.get(); }

	CSoundSet& GetSoundSet() { return m_cSoundSet; }

	CImageListMgr& GetIcons() { return m_cIcons; }

private:
	HINSTANCE			m_hInst;

	//ドキュメント
	std::unique_ptr<CEditDoc>			m_pcEditDoc;

	//ウィンドウ
	std::unique_ptr<CEditWnd>			m_pcEditWnd;

	//IO管理
	std::unique_ptr<CLoadAgent>			m_pcLoadAgent;
	std::unique_ptr<CSaveAgent>			m_pcSaveAgent;
	std::unique_ptr<CVisualProgress>	m_pcVisualProgress;

	//その他ヘルパ
	std::unique_ptr<CMruListener>		m_pcMruListener;		//MRU管理
	std::unique_ptr<CSMacroMgr>			m_pcSMacroMgr;			//マクロ管理

	std::unique_ptr<CPropertyManager>	m_pcPropertyManager;	//プロパティ管理

	std::unique_ptr<CGrepAgent>			m_pcGrepAgent;			//GREPモード
	CSoundSet							m_cSoundSet;			//サウンド管理

	//GUIオブジェクト
	CImageListMgr						m_cIcons;				//!< Image List
};

//WM_QUIT検出例外
class CAppExitException : public std::exception{
public:
	const char* what() const throw() override{ return "CAppExitException"; }
};
