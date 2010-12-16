cmake_minimum_required (VERSION 2.6)
include(CheckIncludeFileCXX)

project (notouchscreen)

set(CMAKE_VERBOSE_MAKEFILE OFF)

# Making more readable error messages in eclipse
if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif(CMAKE_COMPILER_IS_GNUCC)
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif(CMAKE_COMPILER_IS_GNUCXX)


# Centralized version number
include (version.cmake)
message (STATUS "*** Building opencvtest ${opencvtest_VERSION} ***")

# Main source directory
add_subdirectory (src)

