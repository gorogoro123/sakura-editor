/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CConvert.h"

//!半角カナ→全角ひらがな
class CConvert_HankataToZenhira final : public CConvert{
public:
	bool DoConvert(CNativeW* pcData) override;
};
