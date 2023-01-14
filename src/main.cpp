#include <iostream>
#include <string>
#include <image_path.h>
#include <cxxopts.hpp>

#define IMAGE_PATH "/mnt/d/bonsai-images"

namespace bonsai
{
    void run_insert(int argc, char *argv[])
    {
        cxxopts::Options options("insert", "some info here");
        options.add_options()
            ("t,tree-name", "The name of the tree to add an image to", cxxopts::value<std::string>())
            ("i,input", "Path to the input image", cxxopts::value<std::string>())
            ("y,year", "Year when the image was taken", cxxopts::value<std::string>())
            ("m,month", "Month when the image was taken", cxxopts::value<std::string>()->default_value("None"))
            ("d,day", "Day of the month when the image was taken", cxxopts::value<std::string>()->default_value("None"))
            ("h,help", "Print usage");

        auto parsed_options = options.parse(argc, argv);

        if (parsed_options.count("help"))
        {
            std::cout << options.help() << std::endl;
            return;
        }

        if (!parsed_options.count("tree-name") || !parsed_options.count("input") || !parsed_options.count("year"))
        {
            std::cout << "ERROR: --tree-name, --input, and --year are mandatory arguments"
                      << "\n";
            return;
        }

        auto year = parsed_options["year"].as<std::string>();
        auto month = parsed_options["month"].as<std::string>();
        auto day = parsed_options["day"].as<std::string>();

        auto date = convert_string_to_date(year, month, day);

        auto tree_name = parsed_options["tree-name"].as<std::string>();
        auto input_image = parsed_options["input"].as<std::string>();
        insert_image(tree_name, input_image, IMAGE_PATH);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "need inputs" << std::endl;
        return -1;
    }

    if ((std::string)argv[1] == "insert")
    {
        bonsai::run_insert(argc, argv);
    }
    return 1;
}
