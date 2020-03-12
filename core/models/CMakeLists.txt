cmake_minimum_required (VERSION 3.8)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(forge_core PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/FModel.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/FModelExtruded.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/FModelLine.cpp"
)