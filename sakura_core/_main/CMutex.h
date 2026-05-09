/*!	@file
	@brief Mutex管理

	@author ryoji
	@date 2007.07.05
*/
/*
	Copyright (C) 2007, ryoji, genta
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <Windows.h>
#include "util/design_template.h"

/** ミューテックスを扱うクラス
	@date 2007.07.05 ryoji 新規作成
*/
class CMutex
{
public:
	CMutex( BOOL bInitialOwner, LPCWSTR pszName, LPSECURITY_ATTRIBUTES psa = nullptr )
	{
		m_hObj = ::CreateMutex( psa, bInitialOwner, pszName );
	}
	~CMutex()
	{
		if( nullptr != m_hObj )
		{
			::CloseHandle( m_hObj );
			m_hObj = nullptr;
		}
	}
	BOOL Lock( DWORD dwTimeout = INFINITE )
	{
		DWORD dwRet = ::WaitForSingleObject( m_hObj, dwTimeout );
		if( dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED )
			return TRUE;
		else
			return FALSE;
	}
	BOOL Unlock()
	{
		return ::ReleaseMutex( m_hObj );
	}
	operator HANDLE() const { return m_hObj; }
protected:
	HANDLE m_hObj;
	DISALLOW_COPY_AND_ASSIGN(CMutex);
};

/**	スコープから抜けると同時にロックを解除する．

	@date 2007.07.07 genta 新規作成

	@code
	CMutex aMutex;
	
    void function()
    {
        //  other processing
        {
            LockGuard<CMutex> aGuard(aMutex);
            //  aMutex is locked
            //  do something protected by "aMutex"

        } // aMutex is automatically released
        //  other processing
    }
	@endcode
*/
template<class EXCLUSIVE_OBJECT>
class LockGuard {
	EXCLUSIVE_OBJECT& o_;
public:
	LockGuard(EXCLUSIVE_OBJECT& ex) : o_( ex ){
		o_.Lock();
	}
	template<class PARAM>
	LockGuard(EXCLUSIVE_OBJECT& ex, PARAM p) : o_( ex ){
		o_.Lock(p);
	}
	~LockGuard() {
		o_.Unlock();
	}
	DISALLOW_COPY_AND_ASSIGN(LockGuard);
};
