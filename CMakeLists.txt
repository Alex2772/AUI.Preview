cmake_minimum_required(VERSION 3.14.4)

project(AUI.Preview)

add_subdirectory(library)

if (NOT TARGET AUI.Core)
    set(AUI_DIR "" CACHE PATH "AUI DIR PATH")

    if(AUI_USE_OLD_WAY)
        add_subdirectory(${AUI_DIR} build)
    else()
        message("Using new way to link AUI")
        find_package(AUI REQUIRED)
    endif()
endif()

if (TARGET AUI.Core AND NOT AUI.Views)
    message(STATUS "AUI.Views not found. Disabling AUI.Preview")
else()
    AUI_Deploy_Library(AUI.Svg)
    AUI_Deploy_Library(AUI.Image)

    AUI_Executable_Advanced(AUI.Preview "${ADDITIONAL_SRCS}")

    AUI_Compile_Assets(AUI.Preview)

    target_link_libraries(AUI.Preview PRIVATE AUI.Core)
    target_link_libraries(AUI.Preview PRIVATE AUI.Views)
    target_link_libraries(AUI.Preview PRIVATE AUI.Json)
    target_link_libraries(AUI.Preview PRIVATE AUI.Preview.Library)

    if (MSVC)
        set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /MANIFEST:NO")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
    endif()
endif()