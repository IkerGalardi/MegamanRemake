#include "system.hh"

namespace engine {
    system::system(const engine::application& application_instance, std::shared_ptr<spdlog::logger> logger) 
        : application(application_instance)
    {
        this->logger = logger;
    }
}