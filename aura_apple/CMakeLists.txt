cmake_minimum_required(VERSION 3.17)
project(aura_apple CXX)


list(APPEND library_source
   _.cpp
   _.h
   _aura_apple.h
        _mm.h
   factory_exchange.cpp
   factory_exchange.h
   framework.cpp
   framework.h
   node.cpp
   node.h
        user.h

   )


list(APPEND library_references
   acme
   acme_posix
   apex
   apex_posix
   aqua
   aura
   )


add_library(aura_apple SHARED ${library_source})

target_precompile_headers(aura_apple PRIVATE framework.h)

set_target_properties(aura_apple PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(aura_apple PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(aura_apple PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(aura_apple PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(aura_apple PRIVATE ${library_references})


elseif (LINUX)


   pkg_check_modules(PKGCONFIG x11 x11-xcb)
   target_compile_options(aura_apple PRIVATE -fpermissive)
   target_compile_options(aura_apple PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(aura_apple PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(aura_apple PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(aura_apple PRIVATE -Wl,-z,defs)


endif ()




target_include_directories(aura_apple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(aura_apple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(aura_apple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(aura_apple PRIVATE _aura_apple_LIBRARY)
