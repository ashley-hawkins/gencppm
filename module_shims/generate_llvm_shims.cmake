if (NOT DEFINED GENCPPM_PATH)
    message(FATAL_ERROR "GENCPPM_PATH is not defined")
endif()
if (NOT DEFINED LLVM_DIR)
    message(FATAL_ERROR "LLVM_DIR is not defined")
endif()

set(
    wanted_libs
    "clang.AST"
    "clang.ASTMatchers"
    "clang.Basic"
    "clang.Frontend"
    "clang.Lex"
    "clang.Parse"
    "clang.Rewrite"
    "clang.Sema"
    "clang.Support"
    "clang.Tooling"
    "LLVM.Support"
)
set(implicit_includes
    "cstddef"
    "cstdint"
    "compare"
)
set(header_prefix_blacklist
    # Platform specific headers
    "llvm/Support/Windows/"
    "llvm/Support/Solaris/"
    # Broken
    "llvm/Support/ScopedPrinter.h"
)

set(llvm_include_dir ${LLVM_DIR}/include)

set(generated_base_dir ${CMAKE_CURRENT_LIST_DIR}/llvm_generated)
set(generated_cmakelists_path ${generated_base_dir}/CMakeLists.txt)

file(WRITE ${generated_cmakelists_path} "# Auto generated CMakeLists.txt\n")

foreach(lib ${wanted_libs})
    string(REPLACE "." ";" lib_parts ${lib})
    list(GET lib_parts 0 lib_prefix)
    string(TOLOWER ${lib_prefix} lib_prefix_lower)
    list(GET lib_parts 1 lib_name)
    string(TOLOWER ${lib_name} lib_name_lower)
    set(lib_full_name ${lib_prefix}${lib_name})
    set(lib_path ${lib_prefix_lower}/${lib_name})
    list(JOIN lib_parts "_" lib_name_under)
    string(TOLOWER ${lib_name_under} lib_name_under)
    set(headers_path ${llvm_include_dir}/${lib_path})
    file(GLOB_RECURSE headers ${headers_path}/*.h)
    set(headers_relative ${implicit_includes})
    foreach(header ${headers})
        file(RELATIVE_PATH header_rel ${llvm_include_dir} ${header})
        list(APPEND headers_relative ${header_rel})
    endforeach()

    message(STATUS "List of headers for ${lib_full_name}: ${headers_relative}")
    set(generated_dir ${generated_base_dir}/${lib_name_under})
    set(generated_hpp_name ${lib_name_under}.hpp)
    set(generated_hpp_path ${generated_dir}/${generated_hpp_name})
    set(generated_cppm_name ${lib_name_under}.cppm)
    set(generated_cppm_path ${generated_dir}/${generated_cppm_name})
    file(MAKE_DIRECTORY ${generated_dir})
    file(WRITE ${generated_hpp_path} "// Auto generated inclusion directives for ${lib_full_name}\n")
    foreach(header ${headers_relative})
        # Check if the header path starts with any of the blacklisted prefixes
        set(skip_header FALSE)
        foreach(prefix ${header_prefix_blacklist})
            if (header MATCHES "^${prefix}")
                set(skip_header TRUE)
            endif()
        endforeach()
        if (skip_header)
            continue()
        endif()
        file(APPEND ${generated_hpp_path} "#include <${header}>\n")
    endforeach()

    # Execute gencppm -M=${lib} -I=${generated_hpp_name} -H=${lib_path} ${generated_hpp_path} --extra-arg=-I${llvm_include_dir} --extra-arg=-std=c++23
    execute_process(
        COMMAND ${GENCPPM_PATH} -M=${lib} -I=${generated_hpp_name} -H=${lib_path} ${generated_hpp_path} --extra-arg=-I${llvm_include_dir} --extra-arg=-std=c++23
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        OUTPUT_VARIABLE GENCPPM_OUTPUT
        RESULT_VARIABLE GENCPPM_RESULT
    )
    if (NOT GENCPPM_RESULT EQUAL 0)
        message(FATAL_ERROR "gencppm failed for library ${lib} with code ${GENCPPM_RESULT}")
    endif()

    file(WRITE ${generated_cppm_path} "${GENCPPM_OUTPUT}")

    file(APPEND ${generated_cmakelists_path} "\
add_library(${lib_name_under})\n\
target_sources(${lib_name_under} PUBLIC FILE_SET CXX_MODULES FILES ${lib_name_under}/${generated_cppm_name})\n\
llvm_update_compile_flags(${lib_name_under})\n\
target_link_libraries(${lib_name_under} PUBLIC ${lib_full_name})\n\
add_library(${lib_prefix_lower}::${lib_name_lower} ALIAS ${lib_name_under})\n")
endforeach()
