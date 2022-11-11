//
// Created by marcus.wallin on 11/11/22.
//

#include "image_insertion.h"
#include <string>
#include <iostream>
#include <filesystem>

#define IMAGE_PATH filesystem::path("/d/MyStuff/bonsai-images")

using namespace std;


int get_number_two()
{
    return 2;
}

void insert_image(const std::string &tree_name, const std::string &file_path, const std::string &output_dir)
{
    auto input_path = filesystem::path(file_path);
    if (input_path.extension() != ".png")
    {
        throw WrongFileTypeException{};
    }
    auto output_path = filesystem::path(output_dir) / tree_name / input_path.filename();
    filesystem::copy_file(input_path, output_path);
}


