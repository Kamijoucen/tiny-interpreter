cmake_minimum_required(VERSION 3.8)
project(LLanguage)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp scanner.cpp scanner.h token.cpp token.h dictionary.cpp dictionary.h ast.cpp ast.h)
add_executable(LLanguage ${SOURCE_FILES} scanner.cpp scanner.h token.cpp token.h dictionary.cpp dictionary.h ast.cpp ast.h)