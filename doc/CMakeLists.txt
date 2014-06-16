
if(WIN32)
	set(GRAPHVIZ_ROOT "$ENV{PROGRAMFILES(x86)}/Graphviz2.38" CACHE PATH "path to graphviz")
else()
	set(GRAPHVIZ_ROOT "$ENV{PATH}" CACHE PATH "path to graphviz")
endif(WIN32)

find_package(Graphviz)
find_package(LATEX)
if(LATEX_COMPILER)
	set(HAVE_LATEX "YES")
        message(STATUS "LATEX compiler found at ${LATEX_COMPILER}")
else()
	set(HAVE_LATEX "NO")
endif()
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/doc)
set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/doxyfile)
if(WIN32)
	set(HAVE_DOT "NO")
else()
	set(HAVE_DOT "YES")
endif(WIN32)
configure_file(${DOXYGEN_INPUT_DIR}/doc/doxyfile.in ${DOXYGEN_CONFIGURED_INPUT} @ONLY)
add_custom_target(doc ALL
                  COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
                  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
                  COMMAND ${CMAKE_COMMAND} -E echo "Done."
                  WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR})
install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
        DESTINATION ${INSTALL_MISC_DIR}/doc
        COMPONENT doc)