option(FETCH_DEPENDENCIES "Download and install dependencies" OFF)
if(FETCH_DEPENDENCIES)
  include(FetchDependencies.cmake)
else()
  find_package(Catch2 REQUIRED)
endif()

add_executable(unit_tests
  # public api tests
  optional_test.cpp
  # function main
  main.cpp
)
target_compile_options(unit_tests
  PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Wdocumentation>
)

add_library(unit_test_tools STATIC
  tools/relation_only.h
  tools/tracker.cpp
  tools/tracker.h
)

target_link_libraries(unit_tests
  PRIVATE
  ${PROJECT_NAME}::Optional
  unit_test_tools
  Catch2::Catch2
)

add_test(NAME unit_tests COMMAND unit_tests)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
