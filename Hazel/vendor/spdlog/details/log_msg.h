#pragma once

#include "../common.h"
#include <string>

namespace spdlog {
	namespace details {
		struct log_msg
		{
			log_msg() = default;
			log_msg(const std::string* loggers_name, level::level_enum lvl) : loggers_name(loggers_name), level(lvl) {
#ifndef SPDLOG_NO_DATETIME
				time = os::now();
#endif // !SPDLOG_NO_DATETIME
#ifndef SPDLOG_NO_THREAD_ID
				thread_id = os::thread_id();
#endif // !SPDLOG_NO_THREAD_ID

			}
		};
	}

}