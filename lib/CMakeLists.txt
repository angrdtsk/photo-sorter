cmake_minimum_required(VERSION 3.12)
project(sorter)

add_library(sorter-lib STATIC photo_file.cpp photo_util.cpp)
