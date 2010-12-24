#Config file
include(../config.cmake)
configure_file(config.h.cmake config.h)

### Commons includes ###
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/templates
    ${PROJECT_SOURCE_DIR}/src/io
    ${PROJECT_SOURCE_DIR}/src/exceptions
    ${PROJECT_SOURCE_DIR}/src/gestures
    ${PROJECT_SOURCE_DIR}/src/action
    ${PROJECT_SOURCE_DIR}/src/events
    ${PROJECT_SOURCE_DIR}/src/python
    ${PROJECT_SOURCE_DIR}/src/utils 
	)

set(LIBRARIES)

### OpenCV support ###
FIND_PACKAGE(OpenCV REQUIRED)
if(OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})
	set(LIBRARIES "${LIBRARIES}" "${OpenCV_LIBS}")
endif()

### Boost support ###
FIND_PACKAGE(Boost COMPONENTS regex program_options python REQUIRED)
# SET(Boost_ADDITIONAL_VERSIONS "1.78" "1.78.0" "1.79" "1.79.0")
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	if(NTS_COMPILE_ON_LINUX)
		set(LIBRARIES "${LIBRARIES}" "${Boost_LIBRARIES}")
	endif()
	if(NTS_COMPILE_ON_WINDOWS)
		link_directories(${Boost_LIBRARY_DIR})
	endif()
endif()

### LUA Support ###
#find_package(Lua51 REQUIRED)
#if(Boost_FOUND)
#	include_directories(${Lua51_INCLUDE_DIRS})
#	set(LIBRARIES "${LIBRARIES}" "${Lua51_LIBRARIES}")
#endif()

### Python Support ###
find_package(PythonLibs REQUIRED)
if(PYTHONLIBS_FOUND)
	include_directories(${PYTHON_INCLUDE_DIRS})
	set(LIBRARIES "${LIBRARIES}" "${PYTHON_LIBRARIES}")
endif()

### X11 support ###
if(NTS_COMPILE_ON_LINUX)
	find_package(X11 REQUIRED)
	if(X11_FOUND AND X11_XTest_FOUND)
		include_directories(${X11_INCLUDE_DIRS} ${X11_XTest_INCLUDE_PATH})
		set(LIBRARIES ${LIBRARIES} ${X11_LIBRARIES} ${X11_XTest_LIB})
	else()
		message("Required library X11 not found. Please install xorg, xorg-test and the corresponding dev packages.")
	endif()
endif()

### Common source files ###
file(GLOB SOURCES_FILES
		NoTouchScreen.cpp
		exceptions/*.cpp
		io/*.cpp
		gestures/*.cpp
		action/*.cpp
		events/*.cpp
		python/*.cpp
		)

### Platform dependent implementations ###
if(NTS_COMPILE_ON_WINDOWS)
    include_directories(${notouchscreen_SOURCE_DIR}/src/io/windows)
    file(GLOB WINDOWS_SRCS_FILES
		io/windows/*.cpp
		)
    set(SOURCES_FILES ${SOURCES_FILES} ${WINDOWS_SRCS_FILES})
endif()

if(NTS_COMPILE_ON_LINUX)
    include_directories(${notouchscreen_SOURCE_DIR}/src/io/linux)
    file(GLOB LINUX_SRCS_FILES
		io/linux/*.cpp
		)
    set(SOURCES_FILES ${SOURCES_FILES} ${LINUX_SRCS_FILES})
endif()

### Linking ###
add_executable(${PROJECT_NAME} Main.cpp ${SOURCES_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
