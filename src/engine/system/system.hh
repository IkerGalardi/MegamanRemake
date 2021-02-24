#pragma once

namespace engine {
    class application;

    class system {
    public:
        system(const engine::application& app_instance);
        virtual ~system() = default;

        virtual void on_init() {}
        virtual void on_update() {}
        virtual void on_destroy() {}
    private:
    protected:
        const engine::application& application;
    };
}