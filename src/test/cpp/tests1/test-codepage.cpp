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

// 1. 正常系：バッファサイズが十分な場合
TEST( CCodePageTest, GetNameLong_Success )
{
	WCHAR buf[64]{};
	std::span<WCHAR> out(buf);

	int ret = CCodePage::GetNameLong(out, CODE_UTF8);

	EXPECT_EQ(ret, 1);
	
	EXPECT_STRNE(buf, L""); 
}

// 2. 正常系：GetCPInfoEx を通るパターン（例: CP932 / Shift_JIS）
TEST( CCodePageTest, GetNameLong_CP932 )
{
	WCHAR buf[128]{};
	std::span<WCHAR> out(buf);

	int ret = CCodePage::GetNameLong(out, 932);

	EXPECT_EQ(ret, 2);
	EXPECT_STRNE(buf, L""); // 最低限、空文字ではないことを検証
}

// バッファサイズが足りない（切り詰め発生）時の安全性テスト
TEST( CCodePageTest, GetNameLong_BufferTruncate )
{
	WCHAR smallBuf[5]{};
	std::span<WCHAR> out(smallBuf);

	int ret = CCodePage::GetNameLong(out, CODE_CPACP);

	EXPECT_EQ(ret, 2);
	
	EXPECT_STREQ(smallBuf, L"CP_A");
}

// 内部コード種別（IsValidCodeType == true）の場合のテスト
TEST( CCodePageTest, GetNameBracket_InternalCodeType )
{
	WCHAR buf[64]{};
	std::span<WCHAR> out(buf);

	int ret = CCodePage::GetNameBracket(out, CODE_SJIS);

	EXPECT_EQ(ret, 1);
	EXPECT_STRNE(buf, L"");
	EXPECT_STREQ(buf, CCodeTypeName(CODE_SJIS).Bracket());
}

// 特殊なWindowsコードページ（CP_ACP, CP_OEMCP）の場合のテスト
TEST( CCodePageTest, GetNameBracket_SpecialCodePage )
{
	// ケース：CP_ACP
	{
		WCHAR buf[64]{};
		std::span<WCHAR> out(buf);

		int ret = CCodePage::GetNameBracket(out, CODE_CPACP);

		EXPECT_EQ(ret, 2);
		EXPECT_STREQ(buf, L"  [CP_ACP]");
	}

	// ケース：CP_OEMCP
	{
		WCHAR buf[64]{};
		std::span<WCHAR> out(buf);

		int ret = CCodePage::GetNameBracket(out, CODE_CPOEM);

		EXPECT_EQ(ret, 2);
		EXPECT_STREQ(buf, L"  [CP_OEM]");
	}
}

// 一般的なWindowsコードページ（"  [CPXXXX]" となるパターン）のテスト
TEST( CCodePageTest, GetNameBracket_GeneralCodePage )
{
	WCHAR buf[64]{};
	std::span<WCHAR> out(buf);

	int ret = CCodePage::GetNameBracket(out, 65001);

	EXPECT_EQ(ret, 2);
	EXPECT_STREQ(buf, L"  [CP65001]");
}

// バッファサイズが足りない（切り詰め発生）時の安全性テスト
TEST( CCodePageTest, GetNameBracket_BufferTruncate )
{
	// "  [CP_ACP]"（先頭スペース2つ、ヌル含め11要素必要）に対して、6要素のバッファを渡す
	WCHAR smallBuf[6]{};
	std::span<WCHAR> out(smallBuf);

	int ret = CCodePage::GetNameBracket(out, CODE_CPACP);

	EXPECT_EQ(ret, 2);
	
	// wcsncpy_s(..., _TRUNCATE) により、6要素に対して「5文字 + ヌル終端 L'\0'」
	// つまり "  [CP" まで安全に切り詰められることを検証
	EXPECT_STREQ(smallBuf, L"  [CP");
}
