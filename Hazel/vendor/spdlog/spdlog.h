// spdlog main header file.
// see example.cpp for usage example

#pragma once

#include <memory>
#include <string>

namespace spdlog {

	// 返回一个现有的日志记录器，如果不存在这样的日志记录器，则返回nullptr。
	// example: spdlog::get("my_logger")->info("hello {}", "world");
	std::shared_ptr<logger> get(const std::string& name);

	// 设置全局格式
	// example: spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %l : %v");
	void set_pattern(const std::string& format_string);
	void set_formatter(formatter_ptr f);

	// 设置全局日志级别
	void set_level(level::level_enum log_level);

}