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

    date::year_month_day date{date::year(2022), date::month(10), date::day(3)};

    ImageInsertionTest()
    {
        filesystem::remove_all(actual_files);
        filesystem::create_directory(actual_files);
    }

    ~ImageInsertionTest()
    {
        filesystem::remove_all(actual_files);
    }

    void verifyFileExists(const string &tree_name, const string &expected_name)
    {
        auto file_path = actual_files / tree_name / expected_name;
        EXPECT_TRUE(filesystem::exists(file_path));
    }
};

TEST_F(ImageInsertionTest, test_image_that_does_not_exist)
{
    EXPECT_THROW(insert_image("birch1", test_files / "image_that_does_not_exist.png", actual_files, date),
                 filesystem::__cxx11::filesystem_error);
}

TEST_F(ImageInsertionTest, test_should_not_copy_text_files)
{
    EXPECT_THROW(
        insert_image("birch1", test_files / "text.txt", actual_files, date),
        WrongFileTypeException);
}

TEST_F(ImageInsertionTest, test_should_copy_png_files)
{
    const string tree_name = "birch1";

    const bool copySuccessful = insert_image(tree_name, birch_image1_path, actual_files, date);
    EXPECT_TRUE(copySuccessful);
    verifyFileExists(tree_name, "2022-10-03.png");
}

TEST_F(ImageInsertionTest, test_copy_two_png_files_to_same_folder)
{
    const string tree_name = "birch1";

    EXPECT_TRUE(insert_image(tree_name, birch_image1_path, actual_files, date));
    EXPECT_TRUE(insert_image(tree_name, birch_image2_path, actual_files, date));

    verifyFileExists(tree_name, image1);
    verifyFileExists(tree_name, image2);
}

TEST_F(ImageInsertionTest, test_copy_two_png_files_to_different_folder)
{
    const string tree_name1 = "birch1";
    const string tree_name2 = "birch2";

    EXPECT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, date));
    EXPECT_TRUE(insert_image(tree_name2, birch_image2_path, actual_files, date));

    verifyFileExists(tree_name1, image1);
    verifyFileExists(tree_name2, image2);
}

TEST_F(ImageInsertionTest, test_copy_same_png_files_to_same_folder)
{
    const string tree_name1 = "birch1";

    EXPECT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, date));
    EXPECT_THROW(insert_image(tree_name1, birch_image1_path, actual_files, date),
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
    EXPECT_THROW(convert_string_to_date("2022", "5", "35"),
                 InvalidDateException);
    EXPECT_THROW(convert_string_to_date("2000", "0", "5"),
                 InvalidDateException);
    EXPECT_THROW(convert_string_to_date("2022", "-5", "20"),
                 InvalidDateException);
    EXPECT_THROW(convert_string_to_date("2022", "5", "-10"),
                 InvalidDateException);
    EXPECT_THROW(convert_string_to_date("2022", "14", "8"),
                 InvalidDateException);
}

TEST(ConvertStringToDateTest, invalidTextInput)
{
    EXPECT_THROW(convert_string_to_date("2022", "5", "blabla"),
                 InvalidDateException);
    EXPECT_THROW(convert_string_to_date("2022", "5", "bla23"),
                 InvalidDateException);
    EXPECT_THROW(convert_string_to_date("laks", "5", "23"),
                 InvalidDateException);
    EXPECT_THROW(convert_string_to_date("2022", "iause", "bla23"),
                 InvalidDateException);
    EXPECT_THROW(convert_string_to_date("avs", "we", "akwk"),
                 InvalidDateException);
}

TEST(ConvertStringToDateTest, noneInputOnDay)
{
    auto year_and_month = convert_string_to_date("2022", "5", "None");

    EXPECT_FALSE(year_and_month.ok());
    EXPECT_EQ(year_and_month.day(), date::day(0));
    EXPECT_EQ(year_and_month.month(), date::month(5));
    EXPECT_EQ(year_and_month.year(), date::year(2022));
}

TEST(ConvertStringToDateTest, noneInputOnMonth)
{
    auto year_and_month = convert_string_to_date("1999", "None", "23");

    EXPECT_FALSE(year_and_month.ok());
    EXPECT_EQ(year_and_month.day(), date::day(23));
    EXPECT_EQ(year_and_month.month(), date::month(0));
    EXPECT_EQ(year_and_month.year(), date::year(1999));
}

TEST(ConvertStringToDateTest, noneInputOnDayAndMonth)
{
    auto year_and_month = convert_string_to_date("1999", "None", "None");

    EXPECT_FALSE(year_and_month.ok());
    EXPECT_EQ(year_and_month.day(), date::day(0));
    EXPECT_EQ(year_and_month.month(), date::month(0));
    EXPECT_EQ(year_and_month.year(), date::year(1999));
}

TEST(ConvertStringToDateTest, noneInputOnYear)
{
    EXPECT_THROW(convert_string_to_date("None", "11", "23"),
                 InvalidDateException);
}