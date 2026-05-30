/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/

#include "types/CType.h"

void CType_CorbaIdl::InitTypeConfigImp(STypeConfig* pType)
{
}

const auto g_ppszKeywordsCORBA_IDL = std::to_array<const wchar_t*>({
	L"any",
	L"attribute",
	L"boolean",
	L"case",
	L"char",
	L"const",
	L"context",
	L"default",
	L"double",
	L"enum",
	L"exception",
	L"FALSE",
	L"fixed",
	L"float",
	L"in",
	L"inout",
	L"interface",
	L"long",
	L"module",
	L"Object",
	L"octet",
	L"oneway",
	L"out",
	L"raises",
	L"readonly",
	L"sequence",
	L"short",
	L"string",
	L"struct",
	L"switch",
	L"TRUE",
	L"typedef",
	L"unsigned",
	L"union",
	L"void",
	L"wchar_t",
	L"wstring"
});

std::span<const KeywordConfig> CType_CorbaIdl::GetKeywordConfigs() const
{
	static constexpr auto configs = std::to_array<KeywordConfig>({
		{ L"CORBA IDL", true, g_ppszKeywordsCORBA_IDL }
	});
	return configs;
}
