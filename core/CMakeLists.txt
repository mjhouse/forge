cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
file(GLOB INCLUDES "include/*.h")
file(GLOB CSOURCES "source/*.cpp")

add_library(forge_core ${INCLUDES} ${CSOURCES})

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