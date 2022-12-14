add_subdirectory(image_insertion)

add_executable(main main.cpp)

target_link_libraries(
        main
        PRIVATE
        ImageInsertion
        date::date
        cxxopts
)
