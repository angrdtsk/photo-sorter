#ifndef PHOTO_FILE_H
#define PHOTO_FILE_H

#include <filesystem>
#include <string>

#include "photo_data.h"

class PhotoFile {
public:
    PhotoFile(const std::filesystem::path &, const std::filesystem::path &);
    void copy_file();
    bool is_within_date_range(std::time_t &, std::time_t &);
    static bool is_photo_file(const std::string &);

private:
    std::filesystem::path m_source_file_path;
    std::filesystem::path m_target_directory_path;
    std::unique_ptr<PhotoData> m_photo_data;
};

#endif