/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CConvert.h"

//!半角カナ→全角カナ
class CConvert_HankataToZenkata final : public CConvert{
public:
	bool DoConvert(CNativeW* pcData) override;
};
