#ifndef FILESYSTEM_INTERFACE_MOCK_H
#define FILESYSTEM_INTERFACE_MOCK_H

#include "../lib/filesystem_interface.h"

#include <filesystem>

#include "gmock/gmock.h"

//    virtual bool exists(const std::filesystem::path &path) = 0;
//    virtual void create_directory(const std::filesystem::path &path) = 0;
//    virtual void copy(const std::filesystem::path &source, const std::filesystem::path &target) = 0;

class FilesystemInterfaceMock : public FilesystemInterface {
public:
    MOCK_METHOD(bool, exists, (const std::filesystem::path &), (override));
    MOCK_METHOD(void, create_directory, (const std::filesystem::path &), (override));
    MOCK_METHOD(void, copy, (const std::filesystem::path &, const std::filesystem::path &), (override));
};

#endif
