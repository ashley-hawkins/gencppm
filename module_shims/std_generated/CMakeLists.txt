# Auto generated CMakeLists.txt
if (NOT DEFINED GENCPPM_STDLIB_ID)
    message(FATAL_ERROR "GENCPPM_STDLIB_ID is not defined")
endif()

add_library(gencppm_std)
target_sources(gencppm_std PUBLIC FILE_SET CXX_MODULES FILES gencppm_std-${GENCPPM_STDLIB_ID}/gencppm_std.cppm)
llvm_update_compile_flags(gencppm_std)
