cmake_minimum_required(VERSION 3.3)
project(untitled5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp HuffmanCode.cpp HuffmanCode.h HuffmanNode.cpp HuffmanNode.h VigenereAnalyser.cpp VigenereAnalyser.h)
add_executable(untitled5 ${SOURCE_FILES})