#ifndef PHOTO_DATA_H
#define PHOTO_DATA_H

#include <filesystem>
#include <string>
#include <ctime>

class PhotoData {
public:
    PhotoData(const std::filesystem::path &) {}
    virtual std::string get_camera_model() = 0;
    virtual std::string get_timestamp_string() = 0;
    virtual std::time_t get_timestamp() = 0;
    virtual std::string get_target_subdirectory() = 0;
    virtual std::string get_target_filename() = 0;

private:
    std::string m_camera_model;
    std::string m_timestamp_string;
    std::time_t m_timestamp;
    std::string m_target_subdirectory;
    std::string m_target_filename;
};

#endif
