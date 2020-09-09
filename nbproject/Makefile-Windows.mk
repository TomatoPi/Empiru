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
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Windows
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/gui/utils/Handler.o \
	${OBJECTDIR}/src/gui/utils/Sprite.o \
	${OBJECTDIR}/src/gui/utils/Window.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/utils/hex/HexCamera.o \
	${OBJECTDIR}/src/utils/hex/HexCoords.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/src/utils/hex/tests/HexTestClass.o \
	${TESTDIR}/src/utils/hex/tests/HexTestRunner.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall
CXXFLAGS=-Wall

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Llib -lSDL2 -lSDL2_image -lSDL2main

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/empiru.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/empiru.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/empiru ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/gui/utils/Handler.o: src/gui/utils/Handler.cpp
	${MKDIR} -p ${OBJECTDIR}/src/gui/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/gui/utils/Handler.o src/gui/utils/Handler.cpp

${OBJECTDIR}/src/gui/utils/Sprite.o: src/gui/utils/Sprite.cpp
	${MKDIR} -p ${OBJECTDIR}/src/gui/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/gui/utils/Sprite.o src/gui/utils/Sprite.cpp

${OBJECTDIR}/src/gui/utils/Window.o: src/gui/utils/Window.cpp
	${MKDIR} -p ${OBJECTDIR}/src/gui/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/gui/utils/Window.o src/gui/utils/Window.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/utils/hex/HexCamera.o: src/utils/hex/HexCamera.cpp
	${MKDIR} -p ${OBJECTDIR}/src/utils/hex
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/hex/HexCamera.o src/utils/hex/HexCamera.cpp

${OBJECTDIR}/src/utils/hex/HexCoords.o: src/utils/hex/HexCoords.cpp
	${MKDIR} -p ${OBJECTDIR}/src/utils/hex
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/hex/HexCoords.o src/utils/hex/HexCoords.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/src/utils/hex/tests/HexTestClass.o ${TESTDIR}/src/utils/hex/tests/HexTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   


${TESTDIR}/src/utils/hex/tests/HexTestClass.o: src/utils/hex/tests/HexTestClass.cpp 
	${MKDIR} -p ${TESTDIR}/src/utils/hex/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/src/utils/hex/tests/HexTestClass.o src/utils/hex/tests/HexTestClass.cpp


${TESTDIR}/src/utils/hex/tests/HexTestRunner.o: src/utils/hex/tests/HexTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/src/utils/hex/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/src/utils/hex/tests/HexTestRunner.o src/utils/hex/tests/HexTestRunner.cpp


${OBJECTDIR}/src/gui/utils/Handler_nomain.o: ${OBJECTDIR}/src/gui/utils/Handler.o src/gui/utils/Handler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/gui/utils/Handler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/gui/utils/Handler_nomain.o src/gui/utils/Handler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/gui/utils/Handler.o ${OBJECTDIR}/src/gui/utils/Handler_nomain.o;\
	fi

${OBJECTDIR}/src/gui/utils/Sprite_nomain.o: ${OBJECTDIR}/src/gui/utils/Sprite.o src/gui/utils/Sprite.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/gui/utils/Sprite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/gui/utils/Sprite_nomain.o src/gui/utils/Sprite.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/gui/utils/Sprite.o ${OBJECTDIR}/src/gui/utils/Sprite_nomain.o;\
	fi

${OBJECTDIR}/src/gui/utils/Window_nomain.o: ${OBJECTDIR}/src/gui/utils/Window.o src/gui/utils/Window.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/gui/utils/Window.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/gui/utils/Window_nomain.o src/gui/utils/Window.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/gui/utils/Window.o ${OBJECTDIR}/src/gui/utils/Window_nomain.o;\
	fi

${OBJECTDIR}/src/main_nomain.o: ${OBJECTDIR}/src/main.o src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main_nomain.o src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
	fi

${OBJECTDIR}/src/utils/hex/HexCamera_nomain.o: ${OBJECTDIR}/src/utils/hex/HexCamera.o src/utils/hex/HexCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils/hex
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/utils/hex/HexCamera.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/hex/HexCamera_nomain.o src/utils/hex/HexCamera.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/utils/hex/HexCamera.o ${OBJECTDIR}/src/utils/hex/HexCamera_nomain.o;\
	fi

${OBJECTDIR}/src/utils/hex/HexCoords_nomain.o: ${OBJECTDIR}/src/utils/hex/HexCoords.o src/utils/hex/HexCoords.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils/hex
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/utils/hex/HexCoords.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Isrc -Iinclude -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/hex/HexCoords_nomain.o src/utils/hex/HexCoords.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/utils/hex/HexCoords.o ${OBJECTDIR}/src/utils/hex/HexCoords_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
