cmake_minimum_required(VERSION 3.2)

project(NumStr)

#set(CMAKE_CXX_STANDARD 11)
option(CODELITE_GENERATION
       "Generate codelite project files."
       OFF)

IF(CODELITE_GENERATION)
  set(CMAKE_GENERATOR "CodeLite - MinGW Makefiles" CACHE INTERNAL "" FORCE)
  message("generator is set to ${CMAKE_GENERATOR}")
endif(CODELITE_GENERATION)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(NUMSTR_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(NUMSTR_INSTALL_RUN_DIR ${PROJECT_SOURCE_DIR}/run)
set(NUMSTR_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/run/)

add_subdirectory(src)


