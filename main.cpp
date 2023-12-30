#include <string>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <regex>
#include <algorithm>

#include <exiv2/image.hpp>
#include <exiv2/error.hpp>


bool is_photo_file(const std::string &extension_to_check)
{
    std::vector<std::string> extensions = {".jpg", ".JPG", ".arw", ".ARW"};
    if (std::any_of(extensions.begin(), extensions.end(), [extension_to_check] (std::string extension) { return extension_to_check == extension; }))
    {
        return true;
    } else {
        return false;
    }
}

std::string generate_directory_name(const std::string &exif_timestamp)
{
    struct std::tm tm;
    std::istringstream ss(exif_timestamp);
    ss >> std::get_time(&tm, "%Y:%m:%d %H:%M:%S");

    std::ostringstream output;
    output << std::put_time(&tm, "%Y-%m-%d");

    return std::string(output.str());
}

std::string get_photo_number(const std::string &filename)
{
    std::regex regexp("[0-9]{1,}");
    std::smatch match;
    std::regex_search(filename, match, regexp);
    if (match.size() == 1)
    {
        return std::string(match[0]);
    }
    else
    {
        return "";
    }
}

std::string get_camera_id(const std::string &camera_model)
{
    if (camera_model == "DSC-RX100M3")
    {
        return std::string("RXC");
    }
    else if (camera_model == "H8324")
    {
        return std::string("XPA");
    }
    else
    {
        return "";
    }
}

std::string generate_filename(const std::string &original_basename, const std::string &extension, const std::string &camera_model, const std::string &exif_timestamp)
{
    struct std::tm tm;
    std::istringstream ss(exif_timestamp);
    ss >> std::get_time(&tm, "%Y:%m:%d %H:%M:%S");

    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm, "%H%M%S");
    std::string timestamp = timestamp_stream.str();

    std::string photo_number = get_photo_number(original_basename);
    if (photo_number == "")
    {
        return "";
    }
    std::string camera_id = get_camera_id(camera_model);
    if (camera_id == "")
    {
        return "";
    }

    std::ostringstream filename_stream;
    filename_stream << timestamp << "-" << camera_id << "-" << photo_number << extension;

    return filename_stream.str();
}

void copy_file(std::filesystem::path &source_file_path, const std::filesystem::path &target_directory_path)
{
    std::string source_file_basename(source_file_path.filename());
    std::string source_file_extension(source_file_path.extension());

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
    std::string camera_model(exif_data["Exif.Image.Model"].toString());
    if (camera_model == "")
    {
        throw std::runtime_error("Exif.Image.Model was empty");
    }
    std::string exif_timestamp(exif_data["Exif.Image.DateTime"].toString());
    if (exif_timestamp == "")
    {
        throw std::runtime_error("Exif.Image.DateTime was empty");
    }

    std::string target_subdirectory = generate_directory_name(exif_timestamp);
    if (target_subdirectory == "")
    {
        throw std::runtime_error("Couldn't generate subdirectory name");
    }
    std::string target_filename = generate_filename(source_file_basename, source_file_extension, camera_model, exif_timestamp);
    if (target_filename == "")
    {
        throw std::runtime_error("Couldn't generate filename");
    }

    std::filesystem::path target_subdirectory_path;
    target_subdirectory_path = target_directory_path;
    target_subdirectory_path /= target_subdirectory;

    std::filesystem::path target_entry_path;
    target_entry_path = target_subdirectory_path;
    target_entry_path /= target_filename;

    std::cout << source_file_path << " > " << target_entry_path << std::endl;

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
        std::filesystem::copy(source_file_path, target_entry_path, std::filesystem::copy_options::recursive);
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        throw std::runtime_error("Couldn't copy file");
    }
}

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        std::cout << "Two paths required" << std::endl;
        return 0;
    }

    if (!std::filesystem::exists(argv[1]))
    {
        std::cout << "Source directory given doesn't exist" << std::endl;
        return 0;
    }

    if (!std::filesystem::exists(argv[2]))
    {
        std::cout << "Target directory given doesn't exist" << std::endl;
        return 0;
    }

    const std::filesystem::path source_directory_path = argv[1];
    const std::filesystem::path target_directory_path = argv[2];

    for (const auto &source_entry_it : std::filesystem::recursive_directory_iterator(source_directory_path))
    {
        std::filesystem::path source_entry_path = source_entry_it.path();
 
        std::string source_entry_extension = source_entry_path.extension();

        if (is_photo_file(source_entry_extension))
        {
            std::cout << "photo" << std::endl;
            try
            {
                copy_file(source_entry_path, target_directory_path);
            }
            catch (const std::exception &e)
            {
                std::cout << std::string(e.what()) << std::endl;
            }
        }
        else
        {
            std::cout << "unknown" << std::endl;
        }
    }
}
