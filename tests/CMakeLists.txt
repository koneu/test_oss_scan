find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(app_tests
    user_repository_test.cpp
)
target_link_libraries(app_tests PRIVATE app_core GTest::gtest_main)

gtest_discover_tests(app_tests)
