//===- NvfcSubtarget.cpp - Nvfc Subtarget Information ---------*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Nvfc specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "NvfcSubtarget.h"
#include "Nvfc.h"
#include "NvfcGenSubtarget.inc"

using namespace llvm;

NvfcSubtarget::NvfcSubtarget(const std::string &TT, const std::string &FS) {
  std::string CPU = "generic";

  // Parse features string.
  ParseSubtargetFeatures(FS, CPU);
}
