cmake_minimum_required(VERSION 3.27)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_subdirectory(GUI)
add_subdirectory(injector)
add_subdirectory(system)
add_subdirectory(settings)
