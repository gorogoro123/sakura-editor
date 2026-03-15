/*!	@file
	@brief Unix-to-Unix Decode

	@author 
*/

/*
	Copyright (C) 2018-2026, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "basis/CMyString.h" //SFilePath
#include "convert/CDecode.h"

class CDecode_UuDecode final : public CDecode{
private:
	SFilePath m_aFilename;

public:
	bool DoDecode(const CNativeW& cData, CMemory* pDst) override;
	void CopyFilename(std::span<WCHAR> dst) const { ::wcsncpy_s(std::data(dst), std::size(dst), m_aFilename, _TRUNCATE); }
};
