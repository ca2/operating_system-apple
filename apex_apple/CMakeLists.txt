cmake_minimum_required(VERSION 3.17)
project(apex_apple CXX OBJCXX)


#include(../../../objc++.cmake)


list(APPEND library_source
        _.cpp
   _.h
        _apex_apple.h
        _apple.mm
        _c_mm.h
        _mm.h
        _mm_common.h
   datetime.cpp
   datetime.h
   factory_exchange.cpp
   file_context.cpp
   file_context.h
   framework.cpp
   framework.h
   node.cpp
   node.h
        process.cpp
        process.h
   system_color.cpp
   system_time.cpp
        timer.mm
        user.cpp
        user.h
   )


list(APPEND library_references acme acme_posix apex)


add_library(apex_apple SHARED ${library_source})

target_precompile_headers(apex_apple PRIVATE framework.h)

set_target_properties(apex_apple PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(apex_apple PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(apex_apple PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(apex_apple PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(apex_apple PRIVATE ${library_references})
   add_dependencies(apex_apple draw2d_gdiplus)
elseif (LINUX)
   target_compile_options(apex_apple PRIVATE -fpermissive)
   target_compile_options(apex_apple PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(apex_apple PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(apex_apple PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   #target_link_libraries(apex_apple PRIVATE asound)
   target_link_options(apex_apple PRIVATE -Wl,-z,defs)
endif ()


target_include_directories(apex_apple PRIVATE .)
target_include_directories(apex_apple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(apex_apple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(apex_apple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(apex_apple PRIVATE _apex_apple_LIBRARY)



