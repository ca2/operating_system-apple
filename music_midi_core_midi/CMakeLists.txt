cmake_minimum_required(VERSION 3.17)
project(music_midi_core_midi CXX)


list(APPEND library_source
        _.cpp
        _.h
        _music_midi_core_midi.h
        #database.cpp
        #database.h
        factory_exchange.cpp
        factory_exchange.h
        #framework.cpp
        #framework.h
)

list(APPEND library_references
   acme apex aqua aura axis)

add_library(music_midi_core_midi SHARED ${library_source})

target_precompile_headers(music_midi_core_midi PRIVATE framework.h)

set_target_properties(music_midi_core_midi PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(music_midi_core_midi PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(music_midi_core_midi PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(music_midi_core_midi PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/music_midi_core_midi.lib")
    target_link_options(music_midi_core_midi PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/music_midi_core_midi.def")
    target_link_libraries(music_midi_core_midi PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(music_midi_core_midi PRIVATE -fpermissive)
    target_compile_options(music_midi_core_midi PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(music_midi_core_midi PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(music_midi_core_midi PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(music_midi_core_midi PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(music_midi_core_midi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(music_midi_core_midi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(music_midi_core_midi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(music_midi_core_midi PRIVATE _music_midi_core_midi_LIBRARY)



