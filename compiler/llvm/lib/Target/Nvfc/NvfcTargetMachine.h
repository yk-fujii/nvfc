//==-- NvfcTargetMachine.h - Define TargetMachine for Nvfc ---*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Nvfc specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//


#ifndef LLVM_TARGET_NVFUC_TARGETMACHINE_H
#define LLVM_TARGET_NVFUC_TARGETMACHINE_H

#include "NvfcInstrInfo.h"
#include "NvfcISelLowering.h"
#include "NvfcSelectionDAGInfo.h"
#include "NvfcRegisterInfo.h"
#include "NvfcSubtarget.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetFrameInfo.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

/// NvfcTargetMachine
///
class NvfcTargetMachine : public LLVMTargetMachine {
  NvfcSubtarget        Subtarget;
  const TargetData       DataLayout;       // Calculates type size & alignment
  NvfcInstrInfo        InstrInfo;
  NvfcTargetLowering   TLInfo;
  NvfcSelectionDAGInfo TSInfo;

  // Nvfc does not have any call stack frame, therefore not having
  // any Nvfc specific FrameInfo class.
  TargetFrameInfo       FrameInfo;

public:
  NvfcTargetMachine(const Target &T, const std::string &TT,
                      const std::string &FS);

  virtual const TargetFrameInfo *getFrameInfo() const { return &FrameInfo; }
  virtual const NvfcInstrInfo *getInstrInfo() const  { return &InstrInfo; }
  virtual const TargetData *getTargetData() const     { return &DataLayout;}
  virtual const NvfcSubtarget *getSubtargetImpl() const { return &Subtarget; }

  virtual const TargetRegisterInfo *getRegisterInfo() const {
    return &InstrInfo.getRegisterInfo();
  }

  virtual const NvfcTargetLowering *getTargetLowering() const {
    return &TLInfo;
  }

  virtual const NvfcSelectionDAGInfo* getSelectionDAGInfo() const {
    return &TSInfo;
  }

  virtual bool addInstSelector(PassManagerBase &PM, CodeGenOpt::Level OptLevel);
  virtual bool addPreEmitPass(PassManagerBase &PM, CodeGenOpt::Level OptLevel);
}; // NvfcTargetMachine.

} // end namespace llvm

#endif // LLVM_TARGET_NVFUC_TARGETMACHINE_H
