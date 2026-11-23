cmake_minimum_required(VERSION 4.4)
project(bignumber LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "Personal Extended Precision Library")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "$ENV{HOME}" CACHE PATH "Install prefix" FORCE)
    list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}")
endif()
# Keep the RPATH to external shared libraries (e.g. ~/lib/libbignumber.dylib) in installed binaries.
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include(CTest)

option(BIGNUMBER_WARNINGS "Compile with -Wall -Wextra -Wshadow -Wconversion" ON)
if(BIGNUMBER_WARNINGS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion)
endif()

add_library(bignumber SHARED
        src/array.cpp
        include/bignumber/array.hpp)
target_include_directories(bignumber PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/bignumber>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/bignumber>)
target_compile_options(bignumber PRIVATE -fvisibility=hidden)

include(GenerateExportHeader)
generate_export_header(bignumber
        EXPORT_MACRO_NAME BIGNUMBER_API
        EXPORT_FILE_NAME bignumber/bignumber_export.h)


set_target_properties(bignumber PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/bignumber/array.hpp)
set_target_properties(bignumber PROPERTIES PUBLIC_HEADER "${HEADERS};${CMAKE_CURRENT_BINARY_DIR}/bignumber/bignumber_export.h")


install(TARGETS ${PROJECT_NAME} EXPORT bignumber
        ARCHIVE  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME  DESTINATION "${CMAKE_INSTALL_BINDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/bignumber")
install(EXPORT bignumber NAMESPACE bignumber:: DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/bignumber")
export(TARGETS ${PROJECT_NAME} NAMESPACE bignumber:: FILE bignumber.cmake)

if(BUILD_TESTING AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
    add_subdirectory(test)
endif()


include(CPack)
