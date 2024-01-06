project(sorter-test)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(sorter-test
    ../lib/photo_util.cpp
    photo_util_test.cpp
    ../lib/photo_data_impl.cpp
    photo_data_test.cpp
    ../lib/photo_file.cpp
    photo_file_test.cpp
    )
target_link_libraries(sorter-test
    gtest_main
    gmock_main
    )

find_program(LCOV lcov REQUIRED)
find_program(GENHTML genhtml REQUIRED)
add_custom_target(test_coverage
    COMMAND ${LCOV} --directory . --capture --output-file coverage.info
    COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
    )