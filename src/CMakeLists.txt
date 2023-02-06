add_subdirectory(image_insertion)
add_subdirectory(image_viewer)

add_executable(bonsai main.cpp)

target_link_libraries(
        bonsai
        PRIVATE
        ImageInsertion
        date::date
        cxxopts
)
