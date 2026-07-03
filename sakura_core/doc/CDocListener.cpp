/*! @file */
/*
	ObserverパターンのCEditDoc特化版。
	CDocSubjectは観察され、CDocListnerは観察を行う。
	観察の開始は CDocListener::Listen で行う。

	$Note:
		Listener (Observer) と Subject のリレーション管理は
		ジェネリックな汎用モジュールに分離できる。
*/
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#include "doc/CDocListener.h"
#include "doc/CEditDoc.h"

bool SLoadInfo::IsSamePath(LPCWSTR pszPath) const
{
	return _wcsicmp(this->cFilePath,pszPath)==0;
}
bool SSaveInfo::IsSamePath(LPCWSTR pszPath) const
{
	return _wcsicmp(this->cFilePath,pszPath)==0;
}

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                       CDocSubject                           //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//(1)

CDocSubject::~CDocSubject()
{
}

template <typename F>
ECallbackResult CDocSubject::NotifyImpl(F&& func)
{
	int n = GetListenerCount();
	for (int i = 0; i < n; i++) {
		ECallbackResult eRet = func(GetListener(i));
		if (eRet != CALLBACK_CONTINUE) return eRet;
	}
	return CALLBACK_CONTINUE;
}

template <typename F>
void CDocSubject::VoidNotifyImpl(F&& func)
{
	int n = GetListenerCount();
	for (int i = 0; i < n; i++) {
		func(GetListener(i));
	}
}

ECallbackResult CDocSubject::NotifyCheckLoad(SLoadInfo* pLoadInfo)
{
	return NotifyImpl([&](auto* l) { return l->OnCheckLoad(pLoadInfo); });
}

void CDocSubject::NotifyBeforeLoad(SLoadInfo* sLoadInfo)
{
	VoidNotifyImpl([&](auto* l) { l->OnBeforeLoad(sLoadInfo); });
}

ELoadResult CDocSubject::NotifyLoad(const SLoadInfo& sLoadInfo)
{
	int n = GetListenerCount();
	ELoadResult eRet = LOADED_FAILURE;
	for (int i = 0; i < n; i++) {
		ELoadResult e = GetListener(i)->OnLoad(sLoadInfo);
		if (e == LOADED_NOIMPLEMENT) continue;
		if (e == LOADED_FAILURE) return e;
		eRet = e;
	}
	return eRet;
}

void CDocSubject::NotifyLoading(int nPer)
{
	VoidNotifyImpl([&](auto* l) { l->OnLoading(nPer); });
}

void CDocSubject::NotifyAfterLoad(const SLoadInfo& sLoadInfo)
{
	VoidNotifyImpl([&](auto* l) { l->OnAfterLoad(sLoadInfo); });
}

void CDocSubject::NotifyFinalLoad(ELoadResult eLoadResult)
{
	VoidNotifyImpl([&](auto* l) { l->OnFinalLoad(eLoadResult); });
}

ECallbackResult CDocSubject::NotifyCheckSave(SSaveInfo* pSaveInfo)
{
	return NotifyImpl([&](auto* l) { return l->OnCheckSave(pSaveInfo); });
}

ECallbackResult CDocSubject::NotifyPreBeforeSave(SSaveInfo* pSaveInfo)
{
	return NotifyImpl([&](auto* l) { return l->OnPreBeforeSave(pSaveInfo); });
}

void CDocSubject::NotifyBeforeSave(const SSaveInfo& sSaveInfo)
{
	VoidNotifyImpl([&](auto* l) { l->OnBeforeSave(sSaveInfo); });
}

void CDocSubject::NotifySave(const SSaveInfo& sSaveInfo)
{
	VoidNotifyImpl([&](auto* l) { l->OnSave(sSaveInfo); });
}

void CDocSubject::NotifySaving(int nPer)
{
	VoidNotifyImpl([&](auto* l) { l->OnSaving(nPer); });
}

void CDocSubject::NotifyAfterSave(const SSaveInfo& sSaveInfo)
{
	VoidNotifyImpl([&](auto* l) { l->OnAfterSave(sSaveInfo); });
}

void CDocSubject::NotifyFinalSave(ESaveResult eSaveResult)
{
	VoidNotifyImpl([&](auto* l) { l->OnFinalSave(eSaveResult); });
}

ECallbackResult CDocSubject::NotifyBeforeClose()
{
	return NotifyImpl([](auto* l) { return l->OnBeforeClose(); });
}

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                       CDocListener                          //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//(多)

CDocListener::CDocListener(CDocSubject* pcDoc)
{
	if(pcDoc==nullptr) pcDoc = GetDocument();
	assert( pcDoc );
	Listen(pcDoc);
}

CDocListener::~CDocListener()
{
}

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                      CDocListenerEx                         //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
#include "doc/CEditDoc.h"

CEditDoc* CDocListenerEx::GetListeningDoc() const
{
	return static_cast<CEditDoc*>(CDocListener::GetListeningDoc());
}

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                     CProgressSubject                        //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
void CProgressSubject::NotifyProgress(int nPer)
{
	int n = GetListenerCount();
	for(int i=0;i<n;i++){
		GetListener(i)->OnProgress(nPer);
	}
}
