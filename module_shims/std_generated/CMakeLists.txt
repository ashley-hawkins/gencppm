# Auto generated CMakeLists.txt
add_library(gencppm_std)
target_sources(gencppm_std PUBLIC FILE_SET CXX_MODULES FILES gencppm_std/gencppm_std.cppm)
llvm_update_compile_flags(gencppm_std)
