/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CConvert.h"

//!できる限り全角ひらがなにする
class CConvert_ToZenhira final : public CConvert{
public:
	bool DoConvert(CNativeW* pcData) override;
};
