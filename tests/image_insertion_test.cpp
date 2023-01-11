#include <gtest/gtest.h>
#include <image_path.h>
#include <filesystem>
#include <date/date.h>

using namespace std;

class ImageInsertionTest : public ::testing::Test
{
protected:
    std::filesystem::path current_working_directory = std::filesystem::current_path();
    std::filesystem::path test_files = current_working_directory / "test_files";
    std::filesystem::path actual_files = current_working_directory / "actual_files";
    const string image1 = "birch1.png";
    const string image2 = "birch2.png";
    std::filesystem::path birch_image1_path = test_files / image1;
    std::filesystem::path birch_image2_path = test_files / image2;
    std::string year = "2022";
    std::string month = "1";
    std::string day = "1";

    date::year_month_day date;

    ImageInsertionTest()
    {
        filesystem::remove_all(actual_files);
        filesystem::create_directory(actual_files);
    }

    void verifyFileExists(const string &tree_name, const string &expected_name)
    {
        auto file_path = actual_files / tree_name / expected_name;
        ASSERT_TRUE(filesystem::exists(file_path));
    }
};

TEST_F(ImageInsertionTest, test_image_that_does_not_exist)
{
    ASSERT_THROW(insert_image("birch1", test_files / "image_that_does_not_exist.png", actual_files, year, month, day),
                 filesystem::__cxx11::filesystem_error);
}

TEST_F(ImageInsertionTest, test_should_not_copy_text_files)
{
    ASSERT_THROW(
        insert_image("birch1", test_files / "text.txt", actual_files, year, month, day),
        WrongFileTypeException);
}

TEST_F(ImageInsertionTest, test_should_copy_png_files)
{
    const string tree_name = "birch1";

    const bool copySuccessful = insert_image(tree_name, birch_image1_path, actual_files, year, month, day);
    ASSERT_TRUE(copySuccessful);
    verifyFileExists(tree_name, image1);
}

TEST_F(ImageInsertionTest, test_copy_two_png_files_to_same_folder)
{
    const string tree_name = "birch1";

    ASSERT_TRUE(insert_image(tree_name, birch_image1_path, actual_files, year, month, day));
    ASSERT_TRUE(insert_image(tree_name, birch_image2_path, actual_files, year, month, day));

    verifyFileExists(tree_name, image1);
    verifyFileExists(tree_name, image2);
}

TEST_F(ImageInsertionTest, test_copy_two_png_files_to_different_folder)
{
    const string tree_name1 = "birch1";
    const string tree_name2 = "birch2";

    ASSERT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, year, month, day));
    ASSERT_TRUE(insert_image(tree_name2, birch_image2_path, actual_files, year, month, day));

    verifyFileExists(tree_name1, image1);
    verifyFileExists(tree_name2, image2);
}

TEST_F(ImageInsertionTest, test_copy_same_png_files_to_same_folder)
{
    const string tree_name1 = "birch1";

    ASSERT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, year, month, day));
    ASSERT_THROW(insert_image(tree_name1, birch_image1_path, actual_files, year, month, day),
                 filesystem::filesystem_error);

    verifyFileExists(tree_name1, image1);
}

TEST(ConvertStringToDateTest, normalInput)
{
    auto date = convert_string_to_date("2022", "5", "23");

    EXPECT_EQ(date.day(), date::day(23));
    EXPECT_EQ(date.month(), date::month(5));
    EXPECT_EQ(date.year(), date::year(2022));
}

TEST(ConvertStringToDateTest, dateThatDoesNotExist)
{
    ASSERT_THROW(convert_string_to_date("2022", "5", "35"),
                 InvalidDateException);
    ASSERT_THROW(convert_string_to_date("2000", "0", "5"),
                 InvalidDateException);
    ASSERT_THROW(convert_string_to_date("2022", "-5", "20"),
                 InvalidDateException);
    ASSERT_THROW(convert_string_to_date("2022", "5", "-10"),
                 InvalidDateException);
    ASSERT_THROW(convert_string_to_date("2022", "14", "8"),
                 InvalidDateException);
}