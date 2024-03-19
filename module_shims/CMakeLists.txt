# SPDX-FileCopyrightText: (C) 2024 Ashley Hawkins <awhawkins@proton.me>
# SPDX-License-Identifier: LGPL-3.0-only

include(${PROJECT_SOURCE_DIR}/cmake/gencppm.cmake)

# Example usage
if (GENCPPM_CONFIGURE_EXAMPLE_MODULE)
    add_library(gsl_shim)
    target_link_libraries(gsl_shim PUBLIC Microsoft.GSL::GSL)
    init_module_shim(
        # Target name
        gsl_shim
        # Module name
        gsl
        # "Root" headers to include
        HEADERS gsl/gsl
        # Header paths to allow exporting symbols from
        WHITELIST_HEADERS gsl/
    )
endif()

add_subdirectory(llvm_generated)
add_subdirectory(std_generated)
