/*
	Copyright (C) 2023, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/

#include "pch.h"
#include "charset/CCodePage.h"

TEST(CCodePageTest, InternalCodeType)
{
	WCHAR buf[64]{};
	std::span<WCHAR> out(buf);

	// 例：Shift_JIS（内部コード種別）
	int ret = CCodePage::GetNameNormal(out, CODE_SJIS);

	EXPECT_EQ(ret, 1);
	EXPECT_GT(wcslen(buf), 0u);
	// Normal() の値が入っていることを確認
	EXPECT_STREQ(buf, CCodeTypeName(CODE_SJIS).Normal());
}

TEST(CCodePageTest, CodePageACP)
{
	WCHAR buf[64]{};
	std::span<WCHAR> out(buf);

	int ret = CCodePage::GetNameNormal(out, CODE_CPACP);

	EXPECT_EQ(ret, 2);
	EXPECT_STREQ(buf, L"CP_ACP");
}

TEST(CCodePageTest, CodePageOEM)
{
	WCHAR buf[64]{};
	std::span<WCHAR> out(buf);

	int ret = CCodePage::GetNameNormal(out, CODE_CPOEM);

	EXPECT_EQ(ret, 2);
	EXPECT_STREQ(buf, L"CP_OEM");
}

TEST(CCodePageTest, OtherCodePage)
{
	WCHAR buf[64]{};
	std::span<WCHAR> out(buf);

	// UTF-8 のコードページ番号（65001）
	int ret = CCodePage::GetNameNormal(out, 65001);

	EXPECT_EQ(ret, 2);
	EXPECT_STREQ(buf, L"CP65001");
}
