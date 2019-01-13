cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_VERSION "0.1.0")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(LIBS "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LOGGING "${SRC}/modules/logging")
set(DIST "${CMAKE_CURRENT_SOURCE_DIR}/dist")

project (poli VERSION ${PROJECT_VERSION} LANGUAGES CXX)

add_library(logging SHARED)

target_include_directories(logging
PUBLIC
	$<BUILD_INTERFACE:${LOGGING}>
	$<BUILD_INTERFACE:${LIBS}/spdlog/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
PRIVATE
  ${SRC}
)
add_subdirectory("${LIBS}/spdlog")

set_target_properties(logging
PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION}
	CXX_VISIBILITY_PRESET hidden
	VISIBILITY_INLINES_HIDDEN 1
)

target_sources(logging 
PRIVATE
    ${LOGGING}/log.h
    ${LOGGING}/log.cpp
)

include(GenerateExportHeader)
generate_export_header(logging)

# Compiler-specific compile flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message(STATUS "Setting G++ flags")
    # G++
    target_compile_options(logging PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message(STATUS "Setting MSVC flags")
    # MSVC
    target_compile_options(logging PRIVATE /EHsc /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(logging  PRIVATE WIN_EXPORT)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(STATUS "Setting Clang flags")
    # Activate all clang warnings except those that don't really affect much
    target_compile_options(logging PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
endif()

add_executable (poli src/main.cpp)
target_link_libraries(poli logging)

set_target_properties(poli logging
PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${DIST}/lib
	LIBRARY_OUTPUT_DIRECTORY ${DIST}/lib
	RUNTIME_OUTPUT_DIRECTORY ${DIST}/bin
)

if (WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT poli)
endif()