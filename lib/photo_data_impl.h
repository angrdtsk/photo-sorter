#ifndef PHOTO_DATA_IMPL_H
#define PHOTO_DATA_IMPL_H

#include "photo_data_impl.h"

#include <filesystem>
#include <string>
#include <ctime>

#include "photo_data.h"

class PhotoDataImpl : public PhotoData {
public:
    PhotoDataImpl(const std::filesystem::path &);
    virtual std::string get_camera_model();
    virtual std::string get_timestamp_string();
    virtual std::time_t get_timestamp();
    virtual std::string get_target_subdirectory();
    virtual std::string get_target_filename();

private:
    std::string m_camera_model;
    std::string m_timestamp_string;
    std::time_t m_timestamp;
    std::string m_target_subdirectory;
    std::string m_target_filename;
};

#endif
