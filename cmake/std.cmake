include(FetchContent)
FetchContent_Declare(
  std_module
  URL "file://${LIBCXX_INSTALLED_DIR}/share/libc++/v1"
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  SYSTEM
)

if(NOT std_module_POPULATED)
  FetchContent_Populate(std_module)
endif()

#
# Adjust project include directories
#

# target_include_directories(std SYSTEM PUBLIC ${LIBCXX_INSTALLED_DIR}/include/c++/v1)

#
# Adjust project compiler flags
#

# target_compile_options(std
# PUBLIC
# -nostdinc++
# )
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-nostdinc++>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-isystem>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:${LIBCXX_INSTALLED_DIR}/include/c++/v1>)

#
# Adjust project linker flags
#

# target_link_options(std
# INTERFACE
# -nostdlib++
# -L${LIBCXX_INSTALLED_DIR}/lib
# -Wl,-rpath,${LIBCXX_INSTALLED_DIR}/lib
# )
add_link_options($<$<COMPILE_LANGUAGE:CXX>:-nostdlib++>)
add_link_options($<$<COMPILE_LANGUAGE:CXX>:-L${LIBCXX_INSTALLED_DIR}/lib>)
add_link_options($<$<COMPILE_LANGUAGE:CXX>:-Wl,-rpath,${LIBCXX_INSTALLED_DIR}/lib>)

#
# Add std static library
#
add_library(std)

target_sources(std
  PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
  ${std_module_SOURCE_DIR}/std.cppm
  ${std_module_SOURCE_DIR}/std.compat.cppm
)

target_compile_options(std
  PRIVATE
  -Wno-reserved-module-identifier
  -Wno-reserved-user-defined-literal
)
link_libraries(
  libc++.a
  libc++abi.a
  libunwind.a
)

#
# Link to the std modules by default
#

# link_libraries(std)
