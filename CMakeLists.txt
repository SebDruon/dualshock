### CMake file for dualshock 
###
###     Author : seb@codices.org
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

project (dualshock)
set (dualshock_VERSION_MAJOR 0)
set (dualshock_VERSION_MINOR 1)
set (dualshock_VERSION_PATCH 0)
set (dualshock_VERSION_STRING
	${dualshock_VERSION_MAJOR}.${dualshock_VERSION_MINOR}.${dualshock_VERSION_PATCH} )

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH /usr/local/bin )
set ( INSTALL_LIB_PATH /usr/local/lib )
set ( INSTALL_AR_PATH  /usr/local/lib )
set ( INSTALL_HEADERS_PATH /usr/local/include )

# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR)
        set(var INSTALL_${p}_PATH)
        if(NOT IS_ABSOLUTE "${${var}}")
                set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
        endif()
endforeach()

### Config File

configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in" 
			     "${PROJECT_SOURCE_DIR}/src/config.h" )

### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	                 "${CMAKE_CURRENT_BINARY_DIR}" 
                     ) 

### File lists

file( GLOB src  "src/*.c" )
file( GLOB hdr  "include/*.h"  )

### Targets

add_library( "dualshock" SHARED ${src} ) 

set_target_properties(dualshock PROPERTIES VERSION ${dualshock_VERSION_STRING}
                                    SOVERSION ${dualshock_VERSION_MAJOR})

### Cmake file

configure_file(dualshockConfig.cmake.in "${PROJECT_BINARY_DIR}/dualshockConfig.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/dualshockConfig.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/dualshock" COMPONENT dev )  

### Install 

install( TARGETS "dualshock"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
	    ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main ) 

install( FILES ${hdr}
	    DESTINATION ${INSTALL_HEADERS_PATH}/dualshock/${name} 
	    COMPONENT main )

