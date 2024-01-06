#include "gtest/gtest.h"

#include <memory>
#include <filesystem>

#include "../lib/photo_data.h"
#include "../lib/photo_file.h"
#include "../lib/filesystem_interface.h"
#include "photo_data_mock.h"
#include "filesystem_interface_mock.h"


TEST(PhotoFileTest, CanInstantiate) {
    std::filesystem::path source = "";
    std::filesystem::path target = "";
    // Use empty path i.e. non-existing photo and also use a mock for
    // FilesystemInterface to avoid errors because of empty path.
    std::shared_ptr<PhotoData> photo_data_mock = std::make_shared<PhotoDataMock>(std::filesystem::path(""));
    std::shared_ptr<FilesystemInterface> fs_if_mock = std::make_shared<FilesystemInterfaceMock>();
    PhotoFile photo_file(source, target, photo_data_mock, fs_if_mock);
}

TEST(PhotoFileTest, CanCallCopyFile) {
    std::filesystem::path source = "";
    std::filesystem::path target = "";
    // Use empty path i.e. non-existing photo and also use a mock for
    // FilesystemInterface to avoid errors because of empty path.
    std::shared_ptr<PhotoData> photo_data_mock = std::make_shared<PhotoDataMock>(std::filesystem::path(""));
    std::shared_ptr<FilesystemInterface> fs_if_mock = std::make_shared<FilesystemInterfaceMock>();
    PhotoDataMock *photo_data_mock_ptr = static_cast<PhotoDataMock*>(photo_data_mock.get());
    EXPECT_CALL(*photo_data_mock_ptr, get_target_subdirectory());
    EXPECT_CALL(*photo_data_mock_ptr, get_target_filename());
    FilesystemInterfaceMock *fs_if_mock_ptr =  static_cast<FilesystemInterfaceMock*>(fs_if_mock.get());
    EXPECT_CALL(*fs_if_mock_ptr, exists(testing::_));
    EXPECT_CALL(*fs_if_mock_ptr, create_directory(testing::_));
    EXPECT_CALL(*fs_if_mock_ptr, copy(testing::_, testing::_));
    PhotoFile photo_file(source, target, photo_data_mock, fs_if_mock);
    photo_file.copy_file();
}
