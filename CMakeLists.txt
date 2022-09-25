cmake_minimum_required(VERSION 3.16)
project(lab2_sem3)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_CXX_FLAGS -fsanitize=address)

add_compile_options(
        -Werror

        -Wall
        #        -Wextra
        #        -Wpedantic
        #
        #        -Wcast-align
        #        -Wcast-qual
        #        -Wconversion
        #        -Wctor-dtor-privacy
        #        -Wenum-compare
        #        -Wfloat-equal
        #        -Wnon-virtual-dtor
        #        -Wold-style-cast
        #        -Woverloaded-virtual
        #        -Wredundant-decls
        #        -Wsign-conversion
        #        -Wsign-promo
)

set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\")
find_package(Qt5Widgets REQUIRED)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
#add_subdirectory(test/lib/googletest)