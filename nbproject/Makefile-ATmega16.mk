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
ifeq "$(wildcard nbproject/Makefile-local-ATmega16.mk)" "nbproject/Makefile-local-ATmega16.mk"
include nbproject/Makefile-local-ATmega16.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=ATmega16
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
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega16a"



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
	${MAKE}  -f nbproject/Makefile-ATmega16.mk ${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega16A
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
${OBJECTDIR}/src/mega/_7seg/_7seg.o: src/mega/_7seg/_7seg.c  .generated_files/flags/ATmega16/d45d7bc8cd8804e3858587746052b5d9ec41867a .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/_7seg" 
	@${RM} ${OBJECTDIR}/src/mega/_7seg/_7seg.o.d 
	@${RM} ${OBJECTDIR}/src/mega/_7seg/_7seg.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/_7seg/_7seg.o.d" -MT "${OBJECTDIR}/src/mega/_7seg/_7seg.o.d" -MT ${OBJECTDIR}/src/mega/_7seg/_7seg.o  -o ${OBJECTDIR}/src/mega/_7seg/_7seg.o src/mega/_7seg/_7seg.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ADC/adc.o: src/mega/ADC/adc.c  .generated_files/flags/ATmega16/d8e3a373924e7482228a582e692be095910bc612 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ADC" 
	@${RM} ${OBJECTDIR}/src/mega/ADC/adc.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ADC/adc.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ADC/adc.o.d" -MT "${OBJECTDIR}/src/mega/ADC/adc.o.d" -MT ${OBJECTDIR}/src/mega/ADC/adc.o  -o ${OBJECTDIR}/src/mega/ADC/adc.o src/mega/ADC/adc.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/ATmega16/83cc55894c9b8f13759c4415356e13e39c662599 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/ATmega16/fcc5ff845b2277033a972b29cba35f447981f387 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/ATmega16/e2f69799f9f2200c27814544868b5acb64b59cef .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/ATmega16/5a18648d6203ad84fa04b3341b65fb72e4852f1c .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/ATmega16/8f473d0dd97c744ce54ed718dc68451fc26e6406 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/ATmega16/8cbba0f74b9bf60078999c8337479b7690181bb0 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/ATmega16/fe681168d033c898db29d25edc138bc040080a3c .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/fifo/fifo.o: src/mega/fifo/fifo.c  .generated_files/flags/ATmega16/9404ccc1437c80d038b732ecfd07888e31fd9134 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/fifo" 
	@${RM} ${OBJECTDIR}/src/mega/fifo/fifo.o.d 
	@${RM} ${OBJECTDIR}/src/mega/fifo/fifo.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/fifo/fifo.o.d" -MT "${OBJECTDIR}/src/mega/fifo/fifo.o.d" -MT ${OBJECTDIR}/src/mega/fifo/fifo.o  -o ${OBJECTDIR}/src/mega/fifo/fifo.o src/mega/fifo/fifo.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/ATmega16/5e4416b39c4008baddeb7e98b0b1ec2ea9d8704f .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/ATmega16/9f6817ba847868037761455d31abec20b03e7f5c .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/ATmega16/633c193d1f31a5593d22d7bd7df0801688660066 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/ATmega16/9ef3e1ae3804f9d6a5eaf24fac9b830bcd9f1021 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/ATmega16/70671531217ee0acc5d38cf4b1495ad0ea7091ba .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/SSD/SSD.o: src/mega/SSD/SSD.c  .generated_files/flags/ATmega16/dc61610438825d3ccae2b955e0b635e9cfa59698 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/SSD" 
	@${RM} ${OBJECTDIR}/src/mega/SSD/SSD.o.d 
	@${RM} ${OBJECTDIR}/src/mega/SSD/SSD.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/SSD/SSD.o.d" -MT "${OBJECTDIR}/src/mega/SSD/SSD.o.d" -MT ${OBJECTDIR}/src/mega/SSD/SSD.o  -o ${OBJECTDIR}/src/mega/SSD/SSD.o src/mega/SSD/SSD.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/ATmega16/d1b24fb460a6cd48767f24411f67b0e2e9f76c7c .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/ATmega16/36737603b858aad859659e1a1d9e5c5ac1a1cda8 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/Tone/tone.o: src/mega/Tone/tone.c  .generated_files/flags/ATmega16/7422ab1a25518291921745411a6405e64438d88f .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/Tone" 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o.d 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT ${OBJECTDIR}/src/mega/Tone/tone.o  -o ${OBJECTDIR}/src/mega/Tone/tone.o src/mega/Tone/tone.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/ATmega16/1998fc2eadd16b9bd74b358c672befa7ae4faca9 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/ATmega16/7078a3ac4bbb380684461be87224ee2e6e391250 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/utility/utility.o: src/mega/utility/utility.c  .generated_files/flags/ATmega16/58378800eea3e6a11b7b19dea98c3a8d38fa9d3b .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/utility" 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o.d 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT ${OBJECTDIR}/src/mega/utility/utility.o  -o ${OBJECTDIR}/src/mega/utility/utility.o src/mega/utility/utility.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ZLP/ZLP.o: src/mega/ZLP/ZLP.c  .generated_files/flags/ATmega16/835c62d549dacb23919a9d6c24d06ae0785d79a7 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ZLP" 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT ${OBJECTDIR}/src/mega/ZLP/ZLP.o  -o ${OBJECTDIR}/src/mega/ZLP/ZLP.o src/mega/ZLP/ZLP.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/ATmega16/307a234da0c5acdb7a41de66db4372d4f110b349 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/mega/_7seg/_7seg.o: src/mega/_7seg/_7seg.c  .generated_files/flags/ATmega16/863832fb31438aede088650f70cad7d52eda3dc4 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/_7seg" 
	@${RM} ${OBJECTDIR}/src/mega/_7seg/_7seg.o.d 
	@${RM} ${OBJECTDIR}/src/mega/_7seg/_7seg.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/_7seg/_7seg.o.d" -MT "${OBJECTDIR}/src/mega/_7seg/_7seg.o.d" -MT ${OBJECTDIR}/src/mega/_7seg/_7seg.o  -o ${OBJECTDIR}/src/mega/_7seg/_7seg.o src/mega/_7seg/_7seg.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ADC/adc.o: src/mega/ADC/adc.c  .generated_files/flags/ATmega16/706fb7626bba36bd0c76d5937272903018e404c8 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ADC" 
	@${RM} ${OBJECTDIR}/src/mega/ADC/adc.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ADC/adc.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ADC/adc.o.d" -MT "${OBJECTDIR}/src/mega/ADC/adc.o.d" -MT ${OBJECTDIR}/src/mega/ADC/adc.o  -o ${OBJECTDIR}/src/mega/ADC/adc.o src/mega/ADC/adc.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/ATmega16/193eae21b07c25d4cfa0ed28ff3e4cc861fde780 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/ATmega16/a953c5c9ca93df79ba5bf0f39a00e9390edc61ab .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/ATmega16/e3c7b666a2d766ee0ef570fbf67730ad3ebdc23c .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/ATmega16/b3f689c68ef95acce72ee0d7398356b288ffd751 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/ATmega16/347b66120b09b7fbc57dccdf7708a9b5bfa5a2aa .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/ATmega16/169ceab6300d8baccb7d44407e29083ee35b5d1c .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/ATmega16/4a9dea2864e4cdcd2bacde1132bb7aa70ee4645f .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/fifo/fifo.o: src/mega/fifo/fifo.c  .generated_files/flags/ATmega16/252155031eb95f3c4342199999ecc9e2c94a5fba .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/fifo" 
	@${RM} ${OBJECTDIR}/src/mega/fifo/fifo.o.d 
	@${RM} ${OBJECTDIR}/src/mega/fifo/fifo.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/fifo/fifo.o.d" -MT "${OBJECTDIR}/src/mega/fifo/fifo.o.d" -MT ${OBJECTDIR}/src/mega/fifo/fifo.o  -o ${OBJECTDIR}/src/mega/fifo/fifo.o src/mega/fifo/fifo.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/ATmega16/d7401c5bf50a7ffcc5cc0471a9e1ec8a1d41e9d6 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/ATmega16/7e681b848047253f463694dfa01023e5b6839941 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/ATmega16/3f12c87173ddffb9e347b7bafd64557d9c1ae1d6 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/ATmega16/24f72edeaf0e620fce239ebfc8600281b09df276 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/ATmega16/b609f14202ad8d49a2f3b870106b4e435af7bf19 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/SSD/SSD.o: src/mega/SSD/SSD.c  .generated_files/flags/ATmega16/29c54d45594e117eb556bb8e8ce8d210e3aa3d9c .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/SSD" 
	@${RM} ${OBJECTDIR}/src/mega/SSD/SSD.o.d 
	@${RM} ${OBJECTDIR}/src/mega/SSD/SSD.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/SSD/SSD.o.d" -MT "${OBJECTDIR}/src/mega/SSD/SSD.o.d" -MT ${OBJECTDIR}/src/mega/SSD/SSD.o  -o ${OBJECTDIR}/src/mega/SSD/SSD.o src/mega/SSD/SSD.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/ATmega16/a18916b921e385070456a1da3180e00c8aaf4a3a .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/ATmega16/2828e80e1b93673101cddc147d6ab6921e95dd44 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/Tone/tone.o: src/mega/Tone/tone.c  .generated_files/flags/ATmega16/aa352c27c6988044d9cdf3fad5ac312c353ccc3a .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/Tone" 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o.d 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT ${OBJECTDIR}/src/mega/Tone/tone.o  -o ${OBJECTDIR}/src/mega/Tone/tone.o src/mega/Tone/tone.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/ATmega16/64964c993e39339e4905c54c03d0e29f639841fd .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/ATmega16/5ff8406449c8deb6e39b6938adfbbb69b8fad26d .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/utility/utility.o: src/mega/utility/utility.c  .generated_files/flags/ATmega16/136ad5dacd49782cf8ea7902d20960d1d8c409c3 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/utility" 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o.d 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT ${OBJECTDIR}/src/mega/utility/utility.o  -o ${OBJECTDIR}/src/mega/utility/utility.o src/mega/utility/utility.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ZLP/ZLP.o: src/mega/ZLP/ZLP.c  .generated_files/flags/ATmega16/c9e4b9d85095eb39cf56d1f41f4507e85a78f276 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ZLP" 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT ${OBJECTDIR}/src/mega/ZLP/ZLP.o  -o ${OBJECTDIR}/src/mega/ZLP/ZLP.o src/mega/ZLP/ZLP.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/ATmega16/d51d36dcb9953b28b9c0780e49a38683b3edd048 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
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
