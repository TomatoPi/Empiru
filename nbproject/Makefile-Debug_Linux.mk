#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug_Linux
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/gui/utils/Sprite.o \
	${OBJECTDIR}/src/gui/utils/Window.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/utils/hex/HexCamera.o \
	${OBJECTDIR}/src/utils/hex/HexCoords.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lSDL2 -lSDL2_image
CXXFLAGS=-lSDL2 -lSDL2_image

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/empiru

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/empiru: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/empiru ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/gui/utils/Sprite.o: src/gui/utils/Sprite.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src/gui/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/gui/utils/Sprite.o src/gui/utils/Sprite.cpp

${OBJECTDIR}/src/gui/utils/Window.o: src/gui/utils/Window.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src/gui/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/gui/utils/Window.o src/gui/utils/Window.cpp

${OBJECTDIR}/src/main.o: src/main.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/utils/hex/HexCamera.o: src/utils/hex/HexCamera.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src/utils/hex
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/hex/HexCamera.o src/utils/hex/HexCamera.cpp

${OBJECTDIR}/src/utils/hex/HexCoords.o: src/utils/hex/HexCoords.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src/utils/hex
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/hex/HexCoords.o src/utils/hex/HexCoords.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
