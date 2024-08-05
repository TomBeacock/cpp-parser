cmake_minimum_required(VERSION 3.14)

project(cpp-parser)

include(FetchContent)

FetchContent_Declare(
	cpp-types
	GIT_REPOSITORY https://github.com/TomBeacock/cpp-types.git
	GIT_TAG origin/main
)

FetchContent_MakeAvailable(cpp-types)

add_library(cpp-parser STATIC "include/parser/parser.h" "src/parser.cpp")

set_target_properties(cpp-parser PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_include_directories(cpp-parser PUBLIC "include")
target_link_libraries(cpp-parser PUBLIC cpp-types)