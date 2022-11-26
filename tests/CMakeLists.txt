include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_Declare(
        date_src
        GIT_REPOSITORY https://github.com/HowardHinnant/date.git
        GIT_TAG        v3.0.1
        )
FetchContent_MakeAvailable(date_src)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)

#add_library(date::date INTERFACE IMPORTED)

add_executable(
        image_insertion_test
        image_insertion_test.cpp
)

target_link_libraries(
        image_insertion_test
        PRIVATE
        GTest::gtest_main
        date::date
        ImageInsertion
)

add_test(image_insertion_gtest image_insertion_test)

file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/test_files)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test_files)
file(GLOB TEST_FILES "test_files/*")
file(COPY ${TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_files)
