cmake_minimum_required(VERSION 3.8)
project(LLanguage)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


add_subdirectory(googletest)

include_directories(googletest/include)

link_directories(googletest)

set(LIBRARIES
        gtest
        pthread)

set(SOURCE_FILES main.cpp sources/scanner.cpp include/scanner.h sources/token.cpp include/token.h sources/dictionary.cpp include/dictionary.h sources/ast.cpp sources/ast.h test/test.cpp test/test.h sources/parser.cpp include/parser.h sources/environment.cpp include/environment.h sources/value.cpp include/value.h util/util.cpp util/util.h primitives/add.cpp primitives/add.h primitives/minus.cpp primitives/minus.h primitives/multiply.cpp primitives/multiply.h primitives/divide.cpp primitives/divide.h util/error.cpp util/error.h test/unittest.cpp test/unittest.h primitives/greater.cpp primitives/greater.h primitives/less.cpp primitives/less.h primitives/primFun.h sources/interpreter.cpp include/interpreter.h)
add_executable(LLanguage ${SOURCE_FILES} sources/scanner.cpp include/scanner.h sources/token.cpp include/token.h sources/dictionary.cpp include/dictionary.h sources/ast.cpp sources/ast.h test/test.cpp test/test.h sources/parser.cpp include/parser.h sources/environment.cpp include/environment.h sources/value.cpp include/value.h util/util.cpp util/util.h primitives/add.cpp primitives/add.h primitives/minus.cpp primitives/minus.h primitives/multiply.cpp primitives/multiply.h primitives/divide.cpp primitives/divide.h util/error.cpp util/error.h test/unittest.cpp test/unittest.h primitives/greater.cpp primitives/greater.h primitives/less.cpp primitives/less.h primitives/primFun.h sources/interpreter.cpp include/interpreter.h)

target_link_libraries(LLanguage ${LIBRARIES})
