/*! @file */
/*
	Copyright (C) 2021-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/
#include "pch.h"
#include "view/colors/CColor_Numeric.h"

TEST(IsNumber, ComprehensiveSpecificationTest)
{
	auto check = [](const wchar_t* str) {
		std::wstring_view wstr(str);
		return CColor_Numeric::IsNumber(std::span<const WCHAR>(wstr.data(), wstr.size()), 0);
	};

	// ==========================================
	// 1. 先頭 '0' から始まるケース（10進数、16進数、指数など）
	// ==========================================
	ASSERT_EQ(1, check(L"0"));         // 単体の '0'
	ASSERT_EQ(1, check(L"0x"));        // "0x" のみ -> "0" だけが数値 (1)
	ASSERT_EQ(6, check(L"0xfedc"));    // 正常な16進数 ("0xfedc" = 6文字)
	ASSERT_EQ(4, check(L"0x1L"));      // 16進数 + 接尾語 L
	ASSERT_EQ(3, check(L"0.5"));       // 小数 (0.5)
	ASSERT_EQ(1, check(L"0E"));        // "0E" -> "0" だけが数値 (1)
	ASSERT_EQ(3, check(L"0e2"));       // 指数表記 (0e2)

	// ==========================================
	// 2. 先頭 '1'～'9' から始まる10進数ケース
	// ==========================================
	ASSERT_EQ(3, check(L"123"));       // 通常の整数
	ASSERT_EQ(4, check(L"0123"));      // 0始まりの10進数
	ASSERT_EQ(3, check(L"123."));      // 末尾が "." -> "." を含めない (123)
	ASSERT_EQ(2, check(L"1L"));        // 整数 + 接尾語 L
	ASSERT_EQ(2, check(L"1F"));        // 整数 + 接尾語 F
	ASSERT_EQ(4, check(L"1.2f"));      // 小数 + 接尾語 f
	ASSERT_EQ(6, check(L"1.2e+3"));    // 指数表記 (符号付き)
	ASSERT_EQ(6, check(L"1.2e-3"));    // 指数表記 (符号付き)

	// ==========================================
	// 3. マイナス '-' から始まるケース
	// ==========================================
	ASSERT_EQ(0, check(L"-"));         // "-" のみ -> 数値ではない (0)
	ASSERT_EQ(0, check(L"-."));        // "-." のみ -> 数値ではない (0)
	ASSERT_EQ(4, check(L"-123"));      // 負の整数
	ASSERT_EQ(3, check(L"-.5"));       // 負の小数（".5"として判定、マイナス含む）
	ASSERT_EQ(4, check(L"-1e0"));      // 負の指数表記

	// ==========================================
	// 4. 小数点 '.' から始まるケース
	// ==========================================
	ASSERT_EQ(0, check(L"."));         // "." のみ -> 数値ではない (0)
	ASSERT_EQ(2, check(L".5"));        // 小数 (.5)
	ASSERT_EQ(3, check(L".5f"));       // 小数 + 接尾語 f
	ASSERT_EQ(5, check(L"1.2.3"));     // ドット連続の挙動（全体を消費して 5）

	// ==========================================
	// 5. 非数値・中断・例外的なケース
	// ==========================================
	ASSERT_EQ(0, check(L"abc"));       // 完全な非数値
	ASSERT_EQ(0, check(L""));          // 空文字
}
