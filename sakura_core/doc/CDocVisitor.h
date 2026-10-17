/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "basis/CEol.h"

class CEditDoc;

class CDocVisitor{
public:
	CDocVisitor(CEditDoc& cEditDoc) : m_cDocRef(cEditDoc) { }

	void SetAllEol(CEol cEol); //!< 改行コードを統一する
private:
	CEditDoc& m_cDocRef;
};
