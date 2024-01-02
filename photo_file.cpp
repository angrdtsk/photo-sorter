#include "photo_file.h"

#include <filesystem>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <ctime>

#include <exiv2/image.hpp>
#include <exiv2/error.hpp>

#include "photo_util.h"


PhotoFile::PhotoFile(const std::filesystem::path &source_file_path, const std::filesystem::path &target_directory_path)
{
    m_source_file_path = source_file_path;
    m_target_directory_path = target_directory_path;

    std::cout << "PhotoFile " << source_file_path << " " << target_directory_path << std::endl;

    std::unique_ptr<Exiv2::Image> image;
    try
    {
        image = Exiv2::ImageFactory::open(source_file_path);
    }
    catch(const Exiv2::Error &e)
    {
        std::string error_string = "Exiv2::ImageFactory::open failed: ";
        error_string += e.what();
        throw std::runtime_error(error_string);
    }

    try
    {
        image->readMetadata();
    }
    catch (const Exiv2::Error &e)
    {
        std::string error_string = "Exiv2::Image::readMetadata failed: ";
        error_string += e.what();
        throw std::runtime_error(error_string);
    }

    Exiv2::ExifData exif_data = image->exifData();
    m_camera_model = exif_data["Exif.Image.Model"].toString();
    if (m_camera_model == "")
    {
        throw std::runtime_error("Exif.Image.Model was empty");
    }
    m_timestamp_string = exif_data["Exif.Image.DateTime"].toString();
    if (m_timestamp_string == "")
    {
        throw std::runtime_error("Exif.Image.DateTime was empty");
    }

    m_target_subdirectory = PhotoUtil::generate_directory_name(m_timestamp_string);
    if (m_target_subdirectory == "")
    {
        throw std::runtime_error("Couldn't generate subdirectory name");
    }
    std::string source_file_basename(source_file_path.filename());
    std::string source_file_extension(source_file_path.extension());
    m_target_filename = PhotoUtil::generate_filename(source_file_basename, source_file_extension, m_camera_model, m_timestamp_string);
    if (m_target_filename == "")
    {
        throw std::runtime_error("Couldn't generate filename");
    }
}

void PhotoFile::copy_file()
{
    std::filesystem::path target_subdirectory_path;
    target_subdirectory_path = m_target_directory_path;
    target_subdirectory_path /= m_target_subdirectory;

    std::filesystem::path target_entry_path;
    target_entry_path = target_subdirectory_path;
    target_entry_path /= m_target_filename;

    std::cout << m_source_file_path << " > " << target_entry_path << std::endl;

    if (!std::filesystem::exists(target_subdirectory_path))
    {
        try
        {
            std::filesystem::create_directory(target_subdirectory_path);
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            throw std::runtime_error("Couldn't create directory");
        }
    }

    try
    {
        std::filesystem::copy(m_source_file_path, target_entry_path, std::filesystem::copy_options::recursive);
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        throw std::runtime_error("Couldn't copy file");
    }
}

bool PhotoFile::is_within_date_range(std::time_t &start, std::time_t &end)
{
    std::tm tm{};
    std::istringstream ss(m_timestamp_string);
    ss >> std::get_time(&tm, "%Y:%m:%d %H:%M:%S");
    std::time_t date = std::mktime(&tm);

    if (date == -1)
    {
        throw std::runtime_error("Couldn't parse date from Exif data");
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
