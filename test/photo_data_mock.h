#ifndef PHOTO_DATA_MOCK_H
#define PHOTO_DATA_MOCK_H

#include "../lib/photo_data.h"

#include <filesystem>
#include <string>
#include <ctime>

#include "gmock/gmock.h"


class PhotoDataMock : public PhotoData {
public:
    PhotoDataMock(const std::filesystem::path &path) : PhotoData(path) {}
    MOCK_METHOD(std::string,  get_camera_model, (), (override));
    MOCK_METHOD(std::string,  get_timestamp_string, (), (override));
    MOCK_METHOD(std::time_t, get_timestamp, (), (override));
    MOCK_METHOD(std::string, get_target_subdirectory, (), (override));
    MOCK_METHOD(std::string, get_target_filename, (), (override));
};

#endif
