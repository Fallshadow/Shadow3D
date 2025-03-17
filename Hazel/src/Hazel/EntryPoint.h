#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {
    Hazel::Application* app = Hazel::CreateApplication();
    HZ_CORE_ASSERT(app, "Client Application is null!");
    app->Run();
    delete app;
}
#else
#error Hazel only supports Windows
#endif