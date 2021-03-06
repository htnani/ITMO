include(CheckCXXCompilerFlag)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${libpypa_SOURCE_DIR}/modules/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -pedantic -Wno-unused-parameter -Wno-unused-const-variable")

check_cxx_compiler_flag(-Wno-unused-local-typedefs CXX_NO_UNUSED_LOCAL_TYPEDEFS)
if(CXX_NO_UNUSED_LOCAL_TYPEDEFS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs")
endif()

set(CLANG_FLAGS "-Qunused-arguments -fcolor-diagnostics" CACHE STRING "Clang specific C and CXX flags")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_FLAGS}")
endif()

add_subdirectory(double-conversion)

add_library(pypa pypa/ast/ast.cc
                 pypa/ast/dump.cc
                 pypa/filebuf.cc
                 pypa/lexer/lexer.cc
                 pypa/parser/parser.cc
                 pypa/parser/make_string.cc
                 pypa/parser/symbol_table.cc)

# lexer_test
add_executable(lexer-test EXCLUDE_FROM_ALL pypa/parser/test.cc translator/translator.h translator/lib/ast_nodes/Sentence.h translator/lib/abstract_syntax_tree.h)

add_dependencies(lexer-test pypa)
target_link_libraries(lexer-test pypa gmp double-conversion)

# parser_test
add_executable(parser-test EXCLUDE_FROM_ALL pypa/parser/test.cc translator/translator.h translator)
add_dependencies(parser-test pypa)
target_link_libraries(parser-test pypa gmp double-conversion)

# install
install(TARGETS pypa ARCHIVE DESTINATION lib)
install(DIRECTORY pypa DESTINATION include FILES_MATCHING PATTERN "*.hh" PATTERN "*.inl")

# translation_results
add_executable(converted-test ../test/cpp_out/hello_world.cpp translator/lib/ast_nodes/CommentSentence.h translator/lib/ast_nodes/IncludeSentence.h translator/lib/ast_nodes/PrintSentence.h translator/translator.cpp translator/lib/ast_nodes/FunctionDefinitionSentence.h ../test/cpp_out/print_function.cpp translator/lib/ast_nodes/NameSpaceSentence.h)
