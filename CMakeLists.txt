cmake_minimum_required (VERSION 2.8.10)
project(ABBtD CXX C)

#DEPENDENCIES
#x11 xrandr OpenGL UDev GLEW JPEG FreeType OpenAL SNDFile SFML Thor tgui
#
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/resources)
set(PROJECT_LOGO ${RESOURCE_DIR}/logo.png)
set(PROJECT_MAJOR_VERSION 0)
set(PROJECT_MINOR_VERSION 1)
set(CMAKE_MODULE_PATH 
	${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/Modules
)

if(WIN32)
	set(TGUI_INCLUDE_DIR "$ENV{PROGRAMFILES(x86)}/tgui/include")
	set(TGUI_LIBRARY "$ENV{PROGRAMFILES(x86)}/tgui/lib/tgui-d.lib")
	set(SFML_ROOT "$ENV{PROGRAMFILES(x86)}/SFML" CACHE PATH "path to sfml")
	set(THOR_ROOT "$ENV{PROGRAMFILES(x86)}/thor" CACHE PATH "path to thor")
	set(TGUI_ROOT "$ENV{PROGRAMFILES(x86)}/tgui" CACHE PATH "path to tgui")
else()
	set(TGUI_INCLUDE_DIR /usr/local/include/TGUI/)
	set(TGUI_LIBRARY /usr/local/lib/libtgui.so)
endif(WIN32)
find_package(SFML 2.1 COMPONENTS system window audio graphics REQUIRED)
find_package(Thor REQUIRED)
find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_subdirectory(doc)
else ()
  message(STATUS "Doxygen was not found. No documentation can be created")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
#-----------------------------------------------------
configure_file (
  "${PROJECT_SOURCE_DIR}/include/resources.h.in"
  "${PROJECT_SOURCE_DIR}/include/Resources.h"
  )
#-----------------------------------------------------

set(SOURCES 
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/Game.cpp
	${PROJECT_SOURCE_DIR}/src/Form.cpp
	${PROJECT_SOURCE_DIR}/src/ResourceHandler.cpp
	${PROJECT_SOURCE_DIR}/src/Player.cpp
	${PROJECT_SOURCE_DIR}/src/InputHandler.cpp
	${PROJECT_SOURCE_DIR}/src/Physics.cpp
)
set(HEADERS 
	${PROJECT_SOURCE_DIR}/include/Game.hpp
	${PROJECT_SOURCE_DIR}/include/Resources.h
	${PROJECT_SOURCE_DIR}/include/Form.hpp
	${PROJECT_SOURCE_DIR}/include/ResourceHandler.hpp
	${PROJECT_SOURCE_DIR}/include/Player.hpp
	${PROJECT_SOURCE_DIR}/include/InputHandler.hpp
	${PROJECT_SOURCE_DIR}/include/Physics.hpp
)

#message(STATUS "TGUI_INCLUDE_DIR ${TGUI_INCLUDE_DIR}")
#message(STATUS "TGUI_LIBRARY ${TGUI_LIBRARY}")

if(NOT MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif(NOT MSVC)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "build type")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG") #allows text on screen
if(NOT MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg") #allows profiling
endif()

include_directories(${SFML_INCLUDE_DIR} ${THOR_INCLUDE_DIR} ${TGUI_INCLUDE_DIR}) 
add_executable(ABBtD ${SOURCES} ${HEADERS})
target_link_libraries(ABBtD ${SFML_LIBRARIES} ${THOR_LIBRARY} ${TGUI_LIBRARY})
