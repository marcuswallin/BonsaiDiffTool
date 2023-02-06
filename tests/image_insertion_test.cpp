#include <gtest/gtest.h>
#include <image_path.h>
#include <filesystem>
#include <date/date.h>
#include <test_path.h> // cmake defined file containing the path to this compiled binary 

using namespace std;

class ImageInsertionTest : public ::testing::Test
{
protected:
    std::filesystem::path current_working_directory = TEST_PATH;
    std::filesystem::path test_files = current_working_directory / "test_files";
    std::filesystem::path actual_files = current_working_directory / "actual_files";
    std::filesystem::path birch_image1_path = test_files / "birch1.png";
    std::filesystem::path birch_image2_path = test_files / "birch2.png";

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

TEST_F(ImageInsertionTest, image_that_does_not_exist)
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

TEST_F(ImageInsertionTest, should_copy_png_files)
{
    const string tree_name = "birch1";

    const bool copySuccessful = insert_image(tree_name, birch_image1_path, actual_files, date);
    EXPECT_TRUE(copySuccessful);
    verifyFileExists(tree_name, "2022-10-03.png");
}

TEST_F(ImageInsertionTest, insert_two_png_files_to_same_folder)
{
    const string tree_name = "birch1";

    EXPECT_TRUE(insert_image(tree_name, birch_image1_path, actual_files, date));
    EXPECT_TRUE(insert_image(tree_name, birch_image2_path, actual_files, date + date::months(1)));

    verifyFileExists(tree_name, "2022-10-03.png");
    verifyFileExists(tree_name, "2022-11-03.png");
}

TEST_F(ImageInsertionTest, insert_two_png_files_to_different_folder)
{
    const string tree_name1 = "birch1";
    const string tree_name2 = "birch2";

    EXPECT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, date));
    EXPECT_TRUE(insert_image(tree_name2, birch_image2_path, actual_files, date));

    verifyFileExists(tree_name1, "2022-10-03.png");
    verifyFileExists(tree_name2, "2022-10-03.png");
}

TEST_F(ImageInsertionTest, insert_two_files_with_same_date)
{
    const string tree_name1 = "birch1";

    EXPECT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, date));
    EXPECT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, date));

    verifyFileExists(tree_name1, "2022-10-03.png");
    verifyFileExists(tree_name1, "2022-10-03_1.png");
}

TEST_F(ImageInsertionTest, insert_three_files_with_same_date_only_year_available)
{
    const string tree_name1 = "birch1";
    date::year_month_day year_date{date::year{2015}, date::month{0}, date::day{0}};

    EXPECT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, year_date));
    EXPECT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, year_date));
    EXPECT_TRUE(insert_image(tree_name1, birch_image1_path, actual_files, year_date));

    verifyFileExists(tree_name1, "2015.png");
    verifyFileExists(tree_name1, "2015_1.png");
    verifyFileExists(tree_name1, "2015_2.png");
}

TEST(ConvertStringToDateTest, normalInput)
{
    auto date = convert_int_to_date(2022, 5, 23);

    EXPECT_EQ(date.day(), date::day(23));
    EXPECT_EQ(date.month(), date::month(5));
    EXPECT_EQ(date.year(), date::year(2022));
}

TEST(ConvertStringToDateTest, dateThatDoesNotExist)
{
    EXPECT_THROW(convert_int_to_date(2022, 5, 35),
                 InvalidDateException);
    EXPECT_THROW(convert_int_to_date(2000, -1, 5),
                 InvalidDateException);
    EXPECT_THROW(convert_int_to_date(2022, -5, 20),
                 InvalidDateException);
    EXPECT_THROW(convert_int_to_date(2022, 5, -10),
                 InvalidDateException);
    EXPECT_THROW(convert_int_to_date(2022, 14, 8),
                 InvalidDateException);
}

TEST(ConvertStringToDateTest, noneInputOnDay)
{
    auto year_and_month = convert_int_to_date(2022, 5, 0);

    EXPECT_FALSE(year_and_month.ok());
    EXPECT_EQ(year_and_month.day(), date::day(0));
    EXPECT_EQ(year_and_month.month(), date::month(5));
    EXPECT_EQ(year_and_month.year(), date::year(2022));
}

TEST(ConvertStringToDateTest, noneInputOnMonth)
{
    auto year_and_month = convert_int_to_date(1999, 0, 23);

    EXPECT_FALSE(year_and_month.ok());
    EXPECT_EQ(year_and_month.day(), date::day(23));
    EXPECT_EQ(year_and_month.month(), date::month(0));
    EXPECT_EQ(year_and_month.year(), date::year(1999));
}

TEST(ConvertStringToDateTest, noneInputOnDayAndMonth)
{
    auto year_and_month = convert_int_to_date(1999, 0, 0);

    EXPECT_FALSE(year_and_month.ok());
    EXPECT_EQ(year_and_month.day(), date::day(0));
    EXPECT_EQ(year_and_month.month(), date::month(0));
    EXPECT_EQ(year_and_month.year(), date::year(1999));
}

TEST(ConvertDateToFileName, validDate)
{
    date::year_month_day date{date::year{1999}, date::month{12}, date::day{25}};
    auto file_name = convert_date_to_file_name(date);
    EXPECT_EQ(file_name, "1999-12-25");
}

TEST(ConvertDateToFileName, validDateWithOneIntegerInMOnthAndDay)
{
    date::year_month_day date{date::year{2022}, date::month{2}, date::day{8}};
    auto file_name = convert_date_to_file_name(date);
    EXPECT_EQ(file_name, "2022-02-08");
}

TEST(ConvertDateToFileName, unknownDay)
{
    date::year_month_day date{date::year{2022}, date::month{4}, date::day{0}};
    auto file_name = convert_date_to_file_name(date);
    EXPECT_EQ(file_name, "2022-04");
}

TEST(ConvertDateToFileName, unknownDayAndMonth)
{
    date::year_month_day date{date::year{2022}, date::month{0}, date::day{0}};
    auto file_name = convert_date_to_file_name(date);
    EXPECT_EQ(file_name, "2022");
}

TEST(ConvertDateToFileName, unknownMonthNotDay)
{
    date::year_month_day date{date::year{2022}, date::month{0}, date::day{12}};
    auto file_name = convert_date_to_file_name(date);
    EXPECT_EQ(file_name, "2022");
}