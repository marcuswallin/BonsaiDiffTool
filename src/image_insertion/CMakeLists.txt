add_library(ImageInsertion image_insertion.cpp image_insertion.h)

target_link_libraries(
    ImageInsertion
    PUBLIC
    date::date)

target_include_directories(ImageInsertion PUBLIC .)
