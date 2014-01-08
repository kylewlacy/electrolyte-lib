cmake_minimum_required(VERSION 2.8)

project(Electrolyte)



include_directories(${CMAKE_INSTALL_PREFIX}/include)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -fexceptions -Wall -pedantic")
list(APPEND CMAKE_SHARED_LINKER_FLAGS "-stdlib=libc++")

if(CMAKE_GENERATOR MATCHES "Xcode")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif()



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB ELECTROLYTE_LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB ELECTROLYTE_LIB_INC ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(electrolyte_lib STATIC ${ELECTROLYTE_LIB_SRC} ${ELECTROLYTE_LIB_INC})

file(GLOB ELECTROLYTE_LIB_TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
add_executable(electrolyte_test ${ELECTROLYTE_LIB_TEST})
target_link_libraries(electrolyte_test electrolyte_lib)
