cmake_minimum_required(VERSION 3.12)
project(sorter)

find_package(cxxopts REQUIRED)
# cxxopts is a headers-only library so there is nothing to specify about linking

find_package(exiv2lib REQUIRED CONFIG NAMES exiv2)
link_libraries(exiv2lib)

add_subdirectory(app)
add_subdirectory(test)