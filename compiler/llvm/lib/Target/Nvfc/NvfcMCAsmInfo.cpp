//===-- NvfcMCAsmInfo.cpp - Nvfc asm properties -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the NvfcMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "NvfcMCAsmInfo.h"
using namespace llvm;

NvfcMCAsmInfo::NvfcMCAsmInfo(const Target &T, StringRef TT) {
  PrivateGlobalPrefix = ".L";
  WeakRefDirective ="\t.weak\t";
  PCSymbol=".";
  CommentString = "//";

  //AlignmentIsInBytes = false;
  AlignmentIsInBytes = true;
  AllowNameToStartWithDigit = true;
  UsesELFSectionDirectiveForBSS = true;
}
