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
