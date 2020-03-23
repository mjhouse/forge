cmake_minimum_required (VERSION 3.8)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(forge_gui PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/FCameraController.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EventFilters.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/HasIdentifier.cpp"
)