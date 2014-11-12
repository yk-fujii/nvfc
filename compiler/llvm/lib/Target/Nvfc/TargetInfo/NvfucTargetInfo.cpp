//===-- NvfcTargetInfo.cpp - Nvfc Target Implementation ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Nvfc.h"
#include "llvm/Module.h"
#include "llvm/Target/TargetRegistry.h"
using namespace llvm;

Target llvm::TheNvfcTarget;

extern "C" void LLVMInitializeNvfcTargetInfo() { 
  RegisterTarget<Triple::nvfc> 
    X(TheNvfcTarget, "nvfc", "Nvfc [experimental]");
}
