cmake_minimum_required(VERSION 3.8)
project(LLanguage)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(SOURCE_FILES test/main.cpp scanner.cpp scanner.h token.cpp token.h dictionary.cpp dictionary.h ast.cpp ast.h test/test.cpp test/test.h parser.cpp parser.h environment.cpp environment.h value.cpp value.h util/util.cpp util/util.h primitives/add.cpp primitives/add.h primitives/minus.cpp primitives/minus.h)
add_executable(LLanguage ${SOURCE_FILES} scanner.cpp scanner.h token.cpp token.h dictionary.cpp dictionary.h ast.cpp ast.h test/test.cpp test/test.h parser.cpp parser.h environment.cpp environment.h value.cpp value.h util/util.cpp util/util.h primitives/add.cpp primitives/add.h primitives/minus.cpp primitives/minus.h)