//===-- NvfcSelectionDAGInfo.h - Nvfc SelectionDAG Info -----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the Nvfc subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

#ifndef NvfcSELECTIONDAGINFO_H
#define NvfcSELECTIONDAGINFO_H

#include "llvm/Target/TargetSelectionDAGInfo.h"

namespace llvm {

class NvfcTargetMachine;

class NvfcSelectionDAGInfo : public TargetSelectionDAGInfo {
public:
  explicit NvfcSelectionDAGInfo(const NvfcTargetMachine &TM);
  ~NvfcSelectionDAGInfo();
};

}

#endif
