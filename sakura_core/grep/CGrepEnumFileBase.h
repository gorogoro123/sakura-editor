/*!	@file
	
	@brief GREP support library
	
	@author wakura
	@date 2008/04/28
*/
/*
	Copyright (C) 2008, wakura
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <vector>
#include <windows.h>
#include <cstring>
#include <Shlwapi.h>
#include "grep/CGrepEnumKeys.h"
#include "util/string_ex.h"
#include "util/design_template.h"

typedef std::pair< std::wstring, DWORD > PairGrepEnumItem;
typedef std::vector< PairGrepEnumItem > VPGrepEnumItem;

class CGrepEnumOptions {
public:
	CGrepEnumOptions()
		:m_bIgnoreHidden(false)
		,m_bIgnoreReadOnly(false)
		,m_bIgnoreSystem(false)
	{}
	bool	m_bIgnoreHidden;
	bool	m_bIgnoreReadOnly;
	bool	m_bIgnoreSystem;
};

class CGrepEnumFileBase {
private:
	VPGrepEnumItem m_vpItems;

public:
	CGrepEnumFileBase() noexcept = default;
	virtual ~CGrepEnumFileBase() = default;

	void ClearItems( ){
		m_vpItems.clear();
	}

	BOOL IsExist( LPCWSTR lpFileName ){
		for( const auto& item : m_vpItems ){
			if( item.first == lpFileName ){
				return TRUE;
			}
		}
		return FALSE;
	}

	virtual BOOL IsValid( WIN32_FIND_DATA& w32fd, LPCWSTR pFile = nullptr ){
		if( ! IsExist( pFile ? pFile : w32fd.cFileName ) ){
			return TRUE;
		}
		return FALSE;
	}

	int GetCount( ){
		return (int)m_vpItems.size();
	}

	LPCWSTR GetFileName( int i ){
		if( i < 0 || i >= GetCount() ) return nullptr;
		return m_vpItems[ i ].first.c_str();
	}

	DWORD GetFileSizeLow( int i ){
		if( i < 0 || i >= GetCount() ) return 0;
		return m_vpItems[ i ].second;
	}

	int Enumerates( LPCWSTR lpBaseFolder, VGrepEnumKeys& vecKeys, CGrepEnumOptions& option, CGrepEnumFileBase* pExceptItems = nullptr ){
		int found = 0;

		std::wstring baseFolder = std::wstring(lpBaseFolder ? lpBaseFolder : L"");
		for (const auto &iter : vecKeys){
			std::wstring lpPath = baseFolder + L"\\" + iter;
			// vecKeys[ i ] ==> "subdir\*.h" 等の場合に後で(ファイル|フォルダー)名に "subdir\" を連結する
			const WCHAR* keyDirYen = wcsrchr( iter, L'\\' );
			const WCHAR* keyDirSlash = wcsrchr( iter, L'/' );
			const WCHAR* keyDir;
			if( keyDirYen == nullptr ){
				keyDir = keyDirSlash;
			}else if( keyDirSlash == nullptr ){
				keyDir = keyDirYen;
			}else if( keyDirYen < keyDirSlash ){
				keyDir = keyDirSlash;
			}else{
				keyDir = keyDirYen;
			}
			const auto nKeyDirLen = keyDir ? keyDir - iter + 1 : 0;

			WIN32_FIND_DATA w32fd;
			HANDLE handle = ::FindFirstFile( lpPath.c_str(), &w32fd );
			if( INVALID_HANDLE_VALUE != handle ){
				do{
					if( !::PathMatchSpec(w32fd.cFileName, iter + nKeyDirLen) ){
						continue;
					}
					if( option.m_bIgnoreHidden && (w32fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ){
						continue;
					}
					if( option.m_bIgnoreReadOnly && (w32fd.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ){
						continue;
					}
					if( option.m_bIgnoreSystem && (w32fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) ){
						continue;
					}
					std::wstring lpName(iter, nKeyDirLen);
					lpName += w32fd.cFileName;
					std::wstring lpFullPath = baseFolder + L"\\" + lpName;
					if( IsValid( w32fd, lpName.c_str() ) ){
						if( pExceptItems && pExceptItems->IsExist( lpFullPath.c_str() ) ){
						}else{
							m_vpItems.emplace_back( std::move(lpName), w32fd.nFileSizeLow );
							found++; // 2011.11.19
							if( pExceptItems && nKeyDirLen ){
								// フォルダーを含んだパスなら検索済みとして除外指定に追加する
								pExceptItems->m_vpItems.emplace_back( std::move(lpFullPath), w32fd.nFileSizeLow );
							}
							continue;
						}
					}
				}while( ::FindNextFile( handle, &w32fd ) );
				::FindClose( handle );
			}
		}
		return found;
	}

	DISALLOW_COPY_AND_ASSIGN(CGrepEnumFileBase);
};
