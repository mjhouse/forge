cmake_minimum_required (VERSION 3.8)
project ("Forge")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE True)
set(CGAL_EIGEN3_ENABLED True)
set(CGAL_USE_SCIP True)

set(QT5_INSTALL "C:/Qt/5.14.1/msvc2017_64")
set(CGAL_DIR "C:/dev/CGAL-5.0.1/lib/cmake/CGAL")
set(BOOST_ROOT "C:/local/boost_1_72_0/")
set(CMAKE_PREFIX_PATH ${QT5_INSTALL})

include_directories("${QT5_INSTALL}/include/")
include_directories("C:/Program Files/SCIPOptSuite 6.0.2/include")
include_directories("dependencies")
include_directories("core/include")
include_directories("gui/include")

link_directories("${QT5_INSTALL}/lib")
link_directories("C:/Program Files/SCIPOptSuite 6.0.2/lib")

find_package(Qt5 COMPONENTS Widgets Core Gui 3DCore 3DExtras 3DRender 3DInput Network Gamepad Concurrent REQUIRED)
find_package(Boost REQUIRED)
find_package(CGAL REQUIRED)

# Include sub-projects.
add_subdirectory ("core")
add_subdirectory ("gui")

file(COPY "resources" DESTINATION "core")
file(COPY "${QT5_INSTALL}/plugins/geometryloaders" DESTINATION "core")
file(COPY "C:/dev/CGAL-5.0.1/auxiliary/gmp/lib/libgmp-10.dll" DESTINATION "core")
file(COPY "C:/dev/CGAL-5.0.1/auxiliary/gmp/lib/libmpfr-4.dll" DESTINATION "core")
file(COPY "C:/Program Files/SCIPOptSuite 6.0.2/bin/scip.dll" DESTINATION "core")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    if(WIN32)
	    file(COPY "${QT5_INSTALL}/plugins/platforms/qwindowsd.dll" DESTINATION "core/platforms")
    endif(WIN32)
else()
    if(WIN32)
	    file(COPY "${QT5_INSTALL}/plugins/platforms/qwindows.dll" DESTINATION "core/platforms")
    endif(WIN32)
endif()