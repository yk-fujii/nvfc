//===- NvfcRegisterInfo.td - Nvfc Register defs ----------*- tblgen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source 
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the Nvfc register file
//===----------------------------------------------------------------------===//

class NvfcReg<bits<5> num, string n> : Register<n> {
  field bits<5> Num = num;
  let Namespace = "Nvfc";
}

//===----------------------------------------------------------------------===//
//  Registers
//===----------------------------------------------------------------------===//

def FP  : NvfcReg<0,  "$r0">;
def R1  : NvfcReg<1,  "$r1">;
def R2  : NvfcReg<2,  "$r2">;
def R3  : NvfcReg<3,  "$r3">;
def R4  : NvfcReg<4,  "$r4">;
def R5  : NvfcReg<5,  "$r5">;
def R6  : NvfcReg<6,  "$r6">;
def R7  : NvfcReg<7,  "$r7">;
def R8  : NvfcReg<8,  "$r8">;
def R9  : NvfcReg<9,  "$r9">;
def R10 : NvfcReg<10, "$r10">;
def R11 : NvfcReg<11, "$r11">;
def R12 : NvfcReg<12, "$r12">;
def R13 : NvfcReg<13, "$r13">;
def R14 : NvfcReg<14, "$r14">;
def R15 : NvfcReg<15, "$r15">;

def IV0 : NvfcReg<16,  "$iv0">;
def IV1 : NvfcReg<17,  "$iv1">;
def S2  : NvfcReg<18,  "$s2">; // reserved
def TV  : NvfcReg<19,  "$tv">;
def SP  : NvfcReg<20,  "$sp">;
def PC  : NvfcReg<21,  "$pc">;
def XCB : NvfcReg<22,  "$xcbase">;
def XDB : NvfcReg<23,  "$xdbase">;
def FLG : NvfcReg<24,  "$flags">;
def CX  : NvfcReg<25,  "$cx">;
def CAU : NvfcReg<26, "$cauth">;
def XTG : NvfcReg<27, "$xtargets">;
def TS  : NvfcReg<28, "$tstatus">;
def S13 : NvfcReg<29, "$s13">; // reserved
def S14 : NvfcReg<30, "$s14">; // reserved
def S15 : NvfcReg<31, "$s15">; // reserved

def GR32 : RegisterClass<"Nvfc", [i32], 32,
   // Volatile registers
  [R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15,
   // Pseudo frame register
   FP,
   // Not allocable
   S15, S14, S13, TS, XTG, CAU, CX, FLG, XDB, XCB, PC, SP, TV, S2, IV1, IV0]>
{
  let MethodProtos = [{
    iterator allocation_order_end(const MachineFunction &MF) const;
  }];
  let MethodBodies = [{
    GR32Class::iterator
    GR32Class::allocation_order_end(const MachineFunction &MF) const {
      // last 17 register on the list above is reserved
      return end()-17;
    }
  }];
}
