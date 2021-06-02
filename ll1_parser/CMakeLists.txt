cmake_minimum_required(VERSION 3.20)

project(ll1_parser)

file(MAKE_DIRECTORY ../bin/)
set(EXECUTABLE_OUTPUT_PATH ../bin/)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PARSER ll1_parser.hpp)
set(ANALYZER ../lexical_analyzer.hpp)
set(MAIN main.cpp)

add_executable(ll1_parser ${MAIN} ${ANALYZER} ${PARSER})
