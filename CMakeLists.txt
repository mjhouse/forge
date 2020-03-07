cmake_minimum_required (VERSION 3.8)
project ("Forge")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT5_INSTALL "C:/Qt/5.14.1/msvc2017_64")
set(CMAKE_PREFIX_PATH ${QT5_INSTALL})

include_directories("${QT5_INSTALL}/include/")

include_directories("core/include")
include_directories("gui/windows")
include_directories("gui/components")
include_directories("gui/controls")

link_directories("${QT5_INSTALL}/lib")

find_package(Qt5 COMPONENTS Widgets Core Gui 3DCore 3DExtras 3DRender 3DInput Network Gamepad Concurrent REQUIRED)

# Include sub-projects.
add_subdirectory ("forge")
add_subdirectory ("core")
add_subdirectory ("gui")

file(COPY "resources" DESTINATION "forge")
file(COPY "${QT5_INSTALL}/plugins/geometryloaders" DESTINATION "forge")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    if(WIN32)
	    file(COPY "${QT5_INSTALL}/plugins/platforms/qwindowsd.dll" DESTINATION "forge/platforms")
    endif(WIN32)
else()
    if(WIN32)
	    file(COPY "${QT5_INSTALL}/plugins/platforms/qwindows.dll" DESTINATION "forge/platforms")
    endif(WIN32)
endif()