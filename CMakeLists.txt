# GLT BUILD OPTIONS

#ADD_DEFINITIONS(-DGLT_UNICODE)

# CMAKE BUILD OPTIONS

SET(CMAKE_VERBOSE_MAKEFILE 0)
SET(CMAKE_COLOR_MAKEFILE 1)

#SET(CMAKE_BUILD_TYPE DEBUG)
#SET(CMAKE_BUILD_TYPE RELEASE)

# gcc-specific

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

# Windows Visual Studio specific

IF (WIN32)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF (WIN32)

##############

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.7 FATAL_ERROR)

if (COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif (COMMAND cmake_policy)
    
SET(ROOT ${CMAKE_SOURCE_DIR})
INCLUDE_DIRECTORIES(${ROOT}/src)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#LINK_DIRECTORIES(${ROOT}/lib)

################ Dependencies

# OpenGL

INCLUDE (${CMAKE_ROOT}/Modules/FindOpenGL.cmake)
IF (OPENGL_FOUND)
    SET(OPENGL_LIBRARIES GLEW ${OPENGL_LIBRARIES})
    MESSAGE(STATUS " OpenGL detected: ${OPENGL_LIBRARIES}" )
ELSE (OPENGL_FOUND)
    MESSAGE(ERROR " OpenGL not detected")
ENDIF (OPENGL_FOUND)

# Detect local freeglut, GLUT or system GLUT

#IF (EXISTS src/freeglut)
#    ADD_DEFINITIONS(-DGLUTM_FREEGLUT)
#    IF (WIN32)
#        ADD_DEFINITIONS(-DFREEGLUT_STATIC)
#    ENDIF (WIN32)
#    SET(GLUT_LIBRARIES freeglut ${OPENGL_LIBRARIES})
#   MESSAGE(STATUS " GLUT detected: ${GLUT_LIBRARIES}")
#ENDIF (EXISTS src/freeglut)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
ELSE (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    IF (EXISTS src/glut)
        ADD_DEFINITIONS(-DGLUTM_GLUT)
        IF (WIN32)
            ADD_DEFINITIONS(-DGLUT_NO_LIB_PRAGMA)
            SET(GLUT_LIBRARIES glut ${OPENGL_LIBRARIES})
            SET(GLUT_LIBRARIES ${GLUT_LIBRARIES} winmm ws2_32 gdi32)
        ELSE (WIN32)
        SET(GLUT_LIBRARIES glut Xmu ${OPENGL_LIBRARIES})
        ENDIF (WIN32)
    ENDIF (EXISTS src/glut)
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF (GLUT_LIBRARIES)
ELSE (GLUT_LIBRARIES)
   INCLUDE (${CMAKE_ROOT}/Modules/FindGLUT.cmake)
   IF (GLUT_FOUND)
       ADD_DEFINITIONS(-DGLUTM_GLUT)
       SET(GLUT_LIBRARIES ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
   ELSE (GLUT_FOUND)
        MESSAGE(ERROR " GLT depends on GLUT or freeglut.")
   ENDIF (GLUT_FOUND)
ENDIF(GLUT_LIBRARIES)

MESSAGE(STATUS " GLUT detected: ${GLUT_LIBRARIES}")

# GLUI

IF (EXISTS ${ROOT}/src/glui)
    SET(GLUI_LIBRARIES glui ${GLUT_LIBRARIES})
    MESSAGE(STATUS " GLUI detected: ${GLUI_LIBRARIES}")
ELSE (EXISTS ${ROOT}/src/glui)
    MESSAGE(STATUS " not using glui.")
ENDIF (EXISTS ${ROOT}/src/glui)

# ZLIB

IF (EXISTS ${ROOT}/src/zlib)
    ADD_SUBDIRECTORY(${ROOT}/src/zlib)
    ADD_DEFINITIONS(-DGLT_ZLIB)
    INCLUDE_DIRECTORIES(${ROOT}/src/zlib)
    SET(ZLIB_FOUND 1)
    SET(ZLIB_LIBRARIES z)
    MESSAGE(STATUS " ZLIB detected: ${ZLIB_LIBRARIES}")
ELSE (EXISTS ${ROOT}/src/zlib)
    INCLUDE (${CMAKE_ROOT}/Modules/FindZLIB.cmake)
    IF (ZLIB_FOUND)
        ADD_DEFINITIONS(-DGLT_ZLIB)
        MESSAGE(STATUS " ZLIB detected: ${ZLIB_LIBRARIES}")
    ELSE (ZLIB_FOUND)
        MESSAGE(ERROR " GLT depends on zlib.")
    ENDIF (ZLIB_FOUND)
ENDIF (EXISTS ${ROOT}/src/zlib)

# PNG

IF (EXISTS ${ROOT}/src/png)
    ADD_SUBDIRECTORY(${ROOT}/src/png)
    ADD_DEFINITIONS(-DGLT_PNG)
    INCLUDE_DIRECTORIES(${ROOT}/src/png)
    SET(PNG_LIBRARIES png ${ZLIB_LIBRARIES})
    MESSAGE(STATUS " PNG detected: ${PNG_LIBRARIES}")
ELSE (EXISTS ${ROOT}/src/png)
    INCLUDE (${CMAKE_ROOT}/Modules/FindPNG.cmake)
    IF (PNG_FOUND)
        ADD_DEFINITIONS(-DGLT_PNG)
        MESSAGE(STATUS " PNG detected: ${PNG_LIBRARIES}")
    ELSE (PNG_FOUND)
        MESSAGE(STATUS " PNG not found.")
    ENDIF (PNG_FOUND)
ENDIF (EXISTS ${ROOT}/src/png)

# PTYPES

IF (EXISTS ${ROOT}/src/ptypes)
    ADD_SUBDIRECTORY(src/ptypes)
    SET(PTYPES_FOUND 1)
    SET(PTYPES_LIBRARIES ptypes)
    MESSAGE(STATUS " PTYPES detected: ${PTYPES_LIBRARIES}")
ELSE (EXISTS ${ROOT}/src/ptypes)
    SET(PTYPES_FOUND 0)
    MESSAGE(STATUS " PTYPES not found.")
ENDIF (EXISTS ${ROOT}/src/ptypes)

# JPG

IF (EXISTS ${ROOT}/src/jpeg)
    ADD_SUBDIRECTORY(${ROOT}/src/jpeg)
    ADD_DEFINITIONS(-DGLT_JPEG)
    INCLUDE_DIRECTORIES(${ROOT}/src/jpeg)
    SET(JPEG_LIBRARIES jpeg)
    MESSAGE(STATUS " JPEG detected: ${JPEG_LIBRARIES}")
ELSE (EXISTS ${ROOT}/src/jpeg)
    SET(JPEG_FIND_QUIETLY 1)
    INCLUDE (${CMAKE_ROOT}/Modules/FindJPEG.cmake)
    IF (JPEG_FOUND)
        ADD_DEFINITIONS(-DGLT_JPEG)
        MESSAGE(STATUS " JPEG detected: ${JPEG_LIBRARIES}")
    ELSE (JPEG_FOUND)
        MESSAGE(STATUS " JPEG not found.")
    ENDIF (JPEG_FOUND)
ENDIF (EXISTS ${ROOT}/src/jpeg)

# QT4

SET(Qt4_FIND_QUIETLY 1)
INCLUDE (${CMAKE_ROOT}/Modules/FindQt4.cmake)
IF (QT4_FOUND)
    SET(QT_USE_QTOPENGL TRUE)
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(-DGLT_QT4)
    MESSAGE(STATUS " Qt4 detected: ${QT_LIBRARIES}")
ELSE (QT4_FOUND)
    MESSAGE(STATUS " Qt4 not found.")
ENDIF (QT4_FOUND)

#######################################################################

FILE(GLOB SOURCES . 
src/glt/*.cpp 
src/math/*.cpp 
src/mesh/*.cpp 
src/fonts/*.cpp 
src/glutm/*.cpp 
src/node/*.cpp 
src/network/*.cpp 
src/misc/*.cpp
src/misc/internal/lzf_*.c)
ADD_LIBRARY(glt ${SOURCES})

SET(GLT_LINK_LIBRARIES glt)
SET(GLT_LINK_LIBRARIES ${GLT_LINK_LIBRARIES} ${PNG_LIBRARIES} ${ZLIB_LIBRARIES} ${JPEG_LIBRARIES})
SET(GLT_LINK_LIBRARIES ${GLT_LINK_LIBRARIES} ${GLUT_LIBRARIES})

IF (PTYPES_FOUND)
    SET(GLT_LINK_LIBRARIES ${GLT_LINK_LIBRARIES} ${PTYPES_LIBRARIES})
ENDIF (PTYPES_FOUND)

IF (WIN32)
ELSE (WIN32)
  INCLUDE (${CMAKE_ROOT}/Modules/FindThreads.cmake)
  IF (CMAKE_HAVE_THREADS_LIBRARY)
      MESSAGE(STATUS " pthreads detected: ${CMAKE_THREAD_LIBS_INIT}")
  ELSE (CMAKE_HAVE_THREADS_LIBRARY)
      MESSAGE(STATUS " pthreads not found.")
  ENDIF (CMAKE_HAVE_THREADS_LIBRARY)

    SET(GLT_LINK_LIBRARIES ${GLT_LINK_LIBRARIES} ${MATH_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
ENDIF (WIN32)

#######################################################################

#IF (EXISTS src/unifont)
#    ADD_SUBDIRECTORY(src/unifont)
#    SET(GLT_LINK_LIBRARIES ${GLT_LINK_LIBRARIES} ${ROOT}/lib/unifont)
#ENDIF (EXISTS src/unifont)

ADD_SUBDIRECTORY(src/program/util)

SET(GLT_BIN2SRC  ${EXECUTABLE_OUTPUT_PATH}/bin2src)
SET(GLT_TEXT2SRC ${EXECUTABLE_OUTPUT_PATH}/text2src)

IF (ZLIB_FOUND)
    SET(GLT_BIN2SRC ${GLT_BIN2SRC} -z)
ENDIF (ZLIB_FOUND)

#

IF (EXISTS ${ROOT}/src/glew)
    ADD_SUBDIRECTORY(${ROOT}/src/glew)
    ADD_DEFINITIONS(-DGLEW_STATIC)
ENDIF (EXISTS ${ROOT}/src/glew)

IF (EXISTS src/freeglut)
    ADD_SUBDIRECTORY(src/freeglut)
ENDIF (EXISTS src/freeglut)

IF (EXISTS src/glut)
    ADD_SUBDIRECTORY(src/glut)
ENDIF (EXISTS src/glut)

IF (EXISTS src/glui)
    ADD_SUBDIRECTORY(src/glui)
    ADD_SUBDIRECTORY(src/program/glui)
ENDIF (EXISTS src/glui)

IF (EXISTS ${ROOT}/src/program/test)
    ADD_SUBDIRECTORY(${ROOT}/src/program/test)
ENDIF (EXISTS ${ROOT}/src/program/test)

IF (EXISTS ${ROOT}/src/program/example)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/examiner)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/font)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/fractal)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/march)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/note)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/plasma)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/rand)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/skybox)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/slides)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/sphere)
    ADD_SUBDIRECTORY(${ROOT}/src/program/example/texture)
ENDIF (EXISTS ${ROOT}/src/program/example)

IF (EXISTS src/program/example/unifonte)
#   ADD_SUBDIRECTORY(src/program/example/unifonte)
ENDIF (EXISTS src/program/example/unifonte)

IF (EXISTS src/program/raster)
    ADD_SUBDIRECTORY(src/program/raster)
ENDIF (EXISTS src/program/raster)

IF (EXISTS src/program/coaster)
    ADD_SUBDIRECTORY(src/program/coaster)
ENDIF (EXISTS src/program/coaster)

IF (EXISTS ${ROOT}/src/program/gltChaos)
    ADD_SUBDIRECTORY(${ROOT}/src/program/gltChaos)
ENDIF (EXISTS ${ROOT}/src/program/gltChaos)

IF (EXISTS src/program/gltPlasma)
    ADD_SUBDIRECTORY(src/program/gltPlasma)
ENDIF (EXISTS src/program/gltPlasma)

IF (EXISTS src/program/gltLife)
    ADD_SUBDIRECTORY(src/program/gltLife)
ENDIF (EXISTS src/program/gltLife)

IF (EXISTS ${ROOT}/src/program/gltZpr)
    ADD_SUBDIRECTORY(${ROOT}/src/program/gltZpr)
ENDIF (EXISTS ${ROOT}/src/program/gltZpr)

IF (EXISTS ${ROOT}/src/program/grips)
    ADD_SUBDIRECTORY(${ROOT}/src/program/grips)
ENDIF (EXISTS ${ROOT}/src/program/grips)

IF (EXISTS ${ROOT}/src/csg)
    ADD_SUBDIRECTORY(${ROOT}/src/csg)
    ADD_SUBDIRECTORY(${ROOT}/src/program/csg)
ENDIF (EXISTS ${ROOT}/src/csg)

IF (EXISTS src/program/experimental)
    ADD_SUBDIRECTORY(src/program/experimental)
ENDIF (EXISTS src/program/experimental)

IF (EXISTS src/program/experimental/glsl)
    ADD_SUBDIRECTORY(src/program/experimental/glsl)
ENDIF (EXISTS src/program/experimental/glsl)

IF (EXISTS src/neverland)
    ADD_SUBDIRECTORY(src/neverland)
ENDIF (EXISTS src/neverland)

IF (EXISTS src/program/qt/test)
    IF (QT4_FOUND)
        ADD_SUBDIRECTORY(src/program/qt/test)
    ENDIF (QT4_FOUND)
ENDIF (EXISTS src/program/qt/test)
