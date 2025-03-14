#pragma once

#define SPDLOG_VERSION "0.17.0"

#include "tweakme.h"

#include <atomic>
#include <chrono>
#include <exception>
#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>

#if defined(_WIN32) && defined(SPDLOG_WCHAR_FILENAMES)
	#include <codecvt> // 用于在不同字符编码之间进行转换，例如从宽字符到多字节字符的转换。
	#include <locale> // 提供了与区域设置相关的功能，支持国际化和本地化。
#endif

namespace spdlog {
	namespace sinks {
		class sink;
	}

	namespace level {
		enum level_num
		{
			trace = 0,
			debug = 1,
			info = 2,
			warn = 3,
			err = 4,
			critical = 5,
			off = 6
		};

	}
}


