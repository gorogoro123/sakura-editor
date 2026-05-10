/*!	@file
	@brief タグジャンプリスト

	@author MIK
	@date 2005.3.31
*/
/*
	Copyright (C) 2005, MIK, genta
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include <vector>
#include "basis/primitive.h"
#include "util/design_template.h"

#define MAX_TAG_STRING_LENGTH _MAX_PATH	//管理する文字列の最大長

/*!	@brief ダイレクトタグジャンプ用検索結果をソートして保持する．
	@author MIK
*/
class CSortedTagJumpList {
public:
	CSortedTagJumpList(int max);
	~CSortedTagJumpList();

	int		AddBaseDir(std::wstring_view baseDir);
	BOOL AddParamA( const ACHAR* keyword, const ACHAR* filename, int no, ACHAR type, const ACHAR* note, int depth, const int baseDirId );
	BOOL GetParam( int index, WCHAR* keyword, WCHAR* filename, int* no, WCHAR* type, WCHAR* note, int* depth, WCHAR* baseDir );
	int GetCount( ){ return static_cast<int>(m_pTagjump.size()); }
	void Empty( );

	struct TagJumpInfo {
		std::wstring	keyword;	//!< キーワード
		std::wstring	filename;	//!< ファイル名
		int		no;			//!< 行番号
		WCHAR	type;		//!< 種類
		std::wstring	note;		//!< 備考
		int		depth;		//!< (さかのぼる)階層
		int		baseDirId;	//!< ファイル名のベースディレクトリ
	};

	TagJumpInfo* GetPtr( int index );

	/*!	@brief 管理数の最大値を取得する

		@date 2005.04.22 genta 最大値を可変に
	*/
	int GetCapacity() const { return m_MAX_TAGJUMPLIST; }

private:
	std::vector<TagJumpInfo> m_pTagjump;	//!< タグジャンプ情報
	std::vector<std::wstring> m_baseDirArr;	//!< ベースディレクトリ情報
	
	//	2005.04.22 genta 最大値を可変に
	const int		m_MAX_TAGJUMPLIST;	//!< 管理する情報の最大数

	DISALLOW_COPY_AND_ASSIGN(CSortedTagJumpList);
};
