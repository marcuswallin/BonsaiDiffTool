#include <iostream>
#include <string>
#include <image_insertion.h>

#define IMAGE_PATH "/d/MyStuff/bonsai-images"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "Need two input arguments" << "\n";
    }
    insert_image((std::string) argv[1], (std::string) argv[2], IMAGE_PATH);

    return 1;
}

