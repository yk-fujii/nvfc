//==-- Nvfc.h - Top-level interface for Nvfc representation --*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM Nvfc backend.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_NVFUC_H
#define LLVM_TARGET_NVFUC_H

#include "llvm/Target/TargetMachine.h"

namespace NvfcCC {
  // Nvfc specific condition code.
  enum CondCodes {
    COND_E  = 0,  // aka COND_Z
    COND_NE = 1,  // aka COND_NZ
    COND_HS = 2,  // aka COND_C
    COND_LO = 3,  // aka COND_NC
    COND_GE = 4,
    COND_L  = 5,

    COND_INVALID = -1
  };
}

namespace llvm {
  class NvfcTargetMachine;
  class FunctionPass;
  class formatted_raw_ostream;

  FunctionPass *createNvfcISelDag(NvfcTargetMachine &TM,
                                    CodeGenOpt::Level OptLevel);

  FunctionPass *createNvfcBranchSelectionPass();

  extern Target TheNvfcTarget;

} // end namespace llvm;

// Defines symbolic names for Nvfc registers.
// This defines a mapping from register name to register number.
#include "NvfcGenRegisterNames.inc"

// Defines symbolic names for the Nvfc instructions.
#include "NvfcGenInstrNames.inc"

#endif
