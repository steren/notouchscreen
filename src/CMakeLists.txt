#Config file
include(../config.cmake)
configure_file(config.h.cmake config.h)

include_directories(
    ${notouchscreen_SOURCE_DIR}/src
    ${notouchscreen_BINARY_DIR}/src 
    ${notouchscreen_SOURCE_DIR}/src/templates
    ${notouchscreen_SOURCE_DIR}/src/io
    ${notouchscreen_SOURCE_DIR}/src/exceptions 
	)

set(ADDITIONAL_LIBRARIES)

### OpenCV support ###
FIND_PACKAGE(OpenCV REQUIRED)
if(OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})
	set(LIBRARIES "${LIBRARIES}" "${OpenCV_LIBS}")
endif()

### X11 support ###
if(NTS_COMPILE_ON_LINUX)
	find_package(X11 REQUIRED)
	if(X11_FOUND)
		include_directories(${X11_INCLUDE_DIRS} ${X11_XTest_INCLUDE_PATH})
		set(LIBRARIES ${LIBRARIES} ${X11_LIBRARIES} ${X11_XTest_LIB})
	endif()	
endif()

	
file(GLOB SRCS_FILES
		NoTouchScreen.cpp
		exceptions/*.cpp
		io/*.cpp 
		)

add_executable(${PROJECT_NAME} Main.cpp ${SRCS_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

file(GLOB KEY_STROKER_SRCS_FILES
		KeyStrokerMain.cpp
		exceptions/*.cpp 
		io/*.cpp 
		)

add_executable(${PROJECT_NAME}_stroker KeyStrokerMain.cpp ${KEY_STROKER_SRCS_FILES})
target_link_libraries(${PROJECT_NAME}_stroker ${LIBRARIES}) 

