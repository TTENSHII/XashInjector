cmake_minimum_required(VERSION 3.27)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/MonoModule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Assembly.cpp
)
