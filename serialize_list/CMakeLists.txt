cmake_minimum_required(VERSION 3.5)
project(serdeserlist VERSION 1.0.0 LANGUAGES C)

add_library(serdeserlist src/serialization_list.c)

# Depend on a library that we defined in the top-level file
target_link_libraries(serdeserlist
  PRIVATE
    mylist
    serdeser)

#include_directories(${Lib1_SOURCE_DIR})

target_include_directories(serdeserlist
    PUBLIC 
        #${mylist_INCLUDE_DIR}
        #${serdeser_INCLUDE_DIR}
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS serdeserlist EXPORT SerDeserListLibraryConfig 
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}/build
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}/build
  RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/build)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT SerDeserListLibraryConfig DESTINATION share/SerDeserListLibrary/cmake)

# This makes the project importable from the build directory
export(TARGETS serdeserlist FILE SerDeserListLibraryConfig.cmake)
