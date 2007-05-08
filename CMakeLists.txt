SET(CMAKE_VERBOSE_MAKEFILE 0)
SET(CMAKE_COLOR_MAKEFILE 1)

##############

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/jpeg)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
#LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

################ Dependencies

# OpenGL

INCLUDE (${CMAKE_ROOT}/Modules/FindOpenGL.cmake)
IF (OPENGL_FOUND)
    SET(OPENGL_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/GLEW ${OPENGL_LIBRARIES})
    MESSAGE(STATUS " OpenGL detected: ${OPENGL_LIBRARIES}" )
ELSE (OPENGL_FOUND)
    MESSAGE(ERROR " OpenGL not detected")
ENDIF (OPENGL_FOUND)

# Detect local freeglut, GLUT or system GLUT

IF (EXISTS src/freeglut)
    ADD_DEFINITIONS(-DGLUTM_FREEGLUT)
    SET(GLUT_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/freeglut ${OPENGL_LIBRARIES})
    MESSAGE(STATUS " GLUT detected: ${GLUT_LIBRARIES}")
ELSE (EXISTS src/freeglut)
    IF (EXISTS src/glut)
        ADD_DEFINITIONS(-DGLUTM_GLUT)
        SET(GLUT_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/glut ${OPENGL_LIBRARIES})
        MESSAGE(STATUS " GLUT detected: ${GLUT_LIBRARIES}")
    ELSE (EXISTS src/glut)
        INCLUDE (${CMAKE_ROOT}/Modules/FindGLUT.cmake)
        IF (GLUT_FOUND)
            ADD_DEFINITIONS(-DGLUTM_GLUT)
            MESSAGE(STATUS " GLUT detected: ${GLUT_LIBRARIES}")
        ELSE (GLUT_FOUND)
            MESSAGE(ERROR " GLT depends on GLUT or freeglut.")
        ENDIF (GLUT_FOUND)
    ENDIF (EXISTS src/glut)
ENDIF (EXISTS src/freeglut)

# GLUI

IF (EXISTS src/glui)
    SET(GLUI_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/glui ${GLUT_LIBRARIES})
    MESSAGE(STATUS " GLUI detected: ${GLUI_LIBRARIES}")
ELSE (EXISTS src/glui)
    MESSAGE(STATUS " not using glui.")
ENDIF (EXISTS src/glui)

# ZLIB

IF (EXISTS src/zlib)
    ADD_DEFINITIONS(-DGLT_ZLIB)
    SET(ZLIB_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/z)
    MESSAGE(STATUS " ZLIB detected: ${ZLIB_LIBRARIES}")
ELSE (EXISTS src/zlib)
    INCLUDE (${CMAKE_ROOT}/Modules/FindZLIB.cmake)
    IF (ZLIB_FOUND)
        ADD_DEFINITIONS(-DGLT_ZLIB)
        MESSAGE(STATUS " ZLIB detected: ${ZLIB_LIBRARIES}")
    ELSE (ZLIB_FOUND)
        MESSAGE(ERROR " GLT depends on zlib.")
    ENDIF (ZLIB_FOUND)
ENDIF (EXISTS src/zlib)

# PNG

IF (EXISTS src/png)
    ADD_DEFINITIONS(-DGLT_PNG)
    SET(PNG_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/png ${ZLIB_LIBRARIES})
    MESSAGE(STATUS " PNG detected: ${PNG_LIBRARIES}")
ELSE (EXISTS src/png)
    INCLUDE (${CMAKE_ROOT}/Modules/FindPNG.cmake)
    IF (PNG_FOUND)
        ADD_DEFINITIONS(-DGLT_PNG)
        MESSAGE(STATUS " PNG detected: ${PNG_LIBRARIES}")
    ELSE (PNG_FOUND)
        MESSAGE(STATUS " PNG not found.")
    ENDIF (PNG_FOUND)
ENDIF (EXISTS src/png)

# JPG

IF (EXISTS src/jpeg)
    ADD_DEFINITIONS(-DGLT_JPEG)
    SET(JPEG_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/jpeg)
    MESSAGE(STATUS " JPEG detected: ${JPEG_LIBRARIES}")
ELSE (EXISTS src/jpeg)
    SET(JPEG_FIND_QUIETLY 1)
    INCLUDE (${CMAKE_ROOT}/Modules/FindJPEG.cmake)
    IF (JPEG_FOUND)
        ADD_DEFINITIONS(-DGLT_JPEG)
        MESSAGE(STATUS " JPEG detected: ${JPEG_LIBRARIES}")
    ELSE (JPEG_FOUND)
        MESSAGE(STATUS " JPEG not found.")
    ENDIF (JPEG_FOUND)
ENDIF (EXISTS src/jpeg)

#######################################################################

SET(GLT_LINK_LIBRARIES network glutm node mesh glt math fonts)
SET(GLT_LINK_LIBRARIES ${GLT_LINK_LIBRARIES} ${PNG_LIBRARIES} ${ZLIB_LIBRARIES} ${JPEG_LIBRARIES} ptypes)
SET(GLT_LINK_LIBRARIES ${GLT_LINK_LIBRARIES} ${GLUT_LIBRARIES} m pthread)

#####################################

#ADD_SUBDIRECTORY(src/misc)
ADD_SUBDIRECTORY(src/glt)
ADD_SUBDIRECTORY(src/math)
ADD_SUBDIRECTORY(src/mesh)
ADD_SUBDIRECTORY(src/fonts)
ADD_SUBDIRECTORY(src/glutm)
ADD_SUBDIRECTORY(src/node)
ADD_SUBDIRECTORY(src/network)

IF (EXISTS src/glew)
    ADD_SUBDIRECTORY(src/glew)
ENDIF (EXISTS src/glew)

IF (EXISTS src/freeglut)
    ADD_SUBDIRECTORY(src/freeglut)
ENDIF (EXISTS src/freeglut)

IF (EXISTS src/glui)
    ADD_SUBDIRECTORY(src/glui)
    ADD_SUBDIRECTORY(src/program/glui)
ENDIF (EXISTS src/glui)

IF (EXISTS src/zlib)
    ADD_SUBDIRECTORY(src/zlib)
ENDIF (EXISTS src/zlib)

IF (EXISTS src/png)
    ADD_SUBDIRECTORY(src/png)
ENDIF (EXISTS src/png)

IF (EXISTS src/ptypes)
    ADD_SUBDIRECTORY(src/ptypes)
ENDIF (EXISTS src/ptypes)

IF (EXISTS src/jpeg)
    ADD_SUBDIRECTORY(src/jpeg)
ENDIF (EXISTS src/jpeg)

IF (EXISTS src/example)
    ADD_SUBDIRECTORY(src/program/example/examiner)
    ADD_SUBDIRECTORY(src/program/example/font)
    ADD_SUBDIRECTORY(src/program/example/fractal)
    ADD_SUBDIRECTORY(src/program/example/glsl)
    ADD_SUBDIRECTORY(src/program/example/march)
    ADD_SUBDIRECTORY(src/program/example/note)
    ADD_SUBDIRECTORY(src/program/example/plasma)
    ADD_SUBDIRECTORY(src/program/example/rand)
    ADD_SUBDIRECTORY(src/program/example/skybox)
    ADD_SUBDIRECTORY(src/program/example/sphere)
    ADD_SUBDIRECTORY(src/program/example/texture)
ENDIF (EXISTS src/example)

ADD_SUBDIRECTORY(src/program/raster)
ADD_SUBDIRECTORY(src/program/gltChaos)
ADD_SUBDIRECTORY(src/program/gltPlasma)
ADD_SUBDIRECTORY(src/program/gltLife)
ADD_SUBDIRECTORY(src/program/gltZpr)

IF (EXISTS src/program/grips)
    ADD_SUBDIRECTORY(src/program/grips)
ENDIF (EXISTS src/program/grips)

IF (EXISTS src/csg)
    ADD_SUBDIRECTORY(src/csg)
    ADD_SUBDIRECTORY(src/program/csg)
ENDIF (EXISTS src/csg)

IF (EXISTS src/neverland)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/neverland/pgl)
    ADD_SUBDIRECTORY(src/neverland/pgl/engine)
    ADD_SUBDIRECTORY(src/neverland/pgl/geometry)
    ADD_SUBDIRECTORY(src/neverland/pgl/gpc)
    ADD_SUBDIRECTORY(src/neverland/pgl/pgl)
    ADD_SUBDIRECTORY(src/neverland/pgl/pglTexture)
    ADD_SUBDIRECTORY(src/neverland/pgl/ui)
    ADD_SUBDIRECTORY(src/neverland/viewer)
ENDIF (EXISTS src/neverland)
