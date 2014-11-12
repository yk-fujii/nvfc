//=====-- NvfcMCAsmInfo.h - Nvfc asm properties -----------*- C++ -*--====//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source 
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the NvfcMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef NvfcTARGETASMINFO_H
#define NvfcTARGETASMINFO_H

#include "llvm/ADT/StringRef.h"
#include "llvm/MC/MCAsmInfo.h"

namespace llvm {
  class Target;

  struct NvfcMCAsmInfo : public MCAsmInfo {
    explicit NvfcMCAsmInfo(const Target &T, StringRef TT);
  };

} // namespace llvm

#endif
