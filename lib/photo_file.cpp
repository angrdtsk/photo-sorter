#include "photo_file.h"

#include <filesystem>
#include <memory>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <ctime>

#include "photo_data.h"
#include "photo_util.h"
#include "rethrown_exception.h"
#include "local_exception.h"


PhotoFile::PhotoFile(const std::filesystem::path &source_file_path, const std::filesystem::path &target_directory_path, const std::shared_ptr<FilesystemInterface> &fs_if)
{
    m_source_file_path = source_file_path;
    m_target_directory_path = target_directory_path;
    m_fs_if = fs_if;

    m_photo_data = std::make_unique<PhotoData>(source_file_path);
}

void PhotoFile::copy_file()
{
    std::filesystem::path target_subdirectory_path;
    target_subdirectory_path = m_target_directory_path;
    target_subdirectory_path /= m_photo_data->get_target_subdirectory();

    std::filesystem::path target_entry_path;
    target_entry_path = target_subdirectory_path;
    target_entry_path /= m_photo_data->get_target_filename();

    std::cout << m_source_file_path << " > " << target_entry_path << std::endl;

    if (!m_fs_if->exists(target_subdirectory_path))
    {
        try
        {
            m_fs_if->create_directory(target_subdirectory_path);
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            throw RethrownException("Couldn't create directory");
        }
    }

    try
    {
        m_fs_if->copy(m_source_file_path, target_entry_path);
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        throw RethrownException("Couldn't copy file");
    }
}

bool PhotoFile::is_within_date_range(std::time_t &start, std::time_t &end)
{
    std::tm tm{};
    std::istringstream ss(m_photo_data->get_timestamp_string());
    ss >> std::get_time(&tm, "%Y:%m:%d %H:%M:%S");
    std::time_t date = std::mktime(&tm);

    if (date == -1)
    {
        throw LocalException("Couldn't parse date from Exif data");
    }

    if ((date >= start) && (date <= end))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PhotoFile::is_photo_file(const std::string &extension_to_check)
{
    std::vector<std::string> extensions = {".jpg", ".JPG", ".arw", ".ARW"};
    if (std::any_of(extensions.begin(), extensions.end(), [extension_to_check] (std::string extension) { return extension_to_check == extension; }))
    {
        return true;
    } else {
        return false;
    }
}
