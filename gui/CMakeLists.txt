cmake_minimum_required (VERSION 3.8)
add_library(forge_gui)

add_subdirectory("components")
add_subdirectory("windows")

# link QT5 libraries
target_link_libraries(forge_gui 
	Qt5::Core 
	Qt5::Gui 
	Qt5::Widgets 
	Qt5::3DCore
	Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
)