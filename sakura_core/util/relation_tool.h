/*! @file */
/*
	関連の管理
*/
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <vector>
#include "util/design_template.h"

class CListener;

//! 複数のCListenerからウォッチされる
class CSubject{
public:
	//コンストラクタ・デストラクタ
	CSubject();
	virtual ~CSubject();

	//公開インターフェース
	int GetListenerCount() const{ return (int)m_vListenersRef.size(); }
	CListener* GetListener(int nIndex) const{ return m_vListenersRef[nIndex]; }

public:
	//管理用
	void _AddListener(CListener* pcListener);
	void _RemoveListener(CListener* pcListener) noexcept;

private:
	std::vector<CListener*> m_vListenersRef;

	DISALLOW_COPY_AND_ASSIGN(CSubject);
};

//! 1つのCSubjectをウォッチする
class CListener{
public:
	CListener();
	virtual ~CListener();

	//公開インターフェース
	CSubject* Listen(CSubject* pcSubject); //!< 直前にウォッチしていたサブジェクトを返す
	CSubject* GetListeningSubject() const{ return m_pcSubjectRef; }

	//管理用
	void		_EndListen() noexcept;

private:
	CSubject* m_pcSubjectRef = nullptr;

	DISALLOW_COPY_AND_ASSIGN(CListener);
};

template <class LISTENER> class CSubjectT : public CSubject{
public:
	LISTENER* GetListener(int nIndex) const
	{
		return static_cast<LISTENER*>(CSubject::GetListener(nIndex));
	}
};

template <class SUBJECT> class CListenerT : public CListener{
public:
	SUBJECT* Listen(SUBJECT* pcSubject)
	{
		return static_cast<SUBJECT*>(CListener::Listen(static_cast<CSubject*>(pcSubject)));
	}
	SUBJECT* GetListeningSubject() const
	{
		return static_cast<SUBJECT*>(CListener::GetListeningSubject());
	}
};
