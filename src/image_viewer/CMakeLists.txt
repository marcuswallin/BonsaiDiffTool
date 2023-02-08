add_library(ImageViewer image_viewer.cpp image_viewer.h)

target_link_libraries(
    ImageViewer
    PUBLIC
    OpenCV)

target_include_directories(ImageViewer PUBLIC .)
