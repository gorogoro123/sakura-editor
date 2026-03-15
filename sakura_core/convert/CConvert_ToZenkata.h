/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CConvert.h"

//!できる限り全角カタカナにする
class CConvert_ToZenkata final : public CConvert{
public:
	bool DoConvert(CNativeW* pcData) override;
};
