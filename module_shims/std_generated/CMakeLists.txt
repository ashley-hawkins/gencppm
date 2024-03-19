# Auto generated CMakeLists.txt
add_library(std)
target_sources(std PUBLIC FILE_SET CXX_MODULES FILES std/std.cppm)
llvm_update_compile_flags(std)
