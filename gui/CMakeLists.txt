cmake_minimum_required (VERSION 3.8)

file(GLOB INCLUDES "include/*.h")
file(GLOB CSOURCES "source/*.cpp")

set(CGAL_USE_SCIP True)

# Add source to this project's executable.
add_library(ForgeGuiLib ${INCLUDES} ${CSOURCES})

# link QT5 libraries
target_link_libraries(ForgeGuiLib 
	Qt5::Core 
	Qt5::Gui 
	Qt5::Widgets 
	Qt5::3DCore
	Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
	CGAL
	scip
	soplex
	zimpl
)