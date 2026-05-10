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

#include "env/CSortedTagJumpList.h"
#include "util/tchar_convert.h"

/*!
	@date 2005.04.23 genta 管理数の最大値を指定する引数追加
*/
CSortedTagJumpList::CSortedTagJumpList(int max)
	: m_MAX_TAGJUMPLIST( max )
{
	m_pTagjump.reserve(m_MAX_TAGJUMPLIST);

	// id==0 を 空文字列にする
	m_baseDirArr.emplace_back(L"");
}

CSortedTagJumpList::~CSortedTagJumpList() = default;

/*
	リストをすべて解放する。
*/
void CSortedTagJumpList::Empty( )
{
	m_pTagjump.clear();
	m_baseDirArr.clear();
	m_baseDirArr.push_back(L"");
}

/*
	基準フォルダーを登録し、基準フォルダーIDを取得
	@date 2010.07.23 Moca 新規追加
*/
int CSortedTagJumpList::AddBaseDir(std::wstring_view baseDir)
{
	m_baseDirArr.emplace_back(baseDir);
	return int(m_baseDirArr.size() - 1);
}

/*
	アイテムをソートされた状態でリストに追加する。
	アイテムが最大数を超える場合は、超えるアイテムを削除する。
	文字列はコピーを作成するので、呼び出し側は文字列のアドレス先を保持する必要はない。
	
	@param[in] keyword	キーワード
	@param[in] filename	ファイル名
	@param[in] no		行番号
	@param[in] type		種類
	@param[in] note		備考
	@param[in] depth	(さかのぼる)階層
	@param[in] baseDirId	基準フォルダーID。0で空文字列指定 (AddBaseDirの戻り値)
	@retval TRUE  追加した
	@retval FALSE 追加失敗
	@date 2010.07.23 Moca baseDirId 追加
*/
BOOL CSortedTagJumpList::AddParamA( const ACHAR* keyword, const ACHAR* filename, int no,
	ACHAR type, const ACHAR* note, int depth, int baseDirId )
{
	//アイテムを作成する。
	TagJumpInfo item = {
		.keyword = to_wchar(keyword),
		.filename = to_wchar(filename),
		.no       = no,
		.type     = (WCHAR)type,
		.note     = to_wchar(note),
		.depth    = depth,
		.baseDirId = baseDirId,
	};

	//文字列長ガード
	if( item.keyword.length() >= MAX_TAG_STRING_LENGTH ) item.keyword.resize(MAX_TAG_STRING_LENGTH-1);
	if( item.filename.length() >= MAX_TAG_STRING_LENGTH ) item.filename.resize(MAX_TAG_STRING_LENGTH-1);
	if( item.note.length() >= MAX_TAG_STRING_LENGTH ) item.note.resize(MAX_TAG_STRING_LENGTH-1);

	//アイテムをリストの適当な位置に追加する。
	auto it = std::lower_bound(
		m_pTagjump.begin(),
		m_pTagjump.end(),
		item,
		[](const TagJumpInfo& a, const TagJumpInfo& b){
			return a.keyword < b.keyword;
		}
	);

	m_pTagjump.insert(it, std::move(item));

	//最大数を超えたら最後のアイテムを削除する。
	if(m_pTagjump.size() > m_MAX_TAGJUMPLIST)
	{
		m_pTagjump.pop_back();
	}
	return TRUE;
}

/*
	指定の情報を取得する。

	@param[out] keyword		キーワード
	@param[out] filename	ファイル名
	@param[out] no			行番号
	@param[out] type		種類
	@param[out] note		備考
	@param[out] depth		(さかのぼる)階層
	@param[out] baseDir		ファイル名の基準フォルダー
	@return 処理結果

	@note 不要な情報の場合は引数に NULL を指定する。
*/
BOOL CSortedTagJumpList::GetParam( int index, WCHAR* keyword, WCHAR* filename, int* no, WCHAR* type, WCHAR* note, int* depth, WCHAR* baseDir )
{
	if( keyword  ) keyword[0] = L'\0';
	if( filename ) filename[0] = L'\0';
	if( no       ) *no    = 0;
	if( type     ) *type  = 0;
	if( note     ) note[0] = L'\0';
	if( depth    ) *depth = 0;
	if( baseDir  ) baseDir[0] = L'\0';

	CSortedTagJumpList::TagJumpInfo* p;
	p = GetPtr( index );
	if( nullptr != p )
	{
		if( keyword  ) wcscpy( keyword, p->keyword.c_str() );
		if( filename ) wcscpy( filename, p->filename.c_str() );
		if( no       ) *no    = p->no;
		if( type     ) *type  = p->type;
		if( note     ) wcscpy( note, p->note.c_str() );
		if( depth    ) *depth = p->depth;
		if( baseDir ){
			if( 0 <= p->baseDirId && (size_t)p->baseDirId < m_baseDirArr.size() ){
				wcscpy( baseDir, m_baseDirArr[p->baseDirId].c_str() );
			}
		}
		return TRUE;
	}
	return FALSE;
}

/*
	指定の情報を構造体ポインタで取得する。
	取得した情報は参照なので解放してはならない。

	@param[in] index 要素番号
	@return タグジャンプ情報
*/
CSortedTagJumpList::TagJumpInfo* CSortedTagJumpList::GetPtr( int index )
{
	if( index < 0 || index >= static_cast<int>(m_pTagjump.size()) ){
		return nullptr;
	}
	return &m_pTagjump[index];
}