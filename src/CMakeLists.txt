include_directories(
    ${notouchscreen_SOURCE_DIR}/src 
    ${notouchscreen_SOURCE_DIR}/src/templates 
    ${notouchscreen_BINARY_DIR}/src
	)

set(ADDITIONAL_LIBRARIES)

### OpenCV support ###
include(FindPkgConfig)
pkg_search_module(OPENCV opencv)
if(OPENCV_FOUND)
	include_directories(${OPENCV_INCLUDEDIR})
else()
	FIND_PACKAGE(OpenCV REQUIRED)
	include_directories(${OpenCV_INCLUDE_DIRS})
	set(ADDITIONAL_LIBRARIES ${OpenCV_LIBS})
	message(${OpenCV_INCLUDE_DIRS})
endif()
						
file(GLOB SRCS_FILES 
		*.cpp 
		)

add_executable(${PROJECT_NAME} Main.cpp ${SRCS_FILES}) 
# install(TARGETS freebalance DESTINATION ./)

### Linking ###
target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBRARIES} ${ADDITIONAL_LIBRARIES})
