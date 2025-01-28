#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Atmega128A.mk)" "nbproject/Makefile-local-Atmega128A.mk"
include nbproject/Makefile-local-Atmega128A.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Atmega128A
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/TestCommLowLayer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/TestCommLowLayer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/app.c src/dataTiming.c src/configuration.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app.o ${OBJECTDIR}/src/dataTiming.o ${OBJECTDIR}/src/configuration.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app.o.d ${OBJECTDIR}/src/dataTiming.o.d ${OBJECTDIR}/src/configuration.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app.o ${OBJECTDIR}/src/dataTiming.o ${OBJECTDIR}/src/configuration.o

# Source Files
SOURCEFILES=src/app.c src/dataTiming.c src/configuration.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega128a"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Atmega128A.mk ${DISTDIR}/TestCommLowLayer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega128A
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/app.o: src/app.c  .generated_files/flags/Atmega128A/8379cea6bed9f06b997d8b6ac6488e912be73ad6 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/app.o.d" -MT "${OBJECTDIR}/src/app.o.d" -MT ${OBJECTDIR}/src/app.o  -o ${OBJECTDIR}/src/app.o src/app.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/dataTiming.o: src/dataTiming.c  .generated_files/flags/Atmega128A/77b5f5f1a6d40e1af9d286cd3976fff68035f267 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/dataTiming.o.d 
	@${RM} ${OBJECTDIR}/src/dataTiming.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/dataTiming.o.d" -MT "${OBJECTDIR}/src/dataTiming.o.d" -MT ${OBJECTDIR}/src/dataTiming.o  -o ${OBJECTDIR}/src/dataTiming.o src/dataTiming.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/configuration.o: src/configuration.c  .generated_files/flags/Atmega128A/4efb8d7b6166281905161496a318f7ab24549b3d .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/configuration.o.d 
	@${RM} ${OBJECTDIR}/src/configuration.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/configuration.o.d" -MT "${OBJECTDIR}/src/configuration.o.d" -MT ${OBJECTDIR}/src/configuration.o  -o ${OBJECTDIR}/src/configuration.o src/configuration.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/app.o: src/app.c  .generated_files/flags/Atmega128A/bf64df9886d1bc8ec515f42ee950abca80efaf62 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/app.o.d" -MT "${OBJECTDIR}/src/app.o.d" -MT ${OBJECTDIR}/src/app.o  -o ${OBJECTDIR}/src/app.o src/app.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/dataTiming.o: src/dataTiming.c  .generated_files/flags/Atmega128A/b480cf0df3886fbfc1c056887d2b78704d778e63 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/dataTiming.o.d 
	@${RM} ${OBJECTDIR}/src/dataTiming.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/dataTiming.o.d" -MT "${OBJECTDIR}/src/dataTiming.o.d" -MT ${OBJECTDIR}/src/dataTiming.o  -o ${OBJECTDIR}/src/dataTiming.o src/dataTiming.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/configuration.o: src/configuration.c  .generated_files/flags/Atmega128A/86384edfc03a7255ba65bd990ddf9f4425e9d54 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/configuration.o.d 
	@${RM} ${OBJECTDIR}/src/configuration.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/configuration.o.d" -MT "${OBJECTDIR}/src/configuration.o.d" -MT ${OBJECTDIR}/src/configuration.o  -o ${OBJECTDIR}/src/configuration.o src/configuration.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/TestCommLowLayer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  lib/Atmega128/mega2.X.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega128a ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\TestCommLowLayer.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/TestCommLowLayer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    lib\Atmega128\mega2.X.a  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
${DISTDIR}/TestCommLowLayer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  lib/Atmega128/mega2.X.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega128a ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\TestCommLowLayer.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/TestCommLowLayer.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    lib\Atmega128\mega2.X.a  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/TestCommLowLayer.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/TestCommLowLayer.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
