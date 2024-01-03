#include "photo_util.h"

#include <string>
#include <sstream>
#include <regex>
#include <iomanip>
#include <ctime>


std::string PhotoUtil::generate_directory_name(const std::string &exif_timestamp)
{
    // Validate the format on the input string. This is to work-around the
    // observation that get_time() doesn't in anyway indicate whether the input
    // string matches the format exactly. In practice, it accepts a date-only
    // string, parsing it correctly, and a time-only string, apparently
    // interpretting it as a date-only string.
    std::regex regexp("[0-9]{4}:[0-9]{2}:[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}");
    std::smatch match;
    std::regex_search(exif_timestamp, match, regexp);
    if (match.size() != 1)
    {
        return "";
    }

    struct std::tm tm;
    std::istringstream ss(exif_timestamp);
    ss >> std::get_time(&tm, "%Y:%m:%d %H:%M:%S");

    std::ostringstream output;
    output << std::put_time(&tm, "%Y-%m-%d");

    return std::string(output.str());
}

std::string PhotoUtil::get_photo_number(const std::string &filename)
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

std::string PhotoUtil::get_camera_id(const std::string &camera_model)
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

std::string PhotoUtil::generate_filename(const std::string &original_basename, const std::string &extension, const std::string &camera_model, const std::string &exif_timestamp)
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
