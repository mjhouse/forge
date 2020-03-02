cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
file(GLOB INCLUDES "include/*.h")
file(GLOB CSOURCES "source/*.cpp")

add_executable(Forge WIN32 ${INCLUDES} ${CSOURCES})

# link QT5 libraries
target_link_libraries(Forge 
    qtmain        # handles windows-specific WinMain exe
    forge_core    # core business logic for Forge
    forge_gui     # GUI components and commands for Forge
)

add_custom_command(TARGET Forge POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core>        $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui>         $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets>     $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DCore>      $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DExtras>    $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DRender>    $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DInput>     $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DLogic>     $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network>     $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gamepad>     $<TARGET_FILE_DIR:Forge>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Concurrent>  $<TARGET_FILE_DIR:Forge>
)