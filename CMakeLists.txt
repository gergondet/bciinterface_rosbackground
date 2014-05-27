cmake_minimum_required(VERSION 2.8.3)
project(bciinterface_rosbackground)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  image_transport
  ros_h264_streamer
)

find_package(Boost REQUIRED COMPONENTS filesystem system thread)

include_directories(${Boost_INCLUDE_DIRS})

include(FindPkgConfig)

pkg_check_modules(BCIINTERFACE bci-interface)
if(${BCIINTERFACE_LIBRARY_DIRS})
include_directories( ${BCIINTERFACE_INCLUDE_DIRS} )
link_directories( ${BCIINTERFACE_LIBRARY_DIRS} )
else()
set(BCIINTERFACE_INCLUDE_DIRS /usr/include)
set(BCIINTERFACE_LIBRARY_DIRS /usr/lib)
endif()

include_directories(${catkin_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES rosbackground
  CATKIN_DEPENDS roscpp image_transport ros_h264_streamer
)

add_library(rosbackground
src/private/ROSBackgroundImpl.cpp
src/private/ROSBackgroundImageTopicImpl.cpp
src/private/ROSBackgroundH264ReceiverImpl.cpp
src/ROSBackground.cpp
)
target_link_libraries(rosbackground ${catkin_LIBRARIES} bci-interface sfml-graphics sfml-window sfml-system)

add_executable(testROSBackgroundImageTopic test/testROSBackgroundImageTopic.cpp)
target_link_libraries(testROSBackgroundImageTopic rosbackground ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(testROSBackgroundNetwork test/testROSBackgroundNetwork.cpp)
target_link_libraries(testROSBackgroundNetwork rosbackground ${catkin_LIBRARIES} ${Boost_LIBRARIES})

install(TARGETS rosbackground DESTINATION ${BCIINTERFACE_LIBRARY_DIRS})
install(FILES include/bci-interface/Background/ROSBackground.h DESTINATION ${BCIINTERFACE_INCLUDE_DIRS}/bci-interface/Background)
