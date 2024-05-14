cmake_minimum_required(VERSION 3.17)
project(audio_core_audio CXX)


list(APPEND library_source
        _.h
        aligned.cpp
        aligned.h
        aligned_pointer.cpp
        aligned_pointer.h
        command.h
        _factory.cpp
        factory_exchange.h
        framework.cpp
        framework.h
        toolbox.cpp
        toolbox.h
        translation.cpp
        translation.h
        wave_in.cpp
        wave_in.h
        wave_out.cpp
        wave_out.h
)

list(APPEND library_references
   acme apex aqua aura axis)

add_library(audio_core_audio SHARED ${library_source})

target_precompile_headers(audio_core_audio PRIVATE framework.h)

set_target_properties(audio_core_audio PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(audio_core_audio PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(audio_core_audio PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(audio_core_audio PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/audio_core_audio.lib")
    target_link_options(audio_core_audio PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/audio_core_audio.def")
    target_link_libraries(audio_core_audio PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(audio_core_audio PRIVATE -fpermissive)
    target_compile_options(audio_core_audio PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(audio_core_audio PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(audio_core_audio PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(audio_core_audio PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(audio_core_audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(audio_core_audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(audio_core_audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(audio_core_audio PRIVATE _audio_core_audio_LIBRARY)



