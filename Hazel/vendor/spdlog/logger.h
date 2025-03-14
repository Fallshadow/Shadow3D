#pragma once

// 线程安全 logger （除了 set_pattern(..), set_formatter(..) and set_error_handler() ）
// 具有名称、日志等级、共享 sink 指针和格式化的向量。
// 1: 检查其日志级别是否足以记录该消息
// 2: 使用formatter函数格式化消息
// 3: 将格式化的消息传递给它的接收器以执行实际的日志记录

#include "common.h"

namespace spdlog {

	class logger {
	public:
		logger(const std::string &name, )

	};
}