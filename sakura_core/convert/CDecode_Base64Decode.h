/*!	@file
	@brief BASE64 Decode

	@author 
*/

/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "convert/CDecode.h"

class CDecode_Base64Decode final : public CDecode{
public:
	bool DoDecode(const CNativeW& cData, CMemory* pcDst) override;
};
