﻿cmake_minimum_required (VERSION 3.8)
add_library(forge_core)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory("models")
add_subdirectory("symbols")
add_subdirectory("system")

target_sources(forge_core PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/FGeometry.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/FMaterial.cpp"
)

# link QT5 libraries
target_link_libraries(forge_core 
    qtmain        # handles windows-specific WinMain exe
    forge_gui     # gui-code for this application
    Qt5::Core 
	Qt5::Gui 
	Qt5::Widgets 
	Qt5::3DCore
	Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
)