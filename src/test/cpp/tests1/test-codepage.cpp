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

// 内部コード種別（IsValidCodeType == true）の場合のテスト
TEST( CCodePageTest, GetNameShort_InternalCodeType )
{
	WCHAR buf[64]{};
	std::span<WCHAR> out(buf);

	int ret = CCodePage::GetNameShort(out, CODE_SJIS);

	EXPECT_EQ(ret, 1);
	EXPECT_STRNE(buf, L"");
	EXPECT_STREQ(buf, CCodeTypeName(CODE_SJIS).Short());
}

// 特殊なWindowsコードページ（CP_ACP, CP_OEMCP）の場合のテスト
TEST( CCodePageTest, GetNameShort_SpecialCodePage )
{
	// ケース：CP_ACP
	{
		WCHAR buf[64]{};
		std::span<WCHAR> out(buf);

		int ret = CCodePage::GetNameShort(out, CODE_CPACP);

		EXPECT_EQ(ret, 2);
		EXPECT_STREQ(buf, L"cp_acp");
	}

	// ケース：CP_OEMCP
	{
		WCHAR buf[64]{};
		std::span<WCHAR> out(buf);

		int ret = CCodePage::GetNameShort(out, CODE_CPOEM);

		EXPECT_EQ(ret, 2);
		EXPECT_STREQ(buf, L"cp_oem");
	}
}

// 一般的なWindowsコードページ（"cpXXXX" となるパターン）のテスト
TEST( CCodePageTest, GetNameShort_GeneralCodePage )
{
	WCHAR buf[64]{};
	std::span<WCHAR> out(buf);

	int ret = CCodePage::GetNameShort(out, 65001);

	EXPECT_EQ(ret, 2);
	EXPECT_STREQ(buf, L"cp65001");
}

// バッファサイズが足りない（切り詰め発生）時の安全性テスト
TEST( CCodePageTest, GetNameShort_BufferTruncate )
{
	WCHAR smallBuf[5]{};
	std::span<WCHAR> out(smallBuf);

	int ret = CCodePage::GetNameShort(out, 65001);

	EXPECT_EQ(ret, 2);
	EXPECT_STREQ(smallBuf, L"cp65");
}