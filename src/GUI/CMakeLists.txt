cmake_minimum_required(VERSION 3.27)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DirectX11.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/InjectPanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EjectPanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SideBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SettingsPanel.cpp
)

add_subdirectory(Components)
