include(${PROJECT_SOURCE_DIR}/cmake/gencppm.cmake)

# Example usage
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

add_subdirectory(llvm_generated)
add_subdirectory(std_generated)
