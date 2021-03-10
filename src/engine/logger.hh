#pragma once

#include <spdlog/spdlog.h>

namespace engine { namespace logger {

    std::shared_ptr<spdlog::logger> create_from_name(const std::string& name);

} }