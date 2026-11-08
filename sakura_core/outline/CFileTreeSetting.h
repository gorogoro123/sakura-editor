/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/

#pragma once

#include "basis/CMyString.h"

// ファイルツリー関連クラス
enum EFileTreeSettingFrom{
	EFileTreeSettingFrom_Common,
	EFileTreeSettingFrom_Type,
	EFileTreeSettingFrom_File
};

enum EFileTreeItemType{
	EFileTreeItemType_Grep,
	EFileTreeItemType_File,
	EFileTreeItemType_Folder
};

struct SFileTreeItem{
	EFileTreeItemType m_eFileTreeItemType = EFileTreeItemType_Grep;
	SFilePath	m_szTargetPath;	//!< フォルダーorファイルパス
	StaticString<_MAX_PATH> m_szLabelName; //!< ラベル名(""のときはファイル名を使う)
	int  m_nDepth = 0;	//!< 階層

	// GrepタイプTreeItem
	StaticString<_MAX_PATH>	m_szTargetFile;	//!< ファイル一覧
	bool		m_bIgnoreHidden = true;		//!< 隠しファイルを除く
	bool		m_bIgnoreReadOnly = false;	//!< 読み取り専用ファイルを除く
	bool		m_bIgnoreSystem = false;		//!< システムファイルを除く

	SFileTreeItem() = default;
};

struct SFileTree{
	bool		m_bProject;			//!< プロジェクトファイルモード
	SFilePath	m_szProjectIni;		//!< デフォルトiniパス
	int			m_nItemCount;		//!< ファイルパス数
	SFileTreeItem	m_aItems[20];	//!< ツリーアイテム
};

class CFileTreeSetting{
public:
	std::vector<SFileTreeItem>	m_aItems;		//!< ツリーアイテム
	bool		m_bProject;				//!< プロジェクトファイルモード
	SFilePath	m_szDefaultProjectIni;	//!< デフォルトiniファイル名
	SFilePath	m_szLoadProjectIni;		//!< 現在読み込んでいるiniファイル名
	EFileTreeSettingFrom	m_eFileTreeSettingOrgType;
	EFileTreeSettingFrom	m_eFileTreeSettingLoadType;
};
