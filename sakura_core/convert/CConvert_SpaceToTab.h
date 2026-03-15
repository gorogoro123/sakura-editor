/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "CConvert.h"

class CCharWidthCache;

class CConvert_SpaceToTab final : public CConvert{
public:
	CConvert_SpaceToTab(int nTabWidth, int nStartColumn, bool bExtEol, CCharWidthCache& cache)
		: m_nTabWidth(nTabWidth), m_nStartColumn(nStartColumn),
		  m_bExtEol(bExtEol), m_cCache(cache)
	{
	}

	bool DoConvert(CNativeW* pcData) override;

private:
	int m_nTabWidth;
	int m_nStartColumn;
	bool m_bExtEol;
	CCharWidthCache& m_cCache;
};
