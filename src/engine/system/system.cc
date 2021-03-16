#include "system.hh"

#include "engine/application.hh"

namespace engine {
    system::system(std::shared_ptr<spdlog::logger> logger) 
        : application(application::get())
    {
        this->logger = logger;
    }
}