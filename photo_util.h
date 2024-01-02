#ifndef PHOTO_UTIL_H
#define PHOTO_UTIL_H

#include <string>

class PhotoUtil {
public:
    static std::string generate_directory_name(const std::string &);
    static std::string get_photo_number(const std::string &);
    static std::string get_camera_id(const std::string &);
    static std::string generate_filename(const std::string &, const std::string &, const std::string &, const std::string &);
};

#endif
