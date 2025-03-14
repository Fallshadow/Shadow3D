#pragma once

namespace spdlog {
	namespace sinks {
		class sink {
		public:
			virtual ~sink() = default;

			virtual void log(const details::log_msg& msg) = 0;
			virtual void flush() = 0;

			bool should_log(level::level_enum msg_level) const;
			void set_level(level::level_enum log_level);
			level::level_enum level() const;

		private:
			level_t _level{ level::trace };

		};

	}
}