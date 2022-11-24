//
// Created by marcus.wallin on 11/11/22.
//

#include "image_insertion.h"
#include <string>
#include <filesystem>

using namespace std;

bool insert_image(const std::string &tree_name, const std::string &file_path, const std::string &output_dir)
{
    auto input_path = filesystem::path(file_path);
    if (input_path.extension() != ".png")
    {
        throw WrongFileTypeException{};
    }
    auto tree_dir = filesystem::path(output_dir) / tree_name;
    filesystem::create_directory(tree_dir);
    auto output_path = tree_dir / input_path.filename();
    return filesystem::copy_file(input_path, output_path);
}


