#pragma once

#include <memory>
#include <string>

#include <spdlog/spdlog.h>

namespace app {

// Creates (or returns the already existing) application logger.
std::shared_ptr<spdlog::logger> init_logger(const std::string& name = "app",
                                            spdlog::level::level_enum level = spdlog::level::info);

}  // namespace app
