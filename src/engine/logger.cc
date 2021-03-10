#include "logger.hh"

#include <iostream>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace engine { namespace logger {


    std::shared_ptr<spdlog::logger> create_from_name(const std::string& name) {
        // Setup sinks (for now only console printing)
        std::vector<spdlog::sink_ptr> sinks;
        sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

        auto logger = std::make_shared<spdlog::logger>(name, std::begin(sinks), std::end(sinks));

        // Set the printing format to: [lname](type): message
        logger->set_pattern("%^[%n](%l): %v%$");
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        
        spdlog::register_logger(logger);

        return logger;
    }
} }