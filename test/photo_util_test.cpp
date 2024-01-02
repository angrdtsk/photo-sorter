#include "../lib/photo_util.h"

#include "gtest/gtest.h"

namespace {

TEST(PhotoUtil, get_camera_id) {
    ASSERT_STREQ(PhotoUtil::get_camera_id("DSC-RX100M3").c_str(), "RXC");
    ASSERT_STREQ(PhotoUtil::get_camera_id("H8324").c_str(), "XPA");
    ASSERT_STREQ(PhotoUtil::get_camera_id("abc").c_str(), "");
}

}