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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_AMT_8000_V2_4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_AMT_8000_V2_4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../ApoioTeste.c ../ConversorAD.c ../Display.c ../InicioFimTeste.c ../Interrupcao.c ../Reles.c ../bus_master.c ../Gravador.c ../Placa_principal.c ../RotinaTeste_AMT8000_V_2_4.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/ApoioTeste.o ${OBJECTDIR}/_ext/1472/ConversorAD.o ${OBJECTDIR}/_ext/1472/Display.o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o ${OBJECTDIR}/_ext/1472/Interrupcao.o ${OBJECTDIR}/_ext/1472/Reles.o ${OBJECTDIR}/_ext/1472/bus_master.o ${OBJECTDIR}/_ext/1472/Gravador.o ${OBJECTDIR}/_ext/1472/Placa_principal.o ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/ApoioTeste.o.d ${OBJECTDIR}/_ext/1472/ConversorAD.o.d ${OBJECTDIR}/_ext/1472/Display.o.d ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d ${OBJECTDIR}/_ext/1472/Interrupcao.o.d ${OBJECTDIR}/_ext/1472/Reles.o.d ${OBJECTDIR}/_ext/1472/bus_master.o.d ${OBJECTDIR}/_ext/1472/Gravador.o.d ${OBJECTDIR}/_ext/1472/Placa_principal.o.d ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/ApoioTeste.o ${OBJECTDIR}/_ext/1472/ConversorAD.o ${OBJECTDIR}/_ext/1472/Display.o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o ${OBJECTDIR}/_ext/1472/Interrupcao.o ${OBJECTDIR}/_ext/1472/Reles.o ${OBJECTDIR}/_ext/1472/bus_master.o ${OBJECTDIR}/_ext/1472/Gravador.o ${OBJECTDIR}/_ext/1472/Placa_principal.o ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o

# Source Files
SOURCEFILES=../ApoioTeste.c ../ConversorAD.c ../Display.c ../InicioFimTeste.c ../Interrupcao.c ../Reles.c ../bus_master.c ../Gravador.c ../Placa_principal.c ../RotinaTeste_AMT8000_V_2_4.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_AMT_8000_V2_4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ48GA004
MP_LINKER_FILE_OPTION=,--script=p24FJ48GA004.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/ApoioTeste.o: ../ApoioTeste.c  .generated_files/flags/default/6770f84ca3bf0d9836cdb12b73ee20debb78e4d4 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ApoioTeste.c  -o ${OBJECTDIR}/_ext/1472/ApoioTeste.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ApoioTeste.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ConversorAD.o: ../ConversorAD.c  .generated_files/flags/default/5e7abdbd86608cddaf88dad7c29fd7c340313a96 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ConversorAD.c  -o ${OBJECTDIR}/_ext/1472/ConversorAD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ConversorAD.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Display.o: ../Display.c  .generated_files/flags/default/a0773f9e702598dc8be6bf79eb164f9d208a9c69 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Display.c  -o ${OBJECTDIR}/_ext/1472/Display.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Display.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/InicioFimTeste.o: ../InicioFimTeste.c  .generated_files/flags/default/f48c8c2860c4db70138d107462742ee9ff3a5456 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../InicioFimTeste.c  -o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Interrupcao.o: ../Interrupcao.c  .generated_files/flags/default/78842ffeb5afb3ce0d84cadc59a8a1fe955cbd90 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Interrupcao.c  -o ${OBJECTDIR}/_ext/1472/Interrupcao.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Interrupcao.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Reles.o: ../Reles.c  .generated_files/flags/default/b649ae9968be3f8987371040dc833e3b8de2c18f .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Reles.c  -o ${OBJECTDIR}/_ext/1472/Reles.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Reles.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/bus_master.o: ../bus_master.c  .generated_files/flags/default/893b8fc7c35653cb8b03c219d95f6310353f34f2 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bus_master.c  -o ${OBJECTDIR}/_ext/1472/bus_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bus_master.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Gravador.o: ../Gravador.c  .generated_files/flags/default/b1096eef010e636b0cf7c73e84336eca1a9b8220 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Gravador.c  -o ${OBJECTDIR}/_ext/1472/Gravador.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Gravador.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Placa_principal.o: ../Placa_principal.c  .generated_files/flags/default/95d114e9e927df20da423cd4629adce785fc09a5 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Placa_principal.c  -o ${OBJECTDIR}/_ext/1472/Placa_principal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Placa_principal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o: ../RotinaTeste_AMT8000_V_2_4.c  .generated_files/flags/default/fb4872841a295d2b50ccf1f018c3faae71758beb .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RotinaTeste_AMT8000_V_2_4.c  -o ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1472/ApoioTeste.o: ../ApoioTeste.c  .generated_files/flags/default/d5799cb285db9a698d8913e324cad410e9771089 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ApoioTeste.c  -o ${OBJECTDIR}/_ext/1472/ApoioTeste.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ApoioTeste.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ConversorAD.o: ../ConversorAD.c  .generated_files/flags/default/bd79501d87364e0096ea6133b6af6bb9fb7e0887 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ConversorAD.c  -o ${OBJECTDIR}/_ext/1472/ConversorAD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ConversorAD.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Display.o: ../Display.c  .generated_files/flags/default/b3a8a30cb6f5157db5e74a5c53c11891247bf67c .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Display.c  -o ${OBJECTDIR}/_ext/1472/Display.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Display.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/InicioFimTeste.o: ../InicioFimTeste.c  .generated_files/flags/default/9e607b213a99af9097b96f51a5a51ba678e5e0c2 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../InicioFimTeste.c  -o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Interrupcao.o: ../Interrupcao.c  .generated_files/flags/default/a4ad8e6a395f5595427796e0ce15fa3b4cdc7731 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Interrupcao.c  -o ${OBJECTDIR}/_ext/1472/Interrupcao.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Interrupcao.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Reles.o: ../Reles.c  .generated_files/flags/default/a6a0acd592c26a3d45268013ddc49353d7e24d11 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Reles.c  -o ${OBJECTDIR}/_ext/1472/Reles.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Reles.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/bus_master.o: ../bus_master.c  .generated_files/flags/default/b1c62734a8d7b14efbe8ec20646a86cb34b54ca3 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bus_master.c  -o ${OBJECTDIR}/_ext/1472/bus_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bus_master.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Gravador.o: ../Gravador.c  .generated_files/flags/default/1c37a664336599959e8ffbcf6ff008b3912ae33f .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Gravador.c  -o ${OBJECTDIR}/_ext/1472/Gravador.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Gravador.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Placa_principal.o: ../Placa_principal.c  .generated_files/flags/default/b42ebd200333517dc57b97a67a8cec40933c736c .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Placa_principal.c  -o ${OBJECTDIR}/_ext/1472/Placa_principal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Placa_principal.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o: ../RotinaTeste_AMT8000_V_2_4.c  .generated_files/flags/default/9579aeb5f01d9e04352227a85f8cfc777414d990 .generated_files/flags/default/4068c95ad3a05d584a93989dc9018c5112f3aa75
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RotinaTeste_AMT8000_V_2_4.c  -o ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V_2_4.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_AMT_8000_V2_4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_AMT_8000_V2_4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../ANM 2008 MF",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/Jiga_Universal_-_ANM_2008_MF.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_AMT_8000_V2_4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_AMT_8000_V2_4.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../ANM 2008 MF",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/Jiga_Universal_-_ANM_2008_MF.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_AMT_8000_V2_4.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
