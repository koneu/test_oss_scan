from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class TestOssScanConan(ConanFile):
    name = "test_oss_scan"
    version = "0.1.0"
    license = "MIT"
    author = "KoNeu"
    url = "https://github.com/KoNeu/test_oss_scan"
    description = "Small C++ sample project used to try out ORT OSS scanning"
    topics = ("ort", "oss", "sample")

    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt", "app/*", "tests/*", "LICENSE"

    def requirements(self):
        self.requires("spdlog/1.14.1")
        self.requires("sqlitecpp/3.3.2")

    def build_requirements(self):
        self.test_requires("gtest/1.15.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        CMakeDeps(self).generate()
        CMakeToolchain(self).generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake.test()
