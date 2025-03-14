#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {

	class HAZEL_API Application {
		public:
			Application();
			virtual ~Application();

			void Run();
		private:

	};

	// 交给客户端实现
	Application* CreateApplication();
}