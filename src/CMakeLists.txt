include_directories(
    ${opencvtest}_SOURCE_DIR}/src 
    ${opencvtest}_BINARY_DIR}/src
	)

set(ADDITIONAL_LIBRARIES)

### OpenCV support ###
include(FindPkgConfig)
pkg_search_module(OPENCV REQUIRED opencv)
if(OPENCV_FOUND)
	include_directories(${OPENCV_INCLUDEDIR})
endif()
						
file(GLOB SRCS_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SRCS_FILES}) 
# install(TARGETS freebalance DESTINATION ./)

### Linking ###
target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBRARIES} ${ADDITIONAL_LIBRARIES})