/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

class CSoundSet{
public:
	CSoundSet() : m_nMuteCount(0) { }
	void NeedlessToSaveBeep(); //上書き不要ビープ音
	void MuteOn(){ m_nMuteCount++; }
	void MuteOff(){ m_nMuteCount--; }
private:
	int	m_nMuteCount;
};
