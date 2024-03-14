set(GENCPPM_DIR ${CMAKE_CURRENT_LIST_DIR})

# Function to create a shim target
# function(create_module_shim target_name module_name)
function(init_module_shim target_name module_name)
    set(oneValueArgs MODULE_INCLUDE_NAME WHITELIST_HEADERS)
    set(multiValueArgs HEADERS WHITELIST_NAMESPACES)
    cmake_parse_arguments(PARSE_ARGV 2 ARG "" "${oneValueArgs}" "${multiValueArgs}")

    if (NOT DEFINED ARG_MODULE_INCLUDE_NAME)
        set(ARG_MODULE_INCLUDE_NAME "${module_name}.hpp")
    endif()

#     # Store properties for later use
#     set_target_properties(${target_name} PROPERTIES MODULE_NAME "${module_name}")
#     set_target_properties(${target_name} PROPERTIES MODULE_INCLUDE_NAME "${ARG_MODULE_INCLUDE_NAME}")
#     set_target_properties(${target_name} PROPERTIES WHITELIST_HEADERS "${ARG_WHITELIST_HEADERS}")
#     set_target_properties(${target_name} PROPERTIES MODULE_HEADERS "${ARG_HEADERS}")
# endfunction()

# # Function to initialize the module shim
# function(init_module_shim target_name)
    # get_target_property(module_name ${target_name} MODULE_NAME)
    # get_target_property(MODULE_INCLUDE_NAME ${target_name} MODULE_INCLUDE_NAME)
    # get_target_property(whitelist_headers ${target_name} WHITELIST_HEADERS)
    # get_target_property(module_headers ${target_name} MODULE_HEADERS)

    # Create a directory for generated files if not exists
    set(generated_dir "${CMAKE_BINARY_DIR}/_shim_generated/${module_name}")
    file(MAKE_DIRECTORY ${generated_dir})

    # Generate the header file that includes all headers needed for the module
    set(header_file "${generated_dir}/${ARG_MODULE_INCLUDE_NAME}")
    file(WRITE ${header_file} "// Auto-generated module shim file\n")
    foreach(header ${ARG_HEADERS})
        file(APPEND ${header_file} "#include <${header}>\n")
    endforeach()

    set(output_cppm_file "${generated_dir}/${module_name}.cppm")

    file(WRITE ${output_cppm_file} "#include \"${ARG_MODULE_INCLUDE_NAME}\"\n")

    # Extract the compile flags from the target, prepend with '--extra-arg=' and pass to gencppm
    get_target_property(target_compile_options ${target_name} INTERFACE_COMPILE_OPTIONS)
    get_target_property(target_include_directories ${target_name} INTERFACE_INCLUDE_DIRECTORIES)
    
    if (target_compile_options STREQUAL "target_compile_options-NOTFOUND")
        set(target_compile_options)
    endif()
    if (target_include_directories STREQUAL "target_include_directories-NOTFOUND")
        set(target_include_directories)
    endif()

    get_target_property(target_link_libraries ${target_name} LINK_LIBRARIES)
    if (target_link_libraries STREQUAL "target_link_libraries-NOTFOUND")
        set(target_link_libraries)
    endif()

    foreach(lib ${target_link_libraries})
        get_target_property(linked_target_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)

        if(linked_target_include_dirs STREQUAL "linked_target_include_dirs-NOTFOUND")
            continue()
        endif()

        list(APPEND target_include_directories ${linked_target_include_dirs})
    endforeach()


    set(extra_args)
    foreach(flag ${target_compile_options})
        list(APPEND extra_args "--extra-arg=${flag}")
    endforeach()
    foreach(flag ${target_include_directories})
        list(APPEND extra_args "--extra-arg=-I${flag}")
    endforeach()

    set(header_args)
    foreach(header ${ARG_WHITELIST_HEADERS})
        list(APPEND header_args "-H=${header}")
    endforeach()

    set(whitelist_namespaces)
    foreach(namespace ${ARG_WHITELIST_NAMESPACES})
        list(APPEND whitelist_namespaces "-w=${namespace}")
    endforeach()

    set(full_command_line $<TARGET_FILE:gencppm> -p ${CMAKE_BINARY_DIR} -M ${module_name} -I ${ARG_MODULE_INCLUDE_NAME} ${header_args} ${whitelist_namespaces} ${extra_args} ${output_cppm_file})
    message(STATUS "Full command line: ${full_command_line}")
    string(REPLACE ";" "\\;" escaped_full_command_line "${full_command_line}")

    # Update the custom command to include the extra arguments
    add_custom_command(
        OUTPUT ${output_cppm_file}
        COMMAND cmake -DFULL_COMMAND_LINE="${escaped_full_command_line}" -DOUT_FILE=${output_cppm_file} -DHEADER_FILE=${ARG_MODULE_INCLUDE_NAME} -P ${GENCPPM_DIR}/gencppm_generate.cmake
        DEPENDS ${header_file} gencppm
        COMMENT "Regenerating module shim for ${module_name} with updated compile flags"
    )
    # Add the generated file to the target sources
    target_sources(${target_name} PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES BASE_DIRS ${generated_dir} FILES ${output_cppm_file})
endfunction()
