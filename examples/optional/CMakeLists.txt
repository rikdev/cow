cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

add_executable(optional
  main.cpp
)

find_package(COW REQUIRED)
target_link_libraries(optional PRIVATE COW::Optional)
