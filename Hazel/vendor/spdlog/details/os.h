#pragma once

#include "../common.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>

#ifdef _WIN32

	#ifndef NOMINMAX
	#define NOMINMAX // 去除 windows.h 最大最小函数，一般在程序想使用标准库而非 windows.h 库的最大最小函数时使用。
	#endif

	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN // 去除 windows.h 中的 n 种模块，具体根据版本不同有变化。目的是减少引入的代码量，减少命名污染，后面真的有需要再进行声明。
	#endif

	#include <windows.h>

	#include <io.h>      // _get_osfhandle and _isatty support
	#include <process.h> //  _get_pid support

	#ifdef __MINGW32__  // __MINGW32__ 是一个预处理器宏，用于检测代码是否在 MinGW（Minimalist GNU for Windows）环境下编译。MinGW 是一个常用的工具链，允许在 Windows 上使用 GCC 编译器来编译 C 和 C++ 程序。
	#include <share.h>  // 提供了一些用于文件共享模式的定义和函数。这些定义通常用于控制文件的共享访问权限。
	#endif 

#else // unix

	#include <fcntl.h>
	#include <unistd.h>

	#ifdef __linux__
	#include <sys/syscall.h> //Use gettid() syscall under linux to get thread id
	#elif __FreeBSD__
	#include <sys/thr.h> //Use thr_self() syscall under FreeBSD to get thread id
	#endif

#endif

#ifndef __has_feature      // Clang - feature checking macros.
#define __has_feature(x) 0 // 如果 __has_feature 未定义（通常在非 Clang 编译器中会是这种情况），就将其定义为 0。这样，任何使用 __has_feature(x) 的特性检查都会返回 0（即不支持该特性）。
#endif // 这个模式确保了即使在不支持 Clang 特性检查的编译器上，代码也能正常编译，而不会因为找不到 __has_feature 而报错。


namespace spdlog {
	namespace details {
		namespace os {
			inline spdlog::log_clock::time_point now() {


			}
			
			// corecrt.h 提供了许多基础的 C 运行时功能和定义，是其他许多 CRT 头文件的基础。它通常包含一些基本的宏、类型定义和函数声明。
			// 将一个 time_t 类型的时间值转换为 std::tm 结构 转换为本地时间
			// std::tm 是一个结构体，用于存储分解后的日期和时间信息。它包括字段如 tm_year（从1900年开始的年数）、tm_mon（从一月开始的月数）、tm_mday（一个月中的第几天）、tm_hour（从午夜开始的小时数）等。
			// 据说转换后的时间 年份要加上 1900 月份要加上 1
			inline std::tm localtime(const std::time_t& time_tt) {
#ifdef _WIN32
				// localtime_s 是 localtime 的线程安全版本，用于将 time_t 类型的值（通常表示自1970年1月1日以来的秒数）转换为表示本地时间的 std::tm 结构。
				std::tm tm;
				localtime_s(&tm, &time_tt);
#else
				std::tm tm;
				localtime_r(&time_tt, &tm);
#endif
				return tm;
			}

			inline std::tm localtime() {
				std::time_t now_t = time(nullptr);
				return localtime(now_t);
			}

			// 将一个 time_t 类型的时间值转换为 std::tm 结构 转换为协调世界时（UTC）
			inline std::tm gmtime(const std::time_t& time_tt) {
#ifdef _WIN32
				// gmtime_s 是 gmtime 的安全版本，用于将 time_t 类型的值（通常表示自1970年1月1日以来的秒数）转换为表示 UTC 时间的 std::tm 结构。
				std::tm tm;
				gmtime_s(&tm, &time_tt);
#else
				std::tm tm;
				gmtime_r(&time_tt, &tm);
#endif
				return tm;
			}

			inline std::tm gmtime()
			{
				std::time_t now_t = time(nullptr);
				return gmtime(now_t);
			}

			inline bool operator==(const std::tm& tm1, const std::tm& tm2) {
				return (tm1.tm_sec == tm2.tm_sec && tm1.tm_min == tm2.tm_min && tm1.tm_hour == tm2.tm_hour && tm1.tm_mday == tm2.tm_mday &&
					tm1.tm_mon == tm2.tm_mon && tm1.tm_year == tm2.tm_year && tm1.tm_isdst == tm2.tm_isdst);
			}

			inline bool operator!=(const std::tm& tm1, const std::tm& tm2)
			{
				return !(tm1 == tm2);
			}

			// eol definition 代表 “ End Of Line ”（行结束符）
#if !defined(SPDLOG_EOL)
	#ifdef _WIN32
		#define SPDLOG_EOL "\r\n"
	#else
		#define SPDLOG_EOL "\n"
	#endif
#endif
			SPDLOG_CONSTEXPR static const char* default_eol = SPDLOG_EOL;
		}
	}
}

