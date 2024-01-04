#include <filesystem>
#include <stdexcept>
#include <iostream>

#include "gtest/gtest.h"

#include "../lib/photo_data.h"
#include "../lib/rethrown_exception.h"
#include "../lib/local_exception.h"


namespace {

#if 0
TEST(PhotoData, ConstuctorWithProperFile) {
    bool exception_thrown = false;
    try
    {
        PhotoData photo_data(std::filesystem::path("../photos/DSC05331.JPG"));
    }
    catch (const RethrownException &e)
    {
        exception_thrown = true;
        std::cout << e.what() << std::endl;
    }
    ASSERT_FALSE(exception_thrown);
}

/*
*  It was assumed that a photo having no metadata would cause an exception
*  from exiv2, but it only causes metadata fields to be empty, and because
*  of that, the exception to catch here is LocalException instead of
*  RethrownException.
*/
TEST(PhotoData, ConstuctorWithPhotoFileWithNoMetadata) {
    bool exception_thrown = false;
    try
    {
        PhotoData photo_data(std::filesystem::path("../photos/DSC05331-nometadata.JPG"));
    }
    catch (const LocalException &e)
    {
        exception_thrown = true;
        std::cout << e.what() << std::endl;
    }
    ASSERT_TRUE(exception_thrown);
}

TEST(PhotoData, ConstuctorWithEmptyPath) {
    bool exception_thrown = false;
    try
    {
        PhotoData photo_data(std::filesystem::path(""));
    }
    catch (const RethrownException &e)
    {
        exception_thrown = true;
        std::cout << e.what() << std::endl;
    }
    ASSERT_TRUE(exception_thrown);
}

TEST(PhotoData, ConstuctorWithNonPhotoFile) {
    bool exception_thrown = false;
    try
    {
        PhotoData photo_data(std::filesystem::path("../photos/unknown.txt"));
    }
    catch (const RethrownException &e)
    {
        exception_thrown = true;
        std::cout << e.what() << std::endl;
    }
    ASSERT_TRUE(exception_thrown);
}
#endif

}
