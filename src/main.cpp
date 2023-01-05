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
        options.add_options()("t,tree-name", "The name of the tree to add an image to", cxxopts::value<std::string>())("i,input", "Path to the input image", cxxopts::value<std::string>())("h,help", "Print usage");

        auto parsed_options = options.parse(argc, argv);

        if (parsed_options.count("help"))
        {
            std::cout << options.help() << std::endl;
        }

        if (!parsed_options.count("tree-name") || !parsed_options.count("input"))
        {
            std::cout << "Need two input arguments hlo"
                      << "\n";
            return;
        }

        insert_image(parsed_options["tree-name"].as<std::string>(), parsed_options["input"].as<std::string>(), IMAGE_PATH);
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
