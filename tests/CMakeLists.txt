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
  $<$<CXX_COMPILER_ID:Clang,AppleClang>:-Wdocumentation>
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:--coverage>
)
target_link_options(unit_tests
  PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:--coverage>
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

# tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## coverage
set(CTEST_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CTEST_BINARY_DIRECTORY "${CMAKE_BINARY_DIR}")
set(SOURCES_LIST_FILE "${CMAKE_CURRENT_BINARY_DIR}/CoverageSources.txt")

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(CTEST_COVERAGE_COMMAND "llvm-cov")
  set(CTEST_COVERAGE_EXTRA_FLAGS "gcov")
else()
  set(CTEST_COVERAGE_COMMAND "gcov")
  set(CTEST_COVERAGE_EXTRA_FLAGS)
endif()

get_target_property(
  OPTIONAL_LIBRARY_INTERFACE_SOURCES
  ${PROJECT_NAME}::Optional
  INTERFACE_SOURCES
)
file(GENERATE
  OUTPUT "${SOURCES_LIST_FILE}"
  CONTENT "$<JOIN:${OPTIONAL_LIBRARY_INTERFACE_SOURCES},\n>"
)
configure_file(cmake/coverage.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/coverage.cmake"
  @ONLY
)
