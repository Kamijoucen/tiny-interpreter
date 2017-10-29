cmake_minimum_required(VERSION 3.8)
project(LLanguage)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_subdirectory(./googletest)

include_directories(./googletest/include)

link_directories(./googletest)

set(LIBRARIES
        gtest
        pthread)

set(SOURCE_FILES test/main.cpp scanner.cpp scanner.h token.cpp token.h dictionary.cpp dictionary.h ast.cpp ast.h test/test.cpp test/test.h parser.cpp parser.h environment.cpp environment.h value.cpp value.h util/util.cpp util/util.h primitives/add.cpp primitives/add.h primitives/minus.cpp primitives/minus.h primitives/multiply.cpp primitives/multiply.h primitives/divide.cpp primitives/divide.h util/error.cpp util/error.h test/unittest.cpp test/unittest.h primitives/greater.cpp primitives/greater.h primitives/less.cpp primitives/less.h primitives/util.cpp primitives/util.h)
add_executable(LLanguage ${SOURCE_FILES} scanner.cpp scanner.h token.cpp token.h dictionary.cpp dictionary.h ast.cpp ast.h test/test.cpp test/test.h parser.cpp parser.h environment.cpp environment.h value.cpp value.h util/util.cpp util/util.h primitives/add.cpp primitives/add.h primitives/minus.cpp primitives/minus.h primitives/multiply.cpp primitives/multiply.h primitives/divide.cpp primitives/divide.h util/error.cpp util/error.h test/unittest.cpp test/unittest.h primitives/greater.cpp primitives/greater.h primitives/less.cpp primitives/less.h primitives/util.cpp primitives/util.h)

target_link_libraries(LLanguage ${LIBRARIES})
