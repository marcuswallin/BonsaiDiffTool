#include "image_path.h"
#include <string>
#include <filesystem>
#include <date/date.h>

using namespace std;

string convert_date_to_file_name(const date::year_month_day &date)
{
    ostringstream os;
    os << date.year();
    os.fill('0');

    if (date.month().ok())
    {
        os << "-";
        os.width(2);
        os << static_cast<unsigned>(date.month());

        if (date.day().ok())
        {
            os << "-";
            os.width(2);
            os << static_cast<unsigned>(date.day());
        }
    }
    return os.str();
}

// bool should not be necessary here
bool copy_file_with_date_as_file_name(const filesystem::path &input_file,
                                      const filesystem::path &output_directory,
                                      const date::year_month_day &date,
                                      const string &file_extension)
{
    filesystem::create_directory(output_directory);
    auto date_filename = convert_date_to_file_name(date);
    auto output_path = output_directory / (date_filename + file_extension);
    int count = 1;
    while (filesystem::exists(output_path))
    {
        output_path = output_directory / (date_filename + "_" + to_string(count) + file_extension);
        ++count;
    }
    return filesystem::copy_file(input_file, output_path);
}

bool insert_image(const std::string &tree_name,
                  const std::string &file_path,
                  const std::string &output_dir,
                  const date::year_month_day &date)
{
    auto input_path = filesystem::path(file_path);
    string file_extension = input_path.extension();
    if (file_extension == ".png" || file_extension == ".jpg")
    {
        auto tree_dir = filesystem::path(output_dir) / tree_name;
        return copy_file_with_date_as_file_name(input_path, tree_dir, date, file_extension);
    }
    else
    {
        throw WrongFileTypeException{};
    }
}

int convert_date_input_to_int(const string &date_input)
{
    try
    {
        return stoi(date_input);
    }
    catch (const std::invalid_argument &e)
    {
        throw InvalidDateException{"The input " + date_input + " should be an integer"};
    }
}

date::year_month_day convert_int_to_date(const int &year, const int &month, const int &day)
{
    auto no_input = 0;

    auto month_date = date::month(0);
    if (month != no_input)
    {
        month_date = date::month(month);
        if (!month_date.ok())
        {
            throw InvalidDateException{to_string(month) + " is not a valid month. The value should be an integer from 1-12 where 1=January and so on."};
        }
    }

    auto day_date = date::day(0);
    if (day != no_input)
    {
        day_date = date::day(day);
        if (!day_date.ok())
        {
            throw InvalidDateException{to_string(day) + " is not a day of month " + to_string(month)};
        }
    }

    auto year_date = date::year(year);
    if (!year_date.ok())
    {
        throw InvalidDateException{to_string(year) + " is not a valid year."};
    }

    auto date = date::year_month_day{year_date, month_date, day_date};
    return date;
}
