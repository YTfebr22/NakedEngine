cmake_minimum_required(VERSION 3.28)

project(nakedengine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CPM_VERSION 0.40.8)
set(CPM_PATH "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM_${CPM_VERSION}.cmake")

if(NOT EXISTS "${CPM_PATH}")
    file(
            DOWNLOAD
            "https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_VERSION}/CPM.cmake"
            "${CPM_PATH}"
            EXPECTED_HASH SHA256=78ba32abdf798bc616bab7c73aac32a17bbd7b06ad9e26a6add69de8f3ae4791
    )
endif()

include("${CPM_PATH}")

CPMAddPackage(
        NAME GLFW
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.4
        OPTIONS
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_DOCS OFF"
)

CPMAddPackage(
        NAME googletest
        GITHUB_REPOSITORY google/googletest
        VERSION 1.12.1
        GIT_TAG release-1.12.1
        OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

CPMAddPackage(
        NAME Vulkan-Headers
        GITHUB_REPOSITORY KhronosGroup/Vulkan-Headers
        GIT_TAG v1.3.269
)

if(Vulkan-Headers_ADDED)
    add_library(Vulkan-Module)
    target_sources(Vulkan-Module
            PUBLIC
            FILE_SET CXX_MODULES
            BASE_DIRS "${Vulkan-Headers_SOURCE_DIR}/include"
            FILES "${Vulkan-Headers_SOURCE_DIR}/include/vulkan/vulkan.cppm"
    )
    target_compile_features(Vulkan-Module PUBLIC cxx_std_20)
    target_link_libraries(Vulkan-Module PUBLIC Vulkan-Headers)
endif()

find_package(OpenGL REQUIRED)

add_library(glad STATIC lib/glad/src/glad.c)
target_include_directories(glad PUBLIC lib/glad/include)

file(GLOB_RECURSE NAKEDENGINE_CORE_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/nakedengine-core/src/*.cpp"
)

add_library(nakedengine-core STATIC ${NAKEDENGINE_CORE_SOURCES})
add_library(nakedengine::core ALIAS nakedengine-core)
target_include_directories(nakedengine-core PUBLIC lib/nakedengine-core/include)
target_link_libraries(nakedengine-core
        PUBLIC
        glad
        glfw
        OpenGL::GL
)

add_executable(nakedengine src/main.cpp)
target_link_libraries(nakedengine PRIVATE nakedengine::core)

enable_testing()

add_executable(nakedengine-tests tests/test.cpp)
target_link_libraries(nakedengine-tests
        PRIVATE
        nakedengine::core
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(nakedengine-tests)