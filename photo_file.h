#ifndef PHOTO_FILE_H
#define PHOTO_FILE_H

#include <filesystem>
#include <string>

class PhotoFile {
public:
    PhotoFile(const std::filesystem::path &, const std::filesystem::path &);
    void copy_file();
    bool is_within_date_range(std::time_t &, std::time_t &);
    static bool is_photo_file(const std::string &);

private:
    std::filesystem::path m_source_file_path;
    std::filesystem::path m_target_directory_path;
    std::string m_camera_model;
    std::string m_timestamp_string;
    std::time_t m_timestamp;
    std::string m_target_subdirectory;
    std::string m_target_filename;
};

#endif