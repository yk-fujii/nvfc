//===-- NvfcSelectionDAGInfo.cpp - Nvfc SelectionDAG Info -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the NvfcSelectionDAGInfo class.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "nvfc-selectiondag-info"
#include "NvfcTargetMachine.h"
using namespace llvm;

NvfcSelectionDAGInfo::NvfcSelectionDAGInfo(const NvfcTargetMachine &TM)
  : TargetSelectionDAGInfo(TM) {
}

NvfcSelectionDAGInfo::~NvfcSelectionDAGInfo() {
}
