cmake_minimum_required(VERSION 2.8)

project(metadepend)

include_directories(include/)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

file(
	GLOB_RECURSE
	header_files
	include/*
)

file(
	GLOB_RECURSE
	source_files
	src/*
)

SET(CMAKE_CXX_FLAGS "-std=c++14")

add_executable(
	test
	${header_files}
	${source_files}
)