#include <iostream>
#include <gtest/gtest.h>
#include <image_insertion.h>
#include <filesystem>

using namespace std;

class ImageInsertionTest : public ::testing::Test {
protected:
    std::filesystem::path current_working_directory = std::filesystem::current_path();
    std::filesystem::path test_files = current_working_directory / "test_files";
    std::filesystem::path actual_files = current_working_directory / "actual_files";

    void SetUp() override {
        filesystem::remove_all(actual_files);
        cout << current_working_directory << "\n";
        filesystem::create_directory(actual_files);
        filesystem::copy(test_files, actual_files, filesystem::copy_options::recursive);
    }

    void assertDirectoriesEqual(){
        vector<filesystem::directory_entry> files{};
        for (auto it : filesystem::recursive_directory_iterator{test_files})
        {
            files.push_back(it);
        }
    }

    void TearDown() override {
        assertDirectoriesEqual();
        filesystem::remove_all(actual_files);
    }
};


TEST_F(ImageInsertionTest, test_image_that_does_not_exist) {
    ASSERT_THROW(insert_image("birch1", test_files / "image_that_does_not_exist.png", test_files / "birch1"),
                 filesystem::__cxx11::filesystem_error);
}

TEST_F(ImageInsertionTest, test_should_not_copy_text_files) {
    ASSERT_THROW(
            insert_image("birch1", test_files / "text.txt", test_files),
            WrongFileTypeException);
}


