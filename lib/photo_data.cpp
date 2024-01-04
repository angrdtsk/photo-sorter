#include "photo_data.h"

#include <string>
#include <ctime>

#include <exiv2/image.hpp>
#include <exiv2/error.hpp>

#include "photo_util.h"
#include "rethrown_exception.h"
#include "local_exception.h"


PhotoData::PhotoData(const std::filesystem::path &path)
{
    std::unique_ptr<Exiv2::Image> image;
    try
    {
        image = Exiv2::ImageFactory::open(path);
    }
    catch(const Exiv2::Error &e)
    {
        std::string error_string = "Exiv2::ImageFactory::open failed: ";
        error_string += e.what();
        throw RethrownException(error_string);
    }

    try
    {
        image->readMetadata();
    }
    catch (const Exiv2::Error &e)
    {
        std::string error_string = "Exiv2::Image::readMetadata failed: ";
        error_string += e.what();
        throw RethrownException(error_string);
    }

    Exiv2::ExifData exif_data = image->exifData();
    m_camera_model = exif_data["Exif.Image.Model"].toString();
    if (m_camera_model == "")
    {
        throw LocalException("Exif.Image.Model was empty");
    }
    m_timestamp_string = exif_data["Exif.Image.DateTime"].toString();
    if (m_timestamp_string == "")
    {
        throw LocalException("Exif.Image.DateTime was empty");
    }

    m_target_subdirectory = PhotoUtil::generate_directory_name(m_timestamp_string);
    if (m_target_subdirectory == "")
    {
        throw LocalException("Couldn't generate subdirectory name");
    }
    std::string source_file_basename(path.filename());
    std::string source_file_extension(path.extension());
    m_target_filename = PhotoUtil::generate_filename(source_file_basename, source_file_extension, m_camera_model, m_timestamp_string);
    if (m_target_filename == "")
    {
        throw LocalException("Couldn't generate filename");
    }
}

std::string PhotoData::get_camera_model()
{
    return std::string(m_camera_model);
}

std::string PhotoData::get_timestamp_string()
{
    return std::string(m_timestamp_string);
}

std::time_t PhotoData::get_timestamp()
{
    return m_timestamp;
}

std::string PhotoData::get_target_subdirectory()
{
    return std::string(m_target_subdirectory);
}

std::string PhotoData::get_target_filename()
{
    return std::string(m_target_filename);
}
