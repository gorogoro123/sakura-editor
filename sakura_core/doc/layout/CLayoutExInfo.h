/*! @file */
/*
	Copyright (C) 2011, Moca
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#pragma once

#include "util/design_template.h"

class CLayoutColorInfo{
public:
	CLayoutColorInfo(){}
	virtual ~CLayoutColorInfo(){};
	virtual bool IsEqual(const CLayoutColorInfo*)const = 0;
};

class CLayoutExInfo
{
public:
	CLayoutExInfo() : m_colorInfo(nullptr){}
	~CLayoutExInfo(){
		delete m_colorInfo;
	}
	void SetColorInfo(CLayoutColorInfo* p){
		if( m_colorInfo ){
			delete m_colorInfo;
		}
		m_colorInfo = p;
	}
	const CLayoutColorInfo* GetColorInfo() const{
		return m_colorInfo;
	}
	CLayoutColorInfo* DetachColorInfo(){
		CLayoutColorInfo* p = m_colorInfo;
		m_colorInfo = nullptr;
		return p;
	}
private:
	CLayoutColorInfo* m_colorInfo;

	DISALLOW_COPY_AND_ASSIGN(CLayoutExInfo);
};
