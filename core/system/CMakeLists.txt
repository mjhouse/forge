﻿cmake_minimum_required (VERSION 3.8)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(forge_core PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/BulkLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Messages.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Message.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp"
)