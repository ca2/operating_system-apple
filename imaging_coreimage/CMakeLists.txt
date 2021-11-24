cmake_minimum_required(VERSION 3.17)
project(imaging_coreimage CXX)


list(APPEND library_source
        _.h
        context_image.h
        _factory.cpp
        factory_exchange.h
        framework.cpp
        framework.h
        image.cpp
        image_gif.cpp
        mm_macos_image.mm
        save_image.cpp
)

list(APPEND library_references
   acme apex aqua aura axis)

add_library(imaging_coreimage SHARED ${library_source})

target_precompile_headers(imaging_coreimage PRIVATE framework.h)

set_target_properties(imaging_coreimage PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(imaging_coreimage PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_coreimage PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_coreimage PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/imaging_coreimage.lib")
    target_link_options(imaging_coreimage PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/imaging_coreimage.def")
    target_link_libraries(imaging_coreimage PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(imaging_coreimage PRIVATE -fpermissive)
    target_compile_options(imaging_coreimage PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(imaging_coreimage PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(imaging_coreimage PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(imaging_coreimage PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(imaging_coreimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(imaging_coreimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(imaging_coreimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(imaging_coreimage PRIVATE _imaging_coreimage_LIBRARY)



