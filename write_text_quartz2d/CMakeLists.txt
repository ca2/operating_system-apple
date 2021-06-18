cmake_minimum_required(VERSION 3.17)
project(write_text_quartz2d CXX)



list(APPEND library_references
        acme
        apex
        aqua
        aura)


list(APPEND library_source
        _.cpp
        _.h
        factory_exchange.cpp
        font_enumeration.cpp
        font_enumeration.h
        font_enumeration.mm
        fonts.cpp
        fonts.h
        framework.cpp
        framework.h
        write_text.cpp
        write_text.h)




add_library(write_text_quartz2d SHARED ${library_source})

target_precompile_headers(write_text_quartz2d PRIVATE framework.h)

set_target_properties(write_text_quartz2d PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(write_text_quartz2d PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_quartz2d PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_quartz2d PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/write_text_quartz2d.lib")
    target_link_options(write_text_quartz2d PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/write_text_quartz2d.def")
    target_link_libraries(write_text_quartz2d PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG pangocairo)
    target_compile_options(write_text_quartz2d PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(write_text_quartz2d PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(write_text_quartz2d PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(write_text_quartz2d PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
elseif(MACOS)
    target_compile_options(write_text_quartz2d PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(write_text_quartz2d PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(write_text_quartz2d PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(write_text_quartz2d PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


#add_dependencies(write_text_quartz2d ${app_common_dependencies} )


target_link_directories(write_text_quartz2d PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(write_text_quartz2d PRIVATE $ENV{HOME}/__config)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(write_text_quartz2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(write_text_quartz2d PRIVATE _write_text_quartz2d_LIBRARY)
target_compile_definitions(write_text_quartz2d PRIVATE UNICODE)
target_compile_definitions(write_text_quartz2d PRIVATE _UNICODE)



