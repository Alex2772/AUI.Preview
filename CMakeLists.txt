cmake_minimum_required(VERSION 3.14.4)

project(aui.preview)

add_subdirectory(library)

if (NOT TARGET aui::core)
    set(AUI_DIR "" CACHE PATH "AUI DIR PATH")

    find_package(AUI REQUIRED)
endif()

if (AUI_PREVIEW_BUILD_EXECUTABLE)
    aui_executable(aui.preview "${ADDITIONAL_SRCS}")

    aui_compile_assets(aui.preview)

    target_link_libraries(aui.preview PRIVATE aui.core)
    target_link_libraries(aui.preview PRIVATE aui.views)
    target_link_libraries(aui.preview PRIVATE aui.json)
    target_link_libraries(aui.preview PRIVATE aui.preview.library)

    if (MSVC)
        set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /MANIFEST:NO")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
    endif()

endif()