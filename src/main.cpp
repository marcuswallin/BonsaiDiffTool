#include <iostream>
#include <string>
#include <image_path.h>
#include <image_viewer.h>
#include <cxxopts.hpp>

#define IMAGE_PATH "/mnt/d/bonsai-images"

namespace bonsai
{
    void run_insert(int argc, char *argv[])
    {
        cxxopts::Options options("insert", "some info here");
        options.add_options()("t,tree-name", "The name of the tree to add an image to", cxxopts::value<std::string>())("i,input", "Path to the input image", cxxopts::value<std::string>())("y,year", "Year when the image was taken", cxxopts::value<int>())("m,month", "Month when the image was taken as integer 1-12", cxxopts::value<int>()->default_value("0"))("d,day", "Day of the month when the image was taken, must be valid day in the given month", cxxopts::value<int>()->default_value("0"))("h,help", "Print usage");

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

        auto year = parsed_options["year"].as<int>();
        auto month = parsed_options["month"].as<int>();
        auto day = parsed_options["day"].as<int>();

        auto date = convert_int_to_date(year, month, day);

        auto tree_name = parsed_options["tree-name"].as<std::string>();
        auto input_image = parsed_options["input"].as<std::string>();
        insert_image(tree_name, input_image, IMAGE_PATH, date);
    }

    void run_show(int argc, char *argv[])
    {
        std::cout << "Running show command" << "\n";
    }
    

}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "need inputs" << std::endl;
        return -1;
    }

    try
    {
        if ((std::string)argv[1] == "insert")
        {
            bonsai::run_insert(argc, argv);
        }

        if ((std::string)argv[1] == "show")
        {
            bonsai::run_show(argc, argv);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }

    return 1;
}
