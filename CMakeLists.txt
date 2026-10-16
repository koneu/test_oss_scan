cmake_minimum_required(VERSION 3.23)

project(test_oss_scan
    VERSION 0.1.0
    DESCRIPTION "Sample project for ORT OSS scanning"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(APP_BUILD_TESTS "Build unit tests" ON)

find_package(spdlog REQUIRED)
find_package(SQLiteCpp REQUIRED)

add_subdirectory(app)

if(APP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
