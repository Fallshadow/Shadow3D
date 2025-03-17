#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {

	class HAZEL_API Application {
		public:
			Application();
			virtual ~Application();

			void Run();

			virtual void OnInit() { }
			virtual void OnShutdown() { }
			virtual void OnUpdate() { }

		private:

	};

	// 交给客户端实现
	Application* CreateApplication();
}