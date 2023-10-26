cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME Xash)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WIN32_EXECUTABLE ON)

project(
    ${PROJECT_NAME}
    VERSION 1.0.0
    LANGUAGES CXX RC
)

set(ICON_RC ${CMAKE_SOURCE_DIR}/assets/icon.rc)

add_executable(
    ${PROJECT_NAME}
    ${ICON_RC}
)

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:wWinMainCRTStartup"
)

if(MSVC)
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        /W4
    )
endif()

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    d3d11.lib
)

add_subdirectory(external)
add_subdirectory(src)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:${PROJECT_NAME}>
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}.exe
)
