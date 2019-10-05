cmake_minimum_required(VERSION 3.1)
project(rov_challenge)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


set(SOURCES
        rov_chall_ui/joystick.cpp
        rov_chall_ui/joystick_receive.cpp
        rov_chall_ui/main.cpp
        rov_chall_ui/mainwindow.cpp
        rov_chall_ui/rovtimer.cpp
        rov_chall_ui/keybindings.cpp
        rov_chall_ui/connectionwindow.cpp
        libs/rosservice.cpp
        )

set(MOC_HEADERS
        rov_chall_ui/joystick.h
        rov_chall_ui/joystick_receive.h
        rov_chall_ui/mainwindow.h
        rov_chall_ui/rovtimer.h
        rov_chall_ui/keybindings.h
        rov_chall_ui/connectionwindow.h
        libs/rosservice.h
        libs/rospublisher.h
        libs/rossubscriber.h
        )

set(UIS
        rov_chall_ui/mainwindow.ui
        rov_chall_ui/keybindings.ui
        rov_chall_ui/connectionwindow.ui
    )

find_package(catkin REQUIRED COMPONENTS roscpp)
catkin_package(
  CATKIN_DEPENDS roscpp geometry_msgs
  DEPENDS system-lib
)
include_directories(src ${catkin_INCLUDE_DIRS})

# Next lines needed for building all Qt projects
find_package(Qt5 COMPONENTS Widgets REQUIRED)
#include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories( ${CMAKE_BINARY_DIR} )

find_package( Qt5Multimedia REQUIRED )
find_package( Qt5MultimediaWidgets REQUIRED )
set(QT_USE_QTMULTIMEDIA TRUE)
set(QT_USE_QTMULTIMEDIAWIDGETS TRUE)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Next, using precompiler, compiler and linker

# using Qt meta-system (precompiler)
QT5_WRAP_UI( UI_HEADERS ${UIS} )
QT5_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

# compile
add_executable(rov_challenge ${SOURCES} ${MOC_SRCS} ${UI_HEADERS} )
# or use line below instead, if you using Windows ™ Operating System.
#add_executable( PROJECT_NAME WIN32 ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )

# build it (link libraries)
QT5_USE_MODULES (rov_challenge Multimedia MultimediaWidgets)
target_link_libraries(rov_challenge ${QT_LIBRARIES} )

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(rov_challenge ${SDL2_LIBRARIES} ${catkin_LIBRARIES})
install(TARGETS rov_challenge
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

