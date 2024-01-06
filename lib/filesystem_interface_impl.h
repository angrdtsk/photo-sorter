#ifndef FILESYSTEM_INTERFACE_IMPL_H
#define FILESYSTEM_INTERFACE_IMPL_H

#include "filesystem_interface.h"

#include <filesystem>


class FilesystemInterfaceImpl : public FilesystemInterface {
public:
    FilesystemInterfaceImpl() = default;
    bool exists(const std::filesystem::path &path) { return std::filesystem::exists(path); }
    void create_directory(const std::filesystem::path &path) { std::filesystem::create_directory(path); }
    void copy(const std::filesystem::path &source, const std::filesystem::path &target) { std::filesystem::copy(source, target); }
};

#endif
