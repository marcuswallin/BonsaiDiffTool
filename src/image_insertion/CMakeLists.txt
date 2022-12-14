add_library(ImageInsertion image_path.cpp image_path.h)

target_link_libraries(
    ImageInsertion
    PUBLIC
    date::date)

target_include_directories(ImageInsertion PUBLIC .)
