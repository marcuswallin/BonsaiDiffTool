//
// Created by marcus.wallin on 11/11/22.
//

#ifndef BONSAIDIFFTOOL_IMAGEIO_H
#define BONSAIDIFFTOOL_IMAGEIO_H

#include <string>
#include <exception>
#include <filesystem>
#include <date/date.h>

class WrongFileTypeException : public std::exception
{
};

class InvalidDateException : public std::exception
{
};

bool insert_image(const std::string &tree_name, const std::string &file_path, const std::string &output_dir,
                  const std::string &year = "2022", const std::string &month = "01", const std::string &day = "01");

date::year_month_day convert_string_to_date(const std::string &year, const std::string &month, const std::string &day);

#endif // BONSAIDIFFTOOL_IMAGEIO_H
