cmake_minimum_required(VERSION 3.8)
project(PL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_definitions(-O3)
#add_definitions(-Wall)

add_subdirectory(googletest)

include_directories(googletest/include)

link_directories(googletest)

set(LIBRARIES gtest pthread)

set(SOURCE_FILES main.cpp sources/scanner.cpp include/scanner.h sources/token.cpp include/token.h sources/dictionary.cpp include/dictionary.h sources/ast.cpp include/ast.h util/util.cpp util/util.h sources/parser.cpp include/parser.h sources/environment.cpp include/environment.h sources/value.cpp include/value.h sources/primitives/add.cpp include/primitives/add.h sources/primitives/minus.cpp include/primitives/minus.h sources/primitives/multiply.cpp include/primitives/multiply.h sources/primitives/divide.cpp include/primitives/divide.h util/error.cpp util/error.h test/unittest.cpp test/unittest.h sources/primitives/greater.cpp include/primitives/greater.h sources/primitives/less.cpp include/primitives/less.h include/primitives/primFun.h sources/interpreter.cpp include/interpreter.h sources/exception.cpp include/exception.h sources/GlobalScope.cpp include/GlobalScope.h)
add_executable(PL ${SOURCE_FILES} sources/scanner.cpp include/scanner.h sources/token.cpp include/token.h sources/dictionary.cpp include/dictionary.h sources/ast.cpp include/ast.h util/util.cpp util/util.h sources/parser.cpp include/parser.h sources/environment.cpp include/environment.h sources/value.cpp include/value.h sources/primitives/add.cpp include/primitives/add.h sources/primitives/minus.cpp include/primitives/minus.h sources/primitives/multiply.cpp include/primitives/multiply.h sources/primitives/divide.cpp include/primitives/divide.h util/error.cpp util/error.h test/unittest.cpp test/unittest.h sources/primitives/greater.cpp include/primitives/greater.h sources/primitives/less.cpp include/primitives/less.h include/primitives/primFun.h sources/interpreter.cpp include/interpreter.h sources/exception.cpp include/exception.h sources/GlobalScope.cpp include/GlobalScope.h)

target_link_libraries(PL ${LIBRARIES})
