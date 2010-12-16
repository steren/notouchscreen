include_directories(
    ${notouchscreen_SOURCE_DIR}/src 
    ${notouchscreen_SOURCE_DIR}/src/models
    ${notouchscreen_SOURCE_DIR}/src/descriptors
    ${notouchscreen_SOURCE_DIR}/src/templates 
    ${notouchscreen_BINARY_DIR}/src
	)

set(ADDITIONAL_LIBRARIES)

### OpenCV support ###
include(FindPkgConfig)
pkg_search_module(OPENCV REQUIRED opencv)
if(OPENCV_FOUND)
	include_directories(${OPENCV_INCLUDEDIR})
endif()
						
file(GLOB SRCS_FILES 
		*.cpp 
		models/*.cpp
		src/descriptors/*.cpp
		)

add_executable(${PROJECT_NAME} Main.cpp ${SRCS_FILES}) 
# install(TARGETS freebalance DESTINATION ./)

### Linking ###
target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBRARIES} ${ADDITIONAL_LIBRARIES})
