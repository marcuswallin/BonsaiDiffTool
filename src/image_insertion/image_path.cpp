#include "image_path.h"
#include <string>
#include <filesystem>
#include <date/date.h>

using namespace std;

bool insert_image(const string &tree_name, const string &file_path, const string &output_dir,
                  const string &year, const string &month, const string &day)
{
    auto input_path = filesystem::path(file_path);
    if (input_path.extension() == ".png" || input_path.extension() == ".jpg")
    {
        auto tree_dir = filesystem::path(output_dir) / tree_name;
        filesystem::create_directory(tree_dir);
        auto output_path = tree_dir / input_path.filename();
        return filesystem::copy_file(input_path, output_path);
    }
    else
    {
        throw WrongFileTypeException{};
    }
}

date::year_month_day convert_string_to_date(const string &year, const string &month, const string &day)
{
    auto date = date::year_month_day{date::year(stoi(year)), date::month(stoi(month)), date::day(stoi(day))};
    if (!date.ok())
    {
        throw InvalidDateException{};
    }
    return date;
}