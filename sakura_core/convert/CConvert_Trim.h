/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CConvert.h"

class CConvert_Trim final : public CConvert{
public:
	CConvert_Trim(bool bLeft, bool bExtEol) : m_bLeft(bLeft), m_bExtEol(bExtEol) { }

public:
	bool DoConvert(CNativeW* pcData) override;

private:
	bool m_bLeft;
	bool m_bExtEol;
};
