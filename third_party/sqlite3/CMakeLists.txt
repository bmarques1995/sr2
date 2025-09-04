cmake_minimum_required(VERSION 3.22)

add_library(sqlite3 STATIC sqlite3.c)
target_include_directories(sqlite3 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)

set_cxx_project_standards(sqlite3 17 TRUE)
target_installation_behaviour(
	CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/config.cmake.in
	TARGET_NAME sqlite3
	VERSION ${PROJECT_VERSION}
    COMPONENT "sqlite3"
	PROJECT_NAME ${PROJECT_NAME}
	NAMESPACE "sr2"
	HEADER_INPUT ${CMAKE_CURRENT_SOURCE_DIR}
	HEADER_OUTPUT include/)