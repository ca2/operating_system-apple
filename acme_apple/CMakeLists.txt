cmake_minimum_required(VERSION 3.17)
project(acme_apple CXX)


list(APPEND library_source
   _.cpp
   _.h
   _acme_apple.h
   _apple.mm
        _c_mm.h
        _mm.h
        _mm_common.h
        apple_timer.cpp
        DDInvocationGrabber.h
        DDInvocationGrabber.mm
        debug.cpp
   factory_exchange.cpp
   framework.cpp
   framework.h
        image.mm
   node.cpp
   node.h
        NSObject+DDExtensions.h
        NSObject+DDExtensions.mm
        NSString+SymlinksAndAliases.h
        NSString+SymlinksAndAliases.mm
        resource.cpp
        timer.mm
        translator.cpp
        translator.h
        UncaughtExceptionHandler.h
        UncaughtExceptionHandler.mm
   )


add_library(acme_apple SHARED ${library_source})

list(APPEND library_references acme)


target_precompile_headers(acme_apple PRIVATE framework.h)


set_target_properties(acme_apple PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(acme_apple PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(acme_apple PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(acme_apple PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(acme_apple PRIVATE ${library_references})
   add_dependencies(acme_apple draw2d_gdiplus)
elseif (LINUX)
   target_compile_options(acme_apple PRIVATE -fpermissive)
   target_compile_options(acme_apple PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(acme_apple PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(acme_apple PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
   target_link_options(acme_apple PRIVATE -Wl,-z,defs)
endif ()


target_include_directories(acme_apple PRIVATE .)
target_include_directories(acme_apple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(acme_apple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(acme_apple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(acme_apple PRIVATE _acme_apple_LIBRARY)



