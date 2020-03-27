cmake_minimum_required (VERSION 3.8)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(forge_core PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/FSymbol.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/FCrossSection.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/FLine.cpp"
)