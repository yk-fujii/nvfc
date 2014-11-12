set(LLVM_TARGET_DEFINITIONS Nvfc.td)

tablegen(NvfcGenRegisterInfo.h.inc -gen-register-desc-header)
tablegen(NvfcGenRegisterNames.inc -gen-register-enums)
tablegen(NvfcGenRegisterInfo.inc -gen-register-desc)
tablegen(NvfcGenInstrNames.inc -gen-instr-enums)
tablegen(NvfcGenInstrInfo.inc -gen-instr-desc)
tablegen(NvfcGenAsmWriter.inc -gen-asm-writer)
tablegen(NvfcGenDAGISel.inc -gen-dag-isel)
tablegen(NvfcGenCallingConv.inc -gen-callingconv)
tablegen(NvfcGenSubtarget.inc -gen-subtarget)

add_llvm_target(NvfcCodeGen
  NvfcBranchSelector.cpp
  NvfcISelDAGToDAG.cpp
  NvfcISelLowering.cpp
  NvfcInstrInfo.cpp
  NvfcMCAsmInfo.cpp
  NvfcRegisterInfo.cpp
  NvfcSubtarget.cpp
  NvfcTargetMachine.cpp
  NvfcSelectionDAGInfo.cpp
  )

target_link_libraries (LLVMNvfcCodeGen LLVMSelectionDAG)
