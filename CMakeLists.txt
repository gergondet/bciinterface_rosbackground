cmake_minimum_required(VERSION 2.8.3)
project(bciinterface_rosbackground)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  image_transport
)

find_package(Boost REQUIRED COMPONENTS filesystem system thread)

include_directories(${Boost_INCLUDE_DIRS})

include(FindPkgConfig)

pkg_check_modules(BCIINTERFACE bci-interface)
include_directories( ${BCIINTERFACE_INCLUDE_DIRS} )
link_directories( ${BCIINTERFACE_LIBRARY_DIRS} )

include_directories(${catkin_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

catkin_package()

add_library(rosbackground src/ROSBackground.cpp)
target_link_libraries(rosbackground ${catkin_LIBRARIES} bci-interface sfml-graphics sfml-window sfml-system)

add_executable(testROSBackground src/testROSBackground.cpp)
target_link_libraries(testROSBackground rosbackground ${Boost_LIBRARIES})

install(TARGETS rosbackground DESTINATION ${BCIINTERFACE_LIBRARY_DIRS})
install(FILES include/bciinterface_rosbackground/ROSBackground.h DESTINATION ${BCIINTERFACE_INCLUDE_DIRS}/bci-interface/Background)
