#include "image_path.h"
#include <string>
#include <filesystem>
#include <date/date.h>

using namespace std;

string convert_date_to_file_name(const date::year_month_day &date, const string &file_extension)
{
    return "hello";
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
        filesystem::create_directory(tree_dir);
        auto output_path = tree_dir / convert_date_to_file_name(date, file_extension);
        return filesystem::copy_file(input_path, output_path);
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
        throw InvalidDateException{};
    }
}

date::year_month_day convert_string_to_date(const string &year, const string &month, const string &day)
{
    auto no_input = "None";

    auto day_date = date::day(0);
    if (day != no_input)
    {
        day_date = date::day(convert_date_input_to_int(day));
        if (!day_date.ok())
        {
            throw InvalidDateException{};
        }
    }

    auto month_date = date::month(0);
    if (month != no_input)
    {
        month_date = date::month(convert_date_input_to_int(month));
        if (!month_date.ok())
        {
            throw InvalidDateException{};
        }
    }

    auto year_date = date::year(convert_date_input_to_int(year));
    if (!year_date.ok())
    {
        throw InvalidDateException{};
    }

    auto date = date::year_month_day{year_date, month_date, day_date};
    return date;
}
