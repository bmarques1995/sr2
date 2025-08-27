# CMakeList.txt: projeto de CMake para QtSample, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.
cmake_minimum_required(VERSION 3.22)

set(TARGET_NAME sr2)

file(GLOB_RECURSE SAMPLE_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")
file(GLOB_RECURSE SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")

add_executable(${TARGET_NAME} ${SAMPLE_HDRS} ${SAMPLE_SRCS})
target_include_directories(${TARGET_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)