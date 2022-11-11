//
// Created by marcus.wallin on 11/10/22.
//

#include <iostream>
#include <string>
#include <image_insertion.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "Need two input arguments" << "\n";
    }
    insert_image((std::string) argv[1], (std::string) argv[2], <#initializer#>);

    return 1;
}

