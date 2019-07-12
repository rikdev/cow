cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# Declaring
project(COW
  VERSION 0.1.0
  DESCRIPTION "Set of libraries implementing copy-on-write technique"
  HOMEPAGE_URL "https://github.com/rikdev/cow"
  LANGUAGES CXX
)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(
    -Werror
    -pedantic
    -pedantic-errors
    -Wall
    -Wextra
    -Wnull-dereference
    -Wconversion
    -Wsign-conversion
  )
endif()

add_library(Optional INTERFACE)
add_library(${PROJECT_NAME}::Optional ALIAS Optional)

# Building
target_include_directories(Optional
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_sources(Optional
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cow/detail/compatibility/compile_features.h>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cow/detail/compatibility/utility.h>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cow/optional.h>
)
target_compile_features(Optional INTERFACE cxx_std_14)

# Testing
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Installing
include(GNUInstallDirs)
set(PROJECT_EXPORT_NAME ${PROJECT_NAME}Targets)
install(TARGETS Optional
  EXPORT ${PROJECT_EXPORT_NAME}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/ TYPE INCLUDE)

set(PROJECT_INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
install(EXPORT ${PROJECT_EXPORT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${PROJECT_INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  COMPATIBILITY SameMinorVersion
  ARCH_INDEPENDENT
)
install(FILES
  ${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${PROJECT_INSTALL_CONFIGDIR}
)

# Packaging
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
include(CPack)

# Tooling
option(ENABLE_TOOLING "Enable tooling support" ON)
if(ENABLE_TOOLING)
  add_subdirectory(tools)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Examples
option(BUILD_EXAMPLES "Build examples" OFF)
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
