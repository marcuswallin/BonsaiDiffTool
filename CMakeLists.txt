cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(BonsaiDiffTool VERSION 1.0)

enable_testing()

include(FetchContent)

FetchContent_Declare(
        date_src
        GIT_REPOSITORY https://github.com/HowardHinnant/date.git
        GIT_TAG        v3.0.1
        )
FetchContent_MakeAvailable(date_src)

add_subdirectory(tests)
add_subdirectory(src)
