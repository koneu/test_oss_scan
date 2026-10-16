add_library(app_core
    src/logger.cpp
    src/user_repository.cpp
)
target_include_directories(app_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(app_core PUBLIC spdlog::spdlog SQLiteCpp)
target_compile_options(app_core PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE app_core)

install(TARGETS app RUNTIME DESTINATION bin)
