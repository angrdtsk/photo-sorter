project(sorter-test)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(sorter-test photo_util_test.cpp)
target_link_libraries(sorter-test gtest_main sorter-lib)
