//
// Created by marcus.wallin on 11/11/22.
//

#ifndef BONSAIDIFFTOOL_IMAGEIO_H
#define BONSAIDIFFTOOL_IMAGEIO_H

#include <string>
#include <exception>

class WrongFileTypeException : public std::exception {
};

class Date{

};

bool insert_image(const std::string &tree_name, const std::string &file_path, const std::string &output_dir);

#endif //BONSAIDIFFTOOL_IMAGEIO_H
