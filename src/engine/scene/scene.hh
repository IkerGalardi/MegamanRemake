#pragma once 

#include <functional>
#include <string>
#include <memory>

#include <entt/entt.hpp>
#include <spdlog/spdlog.h>

#include "engine/application.hh"

namespace engine {
    class scene {
        friend class application;
        friend class system;
    public:
        scene(const std::string& name, std::function<void(scene&)> func);
        ~scene() = default;

        entt::entity add_entity(const std::string& name);
        void remove_entity(entt::entity& entity);
        
        template<typename T>
        T& add_component(entt::entity& entity) {
            return registry.emplace<T>(entity);
        }

        template<typename T>
        void remove_component(entt::entity& entity) {
            registry.remove_if_exists<T>(entity);
        }
    private:
        void on_update();
        
        void bootstrap_scene();
        
        const entt::registry& get_registry() const;

        entt::registry registry;

        std::function<void(scene&)> bootstrap_function;

        std::shared_ptr<spdlog::logger> logger;

        std::string scene_name;
    protected:
    };
}