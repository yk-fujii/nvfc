##===- lib/Target/Nvfc/Makefile --------------------------*- Makefile -*-===##
# 
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source 
# License. See LICENSE.TXT for details.
# 
##===----------------------------------------------------------------------===##

LEVEL = ../../..
LIBRARYNAME = LLVMNvfcCodeGen
TARGET = Nvfc

# Make sure that tblgen is run, first thing.
BUILT_SOURCES = NvfcGenRegisterInfo.h.inc NvfcGenRegisterNames.inc \
		NvfcGenRegisterInfo.inc NvfcGenInstrNames.inc \
		NvfcGenInstrInfo.inc NvfcGenAsmWriter.inc \
		NvfcGenDAGISel.inc NvfcGenCallingConv.inc \
		NvfcGenSubtarget.inc

DIRS = AsmPrinter TargetInfo

include $(LEVEL)/Makefile.common

