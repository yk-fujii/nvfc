//===- NvfcRegisterInfo.cpp - Nvfc Register Information ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Nvfc implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "nvfc-reg-info"

#include "Nvfc.h"
#include "NvfcMachineFunctionInfo.h"
#include "NvfcRegisterInfo.h"
#include "NvfcTargetMachine.h"
#include "llvm/Function.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

// FIXME: Provide proper call frame setup / destroy opcodes.
NvfcRegisterInfo::NvfcRegisterInfo(NvfcTargetMachine &tm,
                                       const TargetInstrInfo &tii)
  : NvfcGenRegisterInfo(Nvfc::ADJCALLSTACKDOWN, Nvfc::ADJCALLSTACKUP),
    TM(tm), TII(tii) {
  StackAlign = TM.getFrameInfo()->getStackAlignment();
}

const unsigned*
NvfcRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  const Function* F = MF->getFunction();
  static const unsigned CalleeSavedRegs[] = {
    Nvfc::FP, Nvfc::R1, Nvfc::R2, Nvfc::R3,
    Nvfc::R4, Nvfc::R5, Nvfc::R6, Nvfc::R7,
    Nvfc::R8, Nvfc::R9, Nvfc::R10, Nvfc::R11,
    0
  };
#if 0
  static const unsigned CalleeSavedRegsIntr[] = {
    Nvfc::FP, Nvfc::R1, Nvfc::R2, Nvfc::R3,
    Nvfc::R4, Nvfc::R5, Nvfc::R6, Nvfc::R7,
    Nvfc::R8, Nvfc::R9, Nvfc::R10, Nvfc::R11,
    Nvfc::R12, Nvfc::R13, Nvfc::R14, Nvfc::R15,
    0
  };
  return (F->getCallingConv() == CallingConv::NVFUC_INTR ?
	  CalleeSavedRegsIntr : CalleeSavedRegs);
#endif
  F->getCallingConv();
  return CalleeSavedRegs;
}

BitVector NvfcRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  // Mark special registers as reserved.
  Reserved.set(Nvfc::FP);  
  Reserved.set(Nvfc::IV0);
  Reserved.set(Nvfc::IV1);
  Reserved.set(Nvfc::S2);
  Reserved.set(Nvfc::TV);
  Reserved.set(Nvfc::SP);
  Reserved.set(Nvfc::PC);
  Reserved.set(Nvfc::XCB);
  Reserved.set(Nvfc::XDB);
  Reserved.set(Nvfc::FLG);
  Reserved.set(Nvfc::CX);
  Reserved.set(Nvfc::CAU);
  Reserved.set(Nvfc::XTG);
  Reserved.set(Nvfc::TS);
  Reserved.set(Nvfc::S13);
  Reserved.set(Nvfc::S14);
  Reserved.set(Nvfc::S15);

  return Reserved;
}

const TargetRegisterClass *
NvfcRegisterInfo::getPointerRegClass(unsigned Kind) const {
  return &Nvfc::GR32RegClass;
}


bool NvfcRegisterInfo::hasFP(const MachineFunction &MF) const {
  return 0;
}

bool NvfcRegisterInfo::hasReservedCallFrame(const MachineFunction &MF) const {
  return !MF.getFrameInfo()->hasVarSizedObjects();
}

void NvfcRegisterInfo::
eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator I) const {
  if (!hasReservedCallFrame(MF)) {
    // If the stack pointer can be changed after prologue, turn the
    // adjcallstackup instruction into a 'sub SP, <amt>' and the
    // adjcallstackdown instruction into 'add SP, <amt>'
    // TODO: consider using push / pop instead of sub + store / add
    MachineInstr *Old = I;
    uint64_t Amount = Old->getOperand(0).getImm();
    if (Amount != 0) {
      // We need to keep the stack aligned properly.  To do this, we round the
      // amount of space needed for the outgoing arguments up to the next
      // alignment boundary.
      Amount = (Amount+StackAlign-1)/StackAlign*StackAlign;

      MachineInstr *New = 0;
      if (Old->getOpcode() == getCallFrameSetupOpcode()) {
        New = BuildMI(MF, Old->getDebugLoc(),
                      TII.get(Nvfc::SUBsi), Nvfc::SP)
          .addReg(Nvfc::SP).addImm(Amount);
      } else {
        assert(Old->getOpcode() == getCallFrameDestroyOpcode());
        // factor out the amount the callee already popped.
        uint64_t CalleeAmt = Old->getOperand(1).getImm();
        Amount -= CalleeAmt;
        if (Amount)
          New = BuildMI(MF, Old->getDebugLoc(),
                        TII.get(Nvfc::ADDsi), Nvfc::SP)
            .addReg(Nvfc::SP).addImm(Amount);
      }

      if (New) {
        // The FLG implicit def is dead.
        New->getOperand(3).setIsDead();

        // Replace the pseudo instruction with a new instruction...
        MBB.insert(I, New);
      }
    }
  } else if (I->getOpcode() == getCallFrameDestroyOpcode()) {
    // If we are performing frame pointer elimination and if the callee pops
    // something off the stack pointer, add it back.
    if (uint64_t CalleeAmt = I->getOperand(1).getImm()) {
      MachineInstr *Old = I;
      MachineInstr *New =
        BuildMI(MF, Old->getDebugLoc(), TII.get(Nvfc::SUBsi),
                Nvfc::SP).addReg(Nvfc::SP).addImm(CalleeAmt);
      // The FLG implicit def is dead.
      New->getOperand(3).setIsDead();

      MBB.insert(I, New);
    }
  }

  MBB.erase(I);
}

void
NvfcRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                        int SPAdj, RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected");

  unsigned i = 0;
  MachineInstr &MI = *II;
  MachineBasicBlock &MBB = *MI.getParent();
  MachineFunction &MF = *MBB.getParent();
  DebugLoc dl = MI.getDebugLoc();
  while (!MI.getOperand(i).isFI()) {
    ++i;
    assert(i < MI.getNumOperands() && "Instr doesn't have FrameIndex operand!");
  }

  int FrameIndex = MI.getOperand(i).getIndex();

  unsigned BasePtr = Nvfc::SP;
  int Offset = MF.getFrameInfo()->getObjectOffset(FrameIndex);

  // Skip the saved PC
  Offset += 4;

  Offset += MF.getFrameInfo()->getStackSize();

  // Fold imm into offset
  Offset += MI.getOperand(i+1).getImm();

  if (MI.getOpcode() == Nvfc::ADDri) {
    // This is actually "load effective address" of the stack slot
    // instruction. We have only two-address instructions, thus we need to
    // expand it into mov + add

    MI.setDesc(TII.get(Nvfc::MOVrs));
    MI.getOperand(i).ChangeToRegister(BasePtr, false);

    if (Offset == 0)
      return;

    // We need to materialize the offset via add instruction.
    unsigned DstReg = MI.getOperand(0).getReg();
    if (Offset < 0)
      BuildMI(MBB, llvm::next(II), dl, TII.get(Nvfc::SUBri), DstReg)
        .addReg(DstReg).addImm(-Offset);
    else
      BuildMI(MBB, llvm::next(II), dl, TII.get(Nvfc::ADDri), DstReg)
        .addReg(DstReg).addImm(Offset);

    return;
  }

  MI.getOperand(i).ChangeToRegister(BasePtr, false);
  MI.getOperand(i+1).ChangeToImmediate(Offset);
}

void
NvfcRegisterInfo::processFunctionBeforeFrameFinalized(MachineFunction &MF)
                                                                         const {
}


void NvfcRegisterInfo::emitPrologue(MachineFunction &MF) const {
  MachineBasicBlock &MBB = MF.front();   // Prolog goes in entry BB
  MachineFrameInfo *MFI = MF.getFrameInfo();
  NvfcMachineFunctionInfo *NvfcFI = MF.getInfo<NvfcMachineFunctionInfo>();
  MachineBasicBlock::iterator MBBI = MBB.begin();
  DebugLoc DL = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();

  // Get the number of bytes to allocate from the FrameInfo.
  uint64_t StackSize = MFI->getStackSize();

  uint64_t NumBytes = StackSize - NvfcFI->getCalleeSavedFrameSize();

  // Skip the callee-saved push instructions.
  while (MBBI != MBB.end() && (MBBI->getOpcode() == Nvfc::PUSHr))
    ++MBBI;

  if (MBBI != MBB.end())
    DL = MBBI->getDebugLoc();

  if (NumBytes) { // adjust stack pointer: SP -= numbytes
    // If there is an SUBri of SP immediately before this instruction, merge
    // the two.
    //NumBytes -= mergeSPUpdates(MBB, MBBI, true);
    // If there is an ADDri or SUBri of SP immediately after this
    // instruction, merge the two instructions.
    // mergeSPUpdatesDown(MBB, MBBI, &NumBytes);

    if (NumBytes) {
      MachineInstr *MI =
        BuildMI(MBB, MBBI, DL, TII.get(Nvfc::SUBsi), Nvfc::SP)
	  .addReg(Nvfc::SP).addImm(NumBytes);
      // The FLG implicit def is dead.
      MI->getOperand(3).setIsDead();
    }
  }
}

void NvfcRegisterInfo::emitEpilogue(MachineFunction &MF,
                                      MachineBasicBlock &MBB) const {
  const MachineFrameInfo *MFI = MF.getFrameInfo();
  NvfcMachineFunctionInfo *NvfcFI = MF.getInfo<NvfcMachineFunctionInfo>();
  MachineBasicBlock::iterator MBBI = prior(MBB.end());
  unsigned RetOpcode = MBBI->getOpcode();
  DebugLoc DL = MBBI->getDebugLoc();

  switch (RetOpcode) {
  case Nvfc::RET:
  case Nvfc::RETI: break;  // These are ok
  default:
    llvm_unreachable("Can only insert epilog into returning blocks");
  }

  // Get the number of bytes to allocate from the FrameInfo
  uint64_t StackSize = MFI->getStackSize();
  unsigned CSSize = NvfcFI->getCalleeSavedFrameSize();
  uint64_t NumBytes = StackSize - CSSize;

  // Skip the callee-saved pop instructions.
  while (MBBI != MBB.begin()) {
    MachineBasicBlock::iterator PI = prior(MBBI);
    unsigned Opc = PI->getOpcode();
    if (Opc != Nvfc::POPr && !PI->getDesc().isTerminator())
      break;
    --MBBI;
  }

  DL = MBBI->getDebugLoc();

  // If there is an ADDri or SUBri of SP immediately before this
  // instruction, merge the two instructions.
  //if (NumBytes || MFI->hasVarSizedObjects())
  //  mergeSPUpdatesUp(MBB, MBBI, StackPtr, &NumBytes);

  if (MFI->hasVarSizedObjects()) {
    assert(1 && "Unexpected FP");
    BuildMI(MBB, MBBI, DL,
            TII.get(Nvfc::MOVrs), Nvfc::SP).addReg(Nvfc::FP);
    if (CSSize) {
      MachineInstr *MI =
        BuildMI(MBB, MBBI, DL,
                TII.get(Nvfc::SUBsi), Nvfc::SP)
        .addReg(Nvfc::SP).addImm(CSSize);
      // The FLG implicit def is dead.
      MI->getOperand(3).setIsDead();
    }
  } else {
    // adjust stack pointer back: SP += numbytes
    if (NumBytes) {
      MachineInstr *MI =
        BuildMI(MBB, MBBI, DL, TII.get(Nvfc::ADDsi), Nvfc::SP)
        .addReg(Nvfc::SP).addImm(NumBytes);
      // The FLG implicit def is dead.
      MI->getOperand(3).setIsDead();
    }
  }
}

unsigned NvfcRegisterInfo::getRARegister() const {
  return Nvfc::PC;
}

unsigned NvfcRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return Nvfc::SP;
}

int NvfcRegisterInfo::getDwarfRegNum(unsigned RegNum, bool isEH) const {
  llvm_unreachable("Not implemented yet!");
  return 0;
}

#include "NvfcGenRegisterInfo.inc"
