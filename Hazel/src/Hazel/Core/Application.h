#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/Window.h"

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
			std::unique_ptr<Window> m_Window;
	};

	// 交给客户端实现
	Application* CreateApplication();
}