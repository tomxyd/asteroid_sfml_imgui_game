cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME default)
project("${PROJECT_NAME}" VERSION 1.0)

include(FetchContent)

# --- SFML ---
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
    GIT_SHALLOW ON
)

# --- ImGui ---
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.9   # pick a stable version
)

# --- ImGui-SFML ---
FetchContent_Declare(imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG 2.6.x
)

# SFML
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)

FetchContent_MakeAvailable(imgui-sfml)
# --- Executable ---
add_executable("${PROJECT_NAME}")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
target_sources("${PROJECT_NAME}" PRIVATE ${MY_SOURCES})

if(PRODUCTION_BUILD)
    target_compile_definitions("${PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")
    target_compile_definitions("${PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1 DEVELOPMENT_BUILD=0)
else()
    target_compile_definitions("${PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions("${PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0 DEVELOPMENT_BUILD=1)
endif()

target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_17)

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${PROJECT_SOURCE_DIR}/include")


# Link against SFML + ImGui-SFML
target_link_libraries("${PROJECT_NAME}" PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML)
