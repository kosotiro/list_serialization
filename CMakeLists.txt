cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(SerDeserList VERSION 1.0 LANGUAGES C)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

# Some other library that we import that was also built using CMake
# and has an exported target.
#find_package(serdeser REQUIRED)
set(MAINFOLDER ${PROJECT_SOURCE_DIR})

# Targets that we develop here
add_subdirectory(mylist)
add_subdirectory(serialize)
add_subdirectory(serialize_list)
add_subdirectory(serialize_process)
add_subdirectory(deserialize_process)
