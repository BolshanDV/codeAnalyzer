cmake_minimum_required(VERSION 3.21)
project(codeAnalyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(codeAnalyzer main.cpp codeAnalyzer/Analyzer.cpp codeAnalyzer/Analyzer.h)
