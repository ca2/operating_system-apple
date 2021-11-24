cmake_minimum_required(VERSION 3.17)
project(draw2d_quartz2d CXX)


list(APPEND draw2d_quartz2d_source
        _.cpp
        _.h
        _draw2d_quartz2d.h
        database.cpp
        database.h
        _factory.cpp
        factory_exchange.h
        framework.cpp
        framework.h
)

list(APPEND library_references
   acme apex aqua aura axis)

add_library(draw2d_quartz2d SHARED ${draw2d_quartz2d_source})

target_precompile_headers(draw2d_quartz2d PRIVATE framework.h)

set_target_properties(draw2d_quartz2d PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(draw2d_quartz2d PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_quartz2d PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_quartz2d PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/draw2d_quartz2d.lib")
    target_link_options(draw2d_quartz2d PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/draw2d_quartz2d.def")
    target_link_libraries(draw2d_quartz2d PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(draw2d_quartz2d PRIVATE -fpermissive)
    target_compile_options(draw2d_quartz2d PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(draw2d_quartz2d PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(draw2d_quartz2d PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(draw2d_quartz2d PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(draw2d_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(draw2d_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(draw2d_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(draw2d_quartz2d PRIVATE _draw2d_quartz2d_LIBRARY)



