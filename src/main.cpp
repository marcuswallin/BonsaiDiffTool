#include <iostream>
#include <string>
#include <image_path.h>
#include <cxxopts.hpp>

#define IMAGE_PATH "/d/MyStuff/bonsai-images"

int main(int argc, char *argv[])
{

    cxxopts::Options options("dog", "some info here");
    options.add_options()
        ("n,number", "Show line numbers") 
        ("E,show-ends", "Show line endings")
        ("h,help", "Print usage")
    ;
    
    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      exit(0);
    }

    if(argc != 3)
    {
        std::cout << "Need two input arguments hello" << "\n";
        return -1;
    }
    insert_image((std::string) argv[1], (std::string) argv[2], IMAGE_PATH);

    return 1;
}

