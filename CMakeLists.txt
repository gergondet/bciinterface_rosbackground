cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

INCLUDE(FindPkgConfig)
pkg_check_modules(BCIINTERFACE bci-interface)
IF(BCIINTERFACE_FOUND)
EXEC_PROGRAM(${PKG_CONFIG_EXECUTABLE} ARGS bci-interface --cflags
  OUTPUT_VARIABLE BCIINTERFACE_CFLAGS)
MESSAGE(STATUS "BCIINTERFACE_CFLAGS: ${BCIINTERFACE_CFLAGS}")
EXEC_PROGRAM(${PKG_CONFIG_EXECUTABLE} ARGS bci-interface --libs
  OUTPUT_VARIABLE BCIINTERFACE_LIBS)
MESSAGE(STATUS "BCIINTERFACE_LIBS: ${BCIINTERFACE_LIBS}")
ELSE(BCIINTERFACE_FOUND)
MESSAGE(STATUS "bci-interface not found")
ENDIF(BCIINTERFACE_FOUND)

find_package( configparser )
find_package( vision )
find_package( visionsystem )
include_directories( ${VISIONSYSTEM_INCLUDE_DIRS} )
link_directories( "${VISIONSYSTEM_LIBRARY_DIRS}")

rosbuild_add_library(rosbackground src/ROSBackground.cpp)
target_link_libraries(rosbackground bci-interface sfml-graphics sfml-window sfml-system)

rosbuild_add_executable(testROSBackground src/testROSBackground.cpp)
target_link_libraries(testROSBackground rosbackground bci-interface)
rosbuild_link_boost(testROSBackground filesystem system thread)

install(TARGETS rosbackground DESTINATION ${BCIINTERFACE_LIBRARY_DIRS})
install(FILES include/bciinterface_rosbackground/ROSBackground.h DESTINATION ${BCIINTERFACE_INCLUDE_DIRS}/bci-interface/Background)
