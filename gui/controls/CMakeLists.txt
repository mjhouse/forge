﻿cmake_minimum_required (VERSION 3.8)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(forge_gui PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/ForgeCreate.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/ForgeTransform.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/ForgeMainMenu.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/ForgeTitleBar.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/FOrigin.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/ForgeControl.cpp" 
)