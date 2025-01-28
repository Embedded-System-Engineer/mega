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
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/mega/_7seg/_7seg.c src/mega/ADC/adc.c src/mega/buffers/buffers.c src/mega/button/button.c src/mega/cmsa/csma.c src/mega/ds1307/example/ds1307.X/src/app.c src/mega/ds1307/ds1307.c src/mega/eeprom/eeprom.c src/mega/exeeprom/exEprom.c src/mega/fifo/fifo.c src/mega/gpio/gpio.c src/mega/keypad/keypad.c src/mega/lcd/lcd.c src/mega/lcdmnue/lcdmnue.c src/mega/signalGenertor/signalGenertor.c src/mega/SSD/SSD.c src/mega/system/system.c src/mega/system/time.c src/mega/Tone/tone.c src/mega/twi/twi.c src/mega/usart/usart.c src/mega/utility/utility.c src/mega/ZLP/ZLP.c src/mega.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/mega/_7seg/_7seg.o ${OBJECTDIR}/src/mega/ADC/adc.o ${OBJECTDIR}/src/mega/buffers/buffers.o ${OBJECTDIR}/src/mega/button/button.o ${OBJECTDIR}/src/mega/cmsa/csma.o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o ${OBJECTDIR}/src/mega/ds1307/ds1307.o ${OBJECTDIR}/src/mega/eeprom/eeprom.o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o ${OBJECTDIR}/src/mega/fifo/fifo.o ${OBJECTDIR}/src/mega/gpio/gpio.o ${OBJECTDIR}/src/mega/keypad/keypad.o ${OBJECTDIR}/src/mega/lcd/lcd.o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o ${OBJECTDIR}/src/mega/SSD/SSD.o ${OBJECTDIR}/src/mega/system/system.o ${OBJECTDIR}/src/mega/system/time.o ${OBJECTDIR}/src/mega/Tone/tone.o ${OBJECTDIR}/src/mega/twi/twi.o ${OBJECTDIR}/src/mega/usart/usart.o ${OBJECTDIR}/src/mega/utility/utility.o ${OBJECTDIR}/src/mega/ZLP/ZLP.o ${OBJECTDIR}/src/mega.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/mega/_7seg/_7seg.o.d ${OBJECTDIR}/src/mega/ADC/adc.o.d ${OBJECTDIR}/src/mega/buffers/buffers.o.d ${OBJECTDIR}/src/mega/button/button.o.d ${OBJECTDIR}/src/mega/cmsa/csma.o.d ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d ${OBJECTDIR}/src/mega/fifo/fifo.o.d ${OBJECTDIR}/src/mega/gpio/gpio.o.d ${OBJECTDIR}/src/mega/keypad/keypad.o.d ${OBJECTDIR}/src/mega/lcd/lcd.o.d ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d ${OBJECTDIR}/src/mega/SSD/SSD.o.d ${OBJECTDIR}/src/mega/system/system.o.d ${OBJECTDIR}/src/mega/system/time.o.d ${OBJECTDIR}/src/mega/Tone/tone.o.d ${OBJECTDIR}/src/mega/twi/twi.o.d ${OBJECTDIR}/src/mega/usart/usart.o.d ${OBJECTDIR}/src/mega/utility/utility.o.d ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d ${OBJECTDIR}/src/mega.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/mega/_7seg/_7seg.o ${OBJECTDIR}/src/mega/ADC/adc.o ${OBJECTDIR}/src/mega/buffers/buffers.o ${OBJECTDIR}/src/mega/button/button.o ${OBJECTDIR}/src/mega/cmsa/csma.o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o ${OBJECTDIR}/src/mega/ds1307/ds1307.o ${OBJECTDIR}/src/mega/eeprom/eeprom.o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o ${OBJECTDIR}/src/mega/fifo/fifo.o ${OBJECTDIR}/src/mega/gpio/gpio.o ${OBJECTDIR}/src/mega/keypad/keypad.o ${OBJECTDIR}/src/mega/lcd/lcd.o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o ${OBJECTDIR}/src/mega/SSD/SSD.o ${OBJECTDIR}/src/mega/system/system.o ${OBJECTDIR}/src/mega/system/time.o ${OBJECTDIR}/src/mega/Tone/tone.o ${OBJECTDIR}/src/mega/twi/twi.o ${OBJECTDIR}/src/mega/usart/usart.o ${OBJECTDIR}/src/mega/utility/utility.o ${OBJECTDIR}/src/mega/ZLP/ZLP.o ${OBJECTDIR}/src/mega.o

# Source Files
SOURCEFILES=src/mega/_7seg/_7seg.c src/mega/ADC/adc.c src/mega/buffers/buffers.c src/mega/button/button.c src/mega/cmsa/csma.c src/mega/ds1307/example/ds1307.X/src/app.c src/mega/ds1307/ds1307.c src/mega/eeprom/eeprom.c src/mega/exeeprom/exEprom.c src/mega/fifo/fifo.c src/mega/gpio/gpio.c src/mega/keypad/keypad.c src/mega/lcd/lcd.c src/mega/lcdmnue/lcdmnue.c src/mega/signalGenertor/signalGenertor.c src/mega/SSD/SSD.c src/mega/system/system.c src/mega/system/time.c src/mega/Tone/tone.c src/mega/twi/twi.c src/mega/usart/usart.c src/mega/utility/utility.c src/mega/ZLP/ZLP.c src/mega.c

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
	${MAKE}  -f nbproject/Makefile-Atmega128A.mk ${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/mega/_7seg/_7seg.o: src/mega/_7seg/_7seg.c  .generated_files/flags/Atmega128A/41a236206c79a022d7c870e28952fde71ade80a6 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/_7seg" 
	@${RM} ${OBJECTDIR}/src/mega/_7seg/_7seg.o.d 
	@${RM} ${OBJECTDIR}/src/mega/_7seg/_7seg.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/_7seg/_7seg.o.d" -MT "${OBJECTDIR}/src/mega/_7seg/_7seg.o.d" -MT ${OBJECTDIR}/src/mega/_7seg/_7seg.o  -o ${OBJECTDIR}/src/mega/_7seg/_7seg.o src/mega/_7seg/_7seg.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ADC/adc.o: src/mega/ADC/adc.c  .generated_files/flags/Atmega128A/4962f464416fbe2b09a13a81fbf82f1fcd41575e .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ADC" 
	@${RM} ${OBJECTDIR}/src/mega/ADC/adc.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ADC/adc.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ADC/adc.o.d" -MT "${OBJECTDIR}/src/mega/ADC/adc.o.d" -MT ${OBJECTDIR}/src/mega/ADC/adc.o  -o ${OBJECTDIR}/src/mega/ADC/adc.o src/mega/ADC/adc.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/Atmega128A/643c48881bc9bcc946bee8c568a162038656c4be .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/Atmega128A/cc59d85764133d7b6b866623a8c193f4e94b144b .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/Atmega128A/6a19423e539436fec1109115a68dc2114d02bd6 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/Atmega128A/e3b96367edee7958f09c0a78755878e49b0d0caa .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/Atmega128A/241266f83b5ebfddf2173faec07dce982c3b98cf .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/Atmega128A/947aef505602af198e573fcbc363c52528b7b4e5 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/Atmega128A/8f8818726243afe0644671602b496368f6b0ac98 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/fifo/fifo.o: src/mega/fifo/fifo.c  .generated_files/flags/Atmega128A/a1eb81b8b3f3175ebd1501e2627b2e0700475a1b .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/fifo" 
	@${RM} ${OBJECTDIR}/src/mega/fifo/fifo.o.d 
	@${RM} ${OBJECTDIR}/src/mega/fifo/fifo.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/fifo/fifo.o.d" -MT "${OBJECTDIR}/src/mega/fifo/fifo.o.d" -MT ${OBJECTDIR}/src/mega/fifo/fifo.o  -o ${OBJECTDIR}/src/mega/fifo/fifo.o src/mega/fifo/fifo.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/Atmega128A/c62469d5af2e2a99cf6dc6165a459b064ed7b18a .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/Atmega128A/23e24e7d9cfa7ee0997e23e5476194bc59bacb .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/Atmega128A/183e2cb5aa9fe21dcd4cf781f1291712f90985a2 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/Atmega128A/11959e2478a0676535526a1930adb116138db68a .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/Atmega128A/a354eb74b58ad98cff1e5eb6efcd635749a8e78 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/SSD/SSD.o: src/mega/SSD/SSD.c  .generated_files/flags/Atmega128A/aa2b50a0872f5f0a8645092f05bad19ece4f1836 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/SSD" 
	@${RM} ${OBJECTDIR}/src/mega/SSD/SSD.o.d 
	@${RM} ${OBJECTDIR}/src/mega/SSD/SSD.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/SSD/SSD.o.d" -MT "${OBJECTDIR}/src/mega/SSD/SSD.o.d" -MT ${OBJECTDIR}/src/mega/SSD/SSD.o  -o ${OBJECTDIR}/src/mega/SSD/SSD.o src/mega/SSD/SSD.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/Atmega128A/12936f347dc5c7e611426c046df768908819e11f .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/Atmega128A/266f7acd69022020f814e364599ee3e0256e8d7f .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/Tone/tone.o: src/mega/Tone/tone.c  .generated_files/flags/Atmega128A/a1cad201fb406cef6698a5b9fa7def84327b2098 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/Tone" 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o.d 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT ${OBJECTDIR}/src/mega/Tone/tone.o  -o ${OBJECTDIR}/src/mega/Tone/tone.o src/mega/Tone/tone.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/Atmega128A/395f6f3ed9f4c3498e326ba291b3ce7f90aa1c30 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/Atmega128A/c3515c93ada6aa297ce4b79ae4219b2be4208001 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/utility/utility.o: src/mega/utility/utility.c  .generated_files/flags/Atmega128A/fcee39abc6efb46f9b86e453b5919c1754b361fe .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/utility" 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o.d 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT ${OBJECTDIR}/src/mega/utility/utility.o  -o ${OBJECTDIR}/src/mega/utility/utility.o src/mega/utility/utility.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ZLP/ZLP.o: src/mega/ZLP/ZLP.c  .generated_files/flags/Atmega128A/275b104e8a1bedd171315b71d1fd2a0b335ead88 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ZLP" 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT ${OBJECTDIR}/src/mega/ZLP/ZLP.o  -o ${OBJECTDIR}/src/mega/ZLP/ZLP.o src/mega/ZLP/ZLP.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/Atmega128A/bd2a6b311acb7c72b0a80f1923738fd1af7bf640 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/mega/_7seg/_7seg.o: src/mega/_7seg/_7seg.c  .generated_files/flags/Atmega128A/d3492778a0eea77bb94c1d78196c7bdc28415084 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/_7seg" 
	@${RM} ${OBJECTDIR}/src/mega/_7seg/_7seg.o.d 
	@${RM} ${OBJECTDIR}/src/mega/_7seg/_7seg.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/_7seg/_7seg.o.d" -MT "${OBJECTDIR}/src/mega/_7seg/_7seg.o.d" -MT ${OBJECTDIR}/src/mega/_7seg/_7seg.o  -o ${OBJECTDIR}/src/mega/_7seg/_7seg.o src/mega/_7seg/_7seg.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ADC/adc.o: src/mega/ADC/adc.c  .generated_files/flags/Atmega128A/87ae6569644720508001ee378889af0b9e3f918e .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ADC" 
	@${RM} ${OBJECTDIR}/src/mega/ADC/adc.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ADC/adc.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ADC/adc.o.d" -MT "${OBJECTDIR}/src/mega/ADC/adc.o.d" -MT ${OBJECTDIR}/src/mega/ADC/adc.o  -o ${OBJECTDIR}/src/mega/ADC/adc.o src/mega/ADC/adc.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/Atmega128A/6f053c92be2fb6a7021b870aabb1f4535b7ac631 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/Atmega128A/25879d57d893b2ddd534c3e403db92e7a5592136 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/Atmega128A/baae416d750d042f66a1d169315fa9a3081ae020 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/Atmega128A/c7b9522d1e83a9f3f52785577b45302b5fa922e .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/Atmega128A/26e475ddcae2bca5096867e2b110d265695ee74a .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/Atmega128A/6090fca30b52c878e6ae7bf5226cbc77cae06ae3 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/Atmega128A/f8800b60abcf96d1602d7a50bd587d0d585c094a .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/fifo/fifo.o: src/mega/fifo/fifo.c  .generated_files/flags/Atmega128A/b254e35d4d02abaf662b1191ca5014d5106b59a4 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/fifo" 
	@${RM} ${OBJECTDIR}/src/mega/fifo/fifo.o.d 
	@${RM} ${OBJECTDIR}/src/mega/fifo/fifo.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/fifo/fifo.o.d" -MT "${OBJECTDIR}/src/mega/fifo/fifo.o.d" -MT ${OBJECTDIR}/src/mega/fifo/fifo.o  -o ${OBJECTDIR}/src/mega/fifo/fifo.o src/mega/fifo/fifo.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/Atmega128A/a50222673d2f7c934935114aff65f640195703ff .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/Atmega128A/e4538c72e3b355356d06cc6fb93a3edb55081d9e .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/Atmega128A/71659dec03ec43f657d1020b5ca464b08335b398 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/Atmega128A/7ed52245addfc94009e83d939b8c607bc68dac5a .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/Atmega128A/706b1352c1488e89c2e760dae6da2e2755c6d4ad .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/SSD/SSD.o: src/mega/SSD/SSD.c  .generated_files/flags/Atmega128A/311087a72cc457481c5316696a44c63240a6a859 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/SSD" 
	@${RM} ${OBJECTDIR}/src/mega/SSD/SSD.o.d 
	@${RM} ${OBJECTDIR}/src/mega/SSD/SSD.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/SSD/SSD.o.d" -MT "${OBJECTDIR}/src/mega/SSD/SSD.o.d" -MT ${OBJECTDIR}/src/mega/SSD/SSD.o  -o ${OBJECTDIR}/src/mega/SSD/SSD.o src/mega/SSD/SSD.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/Atmega128A/f859fd8076696e4c8249b3d134913e52601dd9ed .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/Atmega128A/21c43f73e84d40407b38284563641a562fd21bda .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/Tone/tone.o: src/mega/Tone/tone.c  .generated_files/flags/Atmega128A/567ec5c08c80586827e319050f1c2e4c5caa23c6 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/Tone" 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o.d 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT ${OBJECTDIR}/src/mega/Tone/tone.o  -o ${OBJECTDIR}/src/mega/Tone/tone.o src/mega/Tone/tone.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/Atmega128A/905389409ff5478464a9fedcd54176d4a4add391 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/Atmega128A/8797590abd0d9912031ba0e797a0ca1d53efb6c9 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/utility/utility.o: src/mega/utility/utility.c  .generated_files/flags/Atmega128A/3f813730cc23c1357d62b23fa0a6dcf0be7448de .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/utility" 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o.d 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT ${OBJECTDIR}/src/mega/utility/utility.o  -o ${OBJECTDIR}/src/mega/utility/utility.o src/mega/utility/utility.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ZLP/ZLP.o: src/mega/ZLP/ZLP.c  .generated_files/flags/Atmega128A/7f2ebe40abb0768dbeb87ac70223204a1225ac5d .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ZLP" 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT ${OBJECTDIR}/src/mega/ZLP/ZLP.o  -o ${OBJECTDIR}/src/mega/ZLP/ZLP.o src/mega/ZLP/ZLP.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/Atmega128A/8b501cdcd1678b6c96e682847102edb79640db7e .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "D:/Smart Solution Final Data/Nurse System/Nurse Master/Nurse Master V3/SW/NurseMaster.X/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: archive
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_AR} $(MP_EXTRA_AR_PRE) -r -o ${DISTDIR}/mega2.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}   
else
${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_AR} $(MP_EXTRA_AR_PRE) -r -o ${DISTDIR}/mega2.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}   
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

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
