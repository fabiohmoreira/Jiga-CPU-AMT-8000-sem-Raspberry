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
FINAL_IMAGE=${DISTDIR}/Jiga_AMT_8000_V2_5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Jiga_AMT_8000_V2_5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../ApoioTeste.c ../ConversorAD.c ../Display.c ../InicioFimTeste.c ../Interrupcao.c ../Reles.c ../bus_master.c ../Gravador.c ../Placa_principal.c ../RotinaTeste_AMT8000_V2_5.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/ApoioTeste.o ${OBJECTDIR}/_ext/1472/ConversorAD.o ${OBJECTDIR}/_ext/1472/Display.o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o ${OBJECTDIR}/_ext/1472/Interrupcao.o ${OBJECTDIR}/_ext/1472/Reles.o ${OBJECTDIR}/_ext/1472/bus_master.o ${OBJECTDIR}/_ext/1472/Gravador.o ${OBJECTDIR}/_ext/1472/Placa_principal.o ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/ApoioTeste.o.d ${OBJECTDIR}/_ext/1472/ConversorAD.o.d ${OBJECTDIR}/_ext/1472/Display.o.d ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d ${OBJECTDIR}/_ext/1472/Interrupcao.o.d ${OBJECTDIR}/_ext/1472/Reles.o.d ${OBJECTDIR}/_ext/1472/bus_master.o.d ${OBJECTDIR}/_ext/1472/Gravador.o.d ${OBJECTDIR}/_ext/1472/Placa_principal.o.d ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/ApoioTeste.o ${OBJECTDIR}/_ext/1472/ConversorAD.o ${OBJECTDIR}/_ext/1472/Display.o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o ${OBJECTDIR}/_ext/1472/Interrupcao.o ${OBJECTDIR}/_ext/1472/Reles.o ${OBJECTDIR}/_ext/1472/bus_master.o ${OBJECTDIR}/_ext/1472/Gravador.o ${OBJECTDIR}/_ext/1472/Placa_principal.o ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o

# Source Files
SOURCEFILES=../ApoioTeste.c ../ConversorAD.c ../Display.c ../InicioFimTeste.c ../Interrupcao.c ../Reles.c ../bus_master.c ../Gravador.c ../Placa_principal.c ../RotinaTeste_AMT8000_V2_5.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Jiga_AMT_8000_V2_5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ48GA004
MP_LINKER_FILE_OPTION=,--script=p24FJ48GA004.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/ApoioTeste.o: ../ApoioTeste.c  .generated_files/flags/default/229b3576dd974ddcbde9fd243c7ed2bdd53267e7 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ApoioTeste.c  -o ${OBJECTDIR}/_ext/1472/ApoioTeste.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ApoioTeste.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ConversorAD.o: ../ConversorAD.c  .generated_files/flags/default/7342da79ee2b8bec4f9a769a21751ee3b70eec0a .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ConversorAD.c  -o ${OBJECTDIR}/_ext/1472/ConversorAD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ConversorAD.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Display.o: ../Display.c  .generated_files/flags/default/3232cfd2736808381fa3c4cf89f40a4c604bb4f0 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Display.c  -o ${OBJECTDIR}/_ext/1472/Display.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Display.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/InicioFimTeste.o: ../InicioFimTeste.c  .generated_files/flags/default/afcad252ba904a471879b6932c0db3afb1c50bc7 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../InicioFimTeste.c  -o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Interrupcao.o: ../Interrupcao.c  .generated_files/flags/default/202104fb0af4f5b0049b18711252a35d0e46c62 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Interrupcao.c  -o ${OBJECTDIR}/_ext/1472/Interrupcao.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Interrupcao.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Reles.o: ../Reles.c  .generated_files/flags/default/ad58dc7aad1f8ab65ca4aa6e8692a7004d62f810 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Reles.c  -o ${OBJECTDIR}/_ext/1472/Reles.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Reles.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/bus_master.o: ../bus_master.c  .generated_files/flags/default/70ff7455815b843e3f764123c17c3da5441a56d6 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bus_master.c  -o ${OBJECTDIR}/_ext/1472/bus_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bus_master.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Gravador.o: ../Gravador.c  .generated_files/flags/default/14ab5f57360ff3063c000451339e9f3c38f4c511 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Gravador.c  -o ${OBJECTDIR}/_ext/1472/Gravador.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Gravador.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Placa_principal.o: ../Placa_principal.c  .generated_files/flags/default/ccac344cb3c78d67edb55c6d13882bec217570a8 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Placa_principal.c  -o ${OBJECTDIR}/_ext/1472/Placa_principal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Placa_principal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o: ../RotinaTeste_AMT8000_V2_5.c  .generated_files/flags/default/76dd174e61a97bfe59ea5893682317bff4422b6 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RotinaTeste_AMT8000_V2_5.c  -o ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1472/ApoioTeste.o: ../ApoioTeste.c  .generated_files/flags/default/5de195c2aafeb0bbe5c19c455881ae2fec58f448 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ApoioTeste.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ApoioTeste.c  -o ${OBJECTDIR}/_ext/1472/ApoioTeste.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ApoioTeste.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ConversorAD.o: ../ConversorAD.c  .generated_files/flags/default/ec565bef859408c5022ad6441de2bc44183dac05 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ConversorAD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ConversorAD.c  -o ${OBJECTDIR}/_ext/1472/ConversorAD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ConversorAD.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Display.o: ../Display.c  .generated_files/flags/default/a255a76e4c513aaa007605660d1a68649bd36a9f .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Display.c  -o ${OBJECTDIR}/_ext/1472/Display.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Display.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/InicioFimTeste.o: ../InicioFimTeste.c  .generated_files/flags/default/5e132348fc69b34a30e54831216a495e0659689d .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InicioFimTeste.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../InicioFimTeste.c  -o ${OBJECTDIR}/_ext/1472/InicioFimTeste.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/InicioFimTeste.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Interrupcao.o: ../Interrupcao.c  .generated_files/flags/default/1d43cf5a4429ff4c66668d72f5fc66dcf5b96192 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Interrupcao.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Interrupcao.c  -o ${OBJECTDIR}/_ext/1472/Interrupcao.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Interrupcao.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Reles.o: ../Reles.c  .generated_files/flags/default/34ec4ae6e1b1895a60d09e4084f198e5407260c1 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Reles.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Reles.c  -o ${OBJECTDIR}/_ext/1472/Reles.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Reles.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/bus_master.o: ../bus_master.c  .generated_files/flags/default/d0299644064b114a868251d9f0d4bc793ede7b54 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bus_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bus_master.c  -o ${OBJECTDIR}/_ext/1472/bus_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bus_master.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Gravador.o: ../Gravador.c  .generated_files/flags/default/44b4de215105ebee9616fac57cd48e39aff2c671 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Gravador.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Gravador.c  -o ${OBJECTDIR}/_ext/1472/Gravador.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Gravador.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Placa_principal.o: ../Placa_principal.c  .generated_files/flags/default/d39a7cfdb6ba55c7671dad50055c589bc0c41c77 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Placa_principal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Placa_principal.c  -o ${OBJECTDIR}/_ext/1472/Placa_principal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Placa_principal.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o: ../RotinaTeste_AMT8000_V2_5.c  .generated_files/flags/default/3601ed185f4f8c07f7ecff96bce0aacd701f7184 .generated_files/flags/default/872955d66890500c2e764fa2ba671a156326d720
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RotinaTeste_AMT8000_V2_5.c  -o ${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/RotinaTeste_AMT8000_V2_5.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../ANM 2008 MF" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
${DISTDIR}/Jiga_AMT_8000_V2_5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Jiga_AMT_8000_V2_5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../ANM 2008 MF",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/Jiga_Universal_-_ANM_2008_MF.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Jiga_AMT_8000_V2_5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Jiga_AMT_8000_V2_5.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../ANM 2008 MF",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/Jiga_Universal_-_ANM_2008_MF.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/Jiga_AMT_8000_V2_5.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
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
