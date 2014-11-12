include_directories( ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_library(LLVMNvfcInfo
  NvfcTargetInfo.cpp
  )

add_dependencies(LLVMNvfcInfo NvfcTable_gen)
