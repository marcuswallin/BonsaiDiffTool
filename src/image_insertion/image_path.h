//
// Created by marcus.wallin on 11/11/22.
//

#ifndef BONSAIDIFFTOOL_IMAGEPATH_H
#define BONSAIDIFFTOOL_IMAGEPATH_H

#include <string>
#include <exception>
#include <filesystem>
#include <date/date.h>

class WrongFileTypeException : public std::exception
{
};

class InvalidDateException : public std::exception
{
private:
    std::string message;

public:
    explicit InvalidDateException(const std::string &message_) : message{message_} {};
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

bool insert_image(const std::string &tree_name,
                  const std::string &file_path,
                  const std::string &output_dir,
                  const date::year_month_day &date);

date::year_month_day convert_int_to_date(const int &year, const int &month, const int &day);

/*
    This function converts a date to a filename without file extension.
    The date should either contain an existing date, or a month or day field with zeros, indicating that this is unknown.
*/
std::string convert_date_to_file_name(const date::year_month_day &date);

#endif // BONSAIDIFFTOOL_IMAGEPATH_H
