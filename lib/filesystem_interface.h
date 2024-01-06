#ifndef FILESYSTEM_INTERFACE_H
#define FILESYSTEM_INTERFACE_H

#include <filesystem>


class FilesystemInterface {
public:
    FilesystemInterface() = default;
    virtual bool exists(const std::filesystem::path &path) = 0;
    virtual void create_directory(const std::filesystem::path &path) = 0;
    virtual void copy(const std::filesystem::path &source, const std::filesystem::path &target) = 0;
};

#endif
