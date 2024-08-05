cmake_minimum_required(VERSION 3.14)

project(cpp-parser)

include(FetchContent)

FetchContent_Declare(
	cpp-types
	GIT_REPOSITORY https://github.com/TomBeacock/cpp-types.git
	GIT_TAG origin/main
)

FetchContent_MakeAvailable(cpp-types)

add_library(cpp-parser INTERFACE)

target_include_directories(cpp-parser INTERFACE "include")
target_link_libraries(cpp-parser INTERFACE cpp-types)
target_compile_features(cpp-parser INTERFACE cxx_std_20)