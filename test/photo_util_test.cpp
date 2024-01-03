#include <filesystem>

#include "../lib/photo_util.h"

#include "gtest/gtest.h"

namespace {

TEST(PhotoUtil, generate_directory_name) {
    ASSERT_STREQ(PhotoUtil::generate_directory_name("2023:07:22 16:20:27").c_str(), "2023-07-22");
    ASSERT_STREQ(PhotoUtil::generate_directory_name("2023:07:22").c_str(), "");
    ASSERT_STREQ(PhotoUtil::generate_directory_name("16:20:27").c_str(), "");
    ASSERT_STREQ(PhotoUtil::generate_directory_name("abc").c_str(), "");
    ASSERT_STREQ(PhotoUtil::generate_directory_name("").c_str(), "");
}

TEST(PhotoUtil, get_photo_number) {
    ASSERT_STREQ(PhotoUtil::get_photo_number("DSC05331.ARW").c_str(), "05331");
    ASSERT_STREQ(PhotoUtil::get_photo_number("DSC05331.JPG").c_str(), "05331");
    ASSERT_STREQ(PhotoUtil::get_photo_number("DSC_0971.JPG").c_str(), "0971");
    ASSERT_STREQ(PhotoUtil::get_photo_number("123").c_str(), "123");
    ASSERT_STREQ(PhotoUtil::get_photo_number("abc").c_str(), "");
    ASSERT_STREQ(PhotoUtil::get_photo_number("").c_str(), "");
}

TEST(PhotoUtil, get_camera_id) {
    ASSERT_STREQ(PhotoUtil::get_camera_id("DSC-RX100M3").c_str(), "RXC");
    ASSERT_STREQ(PhotoUtil::get_camera_id("H8324").c_str(), "XPA");
    ASSERT_STREQ(PhotoUtil::get_camera_id("abc").c_str(), "");
}

TEST(PhotoUtil, generate_filename)
{
    ASSERT_STREQ(PhotoUtil::generate_filename("DSC05331.JPG", std::filesystem::path("DSC05331.JPG").extension(), "DSC-RX100M3", "2023:07:22 16:20:27").c_str(), "162027-RXC-05331.JPG");
    ASSERT_STREQ(PhotoUtil::generate_filename("DSC05331.ARW", std::filesystem::path("DSC05331.ARW").extension(), "DSC-RX100M3", "2023:07:22 16:20:27").c_str(), "162027-RXC-05331.ARW");
    ASSERT_STREQ(PhotoUtil::generate_filename("DSC_0971.JPG", std::filesystem::path("DSC_0971.JPG").extension(), "H8324", "2023:07:22 16:20:27").c_str(), "162027-XPA-0971.JPG");
}

}
