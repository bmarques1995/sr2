# CMakeList.txt: projeto de CMake para QtSample, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.
cmake_minimum_required(VERSION 3.22)

macro(add_version_file OUTPUT_FILE)
	file(READ ${CMAKE_CURRENT_SOURCE_DIR}/src/Version.cxx.in SOURCE_CONTENTS)
	string(REGEX REPLACE SR2_MAJOR "${PROJECT_VERSION_MAJOR}" OUTPUT_SOURCE ${SOURCE_CONTENTS})
	string(REGEX REPLACE SR2_MINOR "${PROJECT_VERSION_MINOR}" OUTPUT_SOURCE ${OUTPUT_SOURCE})
	string(REGEX REPLACE SR2_PATCH "${PROJECT_VERSION_PATCH}" OUTPUT_SOURCE ${OUTPUT_SOURCE})
	file(WRITE ${OUTPUT_FILE} ${OUTPUT_SOURCE})
endmacro()

set(TARGET_NAME sr2)

add_version_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Version.cpp)
file(GLOB_RECURSE SAMPLE_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")
file(GLOB_RECURSE SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")

add_executable(${TARGET_NAME} ${SAMPLE_HDRS} ${SAMPLE_SRCS})
target_include_directories(${TARGET_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)