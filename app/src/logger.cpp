#include "app/logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace app {

std::shared_ptr<spdlog::logger> init_logger(const std::string& name, spdlog::level::level_enum level) {
    auto logger = spdlog::get(name);
    if (!logger) {
        logger = spdlog::stdout_color_mt(name);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
    }
    logger->set_level(level);
    return logger;
}

}  // namespace app
