/*! @file */
/*
	Copyright (C) 2008, kobake
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#ifndef SAKURA_STDAPI_29C8A971_234C_46ED_96DB_A2D479992ABE_H_
#define SAKURA_STDAPI_29C8A971_234C_46ED_96DB_A2D479992ABE_H_
#pragma once

namespace ApiWrap
{
	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
	//                      よく使う引数値                         //
	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //

	//! よく使うExtTextOutのオプション
	inline UINT ExtTextOutOption()
	{
		return ETO_CLIPPED | ETO_OPAQUE;
	}

	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
	//                       よく使う用法                          //
	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //

	//! SHIFTを押しているかどうか
	inline bool GetKeyState_Shift()
	{
		return (::GetKeyState(VK_SHIFT)&0x8000)!=0;
	}

	//! CTRLを押しているかどうか
	inline bool GetKeyState_Control()
	{
		return (::GetKeyState(VK_CONTROL)&0x8000)!=0;
	}

	//! ALTを押しているかどうか
	inline bool GetKeyState_Alt()
	{
		return (::GetKeyState(VK_MENU)&0x8000)!=0;
	}
}
#endif /* SAKURA_STDAPI_29C8A971_234C_46ED_96DB_A2D479992ABE_H_ */
