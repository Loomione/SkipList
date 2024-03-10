cmake_minimum_required(VERSION 3.12)
project(skiplist)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
# Add the include directory
include_directories(include)

# Add the source files
set(SOURCES
    source/skip_list.cc
)

# Build the library
add_library(skiplist_lib STATIC ${SOURCES})

# Build the executable
add_executable(skiplist main.cc)

# Link the library with the executable
target_link_libraries(skiplist skiplist_lib)