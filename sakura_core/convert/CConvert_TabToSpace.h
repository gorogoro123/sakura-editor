/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CConvert.h"

class CConvert_TabToSpace final : public CConvert{
public:
	CConvert_TabToSpace(int nTabWidth, int nStartColumn, bool bExtEol)
	: m_nTabWidth(nTabWidth), m_nStartColumn(nStartColumn), m_bExtEol(bExtEol)
	{
	}

	bool DoConvert(CNativeW* pcData) override;

private:
	int m_nTabWidth;
	int m_nStartColumn;
	bool m_bExtEol;
};
