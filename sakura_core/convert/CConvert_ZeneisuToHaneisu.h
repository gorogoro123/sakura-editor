/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CConvert.h"

//!全角英数→半角英数
class CConvert_ZeneisuToHaneisu final : public CConvert{
public:
	bool DoConvert(CNativeW* pcData) override;
};
