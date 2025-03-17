#include "Hazel.h"

class Sandbox : public Hazel::Application {
    public:
        Sandbox() {
            HZ_TRACE("Hello!");
        }
};

Hazel::Application* Hazel::CreateApplication() {
    // return nullptr; 测试 app 断言
    return new Sandbox();
}