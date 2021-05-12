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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_CPU_AMT_8000.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_CPU_AMT_8000.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../ApoioTeste.c ../ConversorAD.c ../Display.c ../InicioFimTeste.c ../Interrupcao.c ../Reles.c ../bus_master.c ../Gravador.c ../RotinaTeste_CPU_AMT8000.c ../Placa_principal.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/ApoioTeste.o ${OBJECTDIR}/_ext/1472/ConversorAD.o ${OBJECTDIR}/_ext/1472/Display.o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o ${OBJECTDIR}/_ext/1472/Interrupcao.o ${OBJECTDIR}/_ext/1472/Reles.o ${OBJECTDIR}/_ext/1472/bus_master.o ${OBJECTDIR}/_ext/1472/Gravador.o ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o ${OBJECTDIR}/_ext/1472/Placa_principal.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/ApoioTeste.o.d ${OBJECTDIR}/_ext/1472/ConversorAD.o.d ${OBJECTDIR}/_ext/1472/Display.o.d ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d ${OBJECTDIR}/_ext/1472/Interrupcao.o.d ${OBJECTDIR}/_ext/1472/Reles.o.d ${OBJECTDIR}/_ext/1472/bus_master.o.d ${OBJECTDIR}/_ext/1472/Gravador.o.d ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.d ${OBJECTDIR}/_ext/1472/Placa_principal.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/ApoioTeste.o ${OBJECTDIR}/_ext/1472/ConversorAD.o ${OBJECTDIR}/_ext/1472/Display.o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o ${OBJECTDIR}/_ext/1472/Interrupcao.o ${OBJECTDIR}/_ext/1472/Reles.o ${OBJECTDIR}/_ext/1472/bus_master.o ${OBJECTDIR}/_ext/1472/Gravador.o ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o ${OBJECTDIR}/_ext/1472/Placa_principal.o

# Source Files
SOURCEFILES=../ApoioTeste.c ../ConversorAD.c ../Display.c ../InicioFimTeste.c ../Interrupcao.c ../Reles.c ../bus_master.c ../Gravador.c ../RotinaTeste_CPU_AMT8000.c ../Placa_principal.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_CPU_AMT_8000.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ48GA004
MP_LINKER_FILE_OPTION=,-Tp24FJ48GA004.gld
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
${OBJECTDIR}/_ext/1472/ApoioTeste.o: ../ApoioTeste.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o.ok ${OBJECTDIR}/_ext/1472/ApoioTeste.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ApoioTeste.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/ApoioTeste.o.d" -o ${OBJECTDIR}/_ext/1472/ApoioTeste.o ../ApoioTeste.c    
	
${OBJECTDIR}/_ext/1472/ConversorAD.o: ../ConversorAD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o.ok ${OBJECTDIR}/_ext/1472/ConversorAD.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ConversorAD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/ConversorAD.o.d" -o ${OBJECTDIR}/_ext/1472/ConversorAD.o ../ConversorAD.c    
	
${OBJECTDIR}/_ext/1472/Display.o: ../Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o.ok ${OBJECTDIR}/_ext/1472/Display.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Display.o.d" -o ${OBJECTDIR}/_ext/1472/Display.o ../Display.c    
	
${OBJECTDIR}/_ext/1472/InicioFimTeste.o: ../InicioFimTeste.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.ok ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d" -o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o ../InicioFimTeste.c    
	
${OBJECTDIR}/_ext/1472/Interrupcao.o: ../Interrupcao.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o.ok ${OBJECTDIR}/_ext/1472/Interrupcao.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Interrupcao.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Interrupcao.o.d" -o ${OBJECTDIR}/_ext/1472/Interrupcao.o ../Interrupcao.c    
	
${OBJECTDIR}/_ext/1472/Reles.o: ../Reles.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o.ok ${OBJECTDIR}/_ext/1472/Reles.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Reles.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Reles.o.d" -o ${OBJECTDIR}/_ext/1472/Reles.o ../Reles.c    
	
${OBJECTDIR}/_ext/1472/bus_master.o: ../bus_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o.ok ${OBJECTDIR}/_ext/1472/bus_master.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/bus_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/bus_master.o.d" -o ${OBJECTDIR}/_ext/1472/bus_master.o ../bus_master.c    
	
${OBJECTDIR}/_ext/1472/Gravador.o: ../Gravador.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o.ok ${OBJECTDIR}/_ext/1472/Gravador.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Gravador.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Gravador.o.d" -o ${OBJECTDIR}/_ext/1472/Gravador.o ../Gravador.c    
	
${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o: ../RotinaTeste_CPU_AMT8000.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.ok ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.d" -o ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o ../RotinaTeste_CPU_AMT8000.c    
	
${OBJECTDIR}/_ext/1472/Placa_principal.o: ../Placa_principal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o.ok ${OBJECTDIR}/_ext/1472/Placa_principal.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Placa_principal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Placa_principal.o.d" -o ${OBJECTDIR}/_ext/1472/Placa_principal.o ../Placa_principal.c    
	
else
${OBJECTDIR}/_ext/1472/ApoioTeste.o: ../ApoioTeste.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o.ok ${OBJECTDIR}/_ext/1472/ApoioTeste.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ApoioTeste.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/ApoioTeste.o.d" -o ${OBJECTDIR}/_ext/1472/ApoioTeste.o ../ApoioTeste.c    
	
${OBJECTDIR}/_ext/1472/ConversorAD.o: ../ConversorAD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o.ok ${OBJECTDIR}/_ext/1472/ConversorAD.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ConversorAD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/ConversorAD.o.d" -o ${OBJECTDIR}/_ext/1472/ConversorAD.o ../ConversorAD.c    
	
${OBJECTDIR}/_ext/1472/Display.o: ../Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o.ok ${OBJECTDIR}/_ext/1472/Display.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Display.o.d" -o ${OBJECTDIR}/_ext/1472/Display.o ../Display.c    
	
${OBJECTDIR}/_ext/1472/InicioFimTeste.o: ../InicioFimTeste.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.ok ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d" -o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o ../InicioFimTeste.c    
	
${OBJECTDIR}/_ext/1472/Interrupcao.o: ../Interrupcao.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o.ok ${OBJECTDIR}/_ext/1472/Interrupcao.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Interrupcao.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Interrupcao.o.d" -o ${OBJECTDIR}/_ext/1472/Interrupcao.o ../Interrupcao.c    
	
${OBJECTDIR}/_ext/1472/Reles.o: ../Reles.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o.ok ${OBJECTDIR}/_ext/1472/Reles.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Reles.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Reles.o.d" -o ${OBJECTDIR}/_ext/1472/Reles.o ../Reles.c    
	
${OBJECTDIR}/_ext/1472/bus_master.o: ../bus_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o.ok ${OBJECTDIR}/_ext/1472/bus_master.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/bus_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/bus_master.o.d" -o ${OBJECTDIR}/_ext/1472/bus_master.o ../bus_master.c    
	
${OBJECTDIR}/_ext/1472/Gravador.o: ../Gravador.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o.ok ${OBJECTDIR}/_ext/1472/Gravador.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Gravador.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Gravador.o.d" -o ${OBJECTDIR}/_ext/1472/Gravador.o ../Gravador.c    
	
${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o: ../RotinaTeste_CPU_AMT8000.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.ok ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o.d" -o ${OBJECTDIR}/_ext/1472/RotinaTeste_CPU_AMT8000.o ../RotinaTeste_CPU_AMT8000.c    
	
${OBJECTDIR}/_ext/1472/Placa_principal.o: ../Placa_principal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o.ok ${OBJECTDIR}/_ext/1472/Placa_principal.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Placa_principal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../ANM 2008 MF" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Placa_principal.o.d" -o ${OBJECTDIR}/_ext/1472/Placa_principal.o ../Placa_principal.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_CPU_AMT_8000.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG  -o dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_CPU_AMT_8000.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"../ANM 2008 MF",-L".",-Map="${DISTDIR}/Jiga_Universal_-_ANM_2008_MF.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_CPU_AMT_8000.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_CPU_AMT_8000.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"../ANM 2008 MF",-L".",-Map="${DISTDIR}/Jiga_Universal_-_ANM_2008_MF.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Jiga_CPU_AMT_8000.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
