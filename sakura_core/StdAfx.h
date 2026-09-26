/*! @file */
/*
	Copyright (C) 2018-2022, Sakura Editor Organization

	SPDX-License-Identifier: Zlib
*/

#pragma once

// 標準C++ヘッダー（追加するときは昇順で。）
#include <algorithm>
#include <array>
#include <atomic>
#include <cassert>
#include <climits>
#include <clocale>
#include <cmath>
#include <concepts>
#include <condition_variable>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <filesystem>
#include <format>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numeric>
#include <optional>
#include <ranges>
#include <regex>
#include <set>
#include <source_location>
#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cerrno>

// Windowsヘッダー(他のSDKヘッダーとは別格。)
#include <Windows.h>

// windowsx.h (他のSDKヘッダーとは別格。)
#include <windowsx.h>

// その他のWindows SDK ヘッダー（ファイル名は最新に合わせる。追加するときは昇順で。）
#include <comdef.h>
#include <CommCtrl.h>
#include <HtmlHelp.h>
#include <imm.h>
#include <oaidl.h>
#include <shellapi.h>
#include <ShlDisp.h>
#include <ShlObj.h>
#include <Uxtheme.h>
#include <vsstyle.h>
#include <wrl.h>
#include <wrl/client.h>
