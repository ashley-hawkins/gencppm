# SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
# SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
#
# SPDX-License-Identifier: LGPL-3.0-only

function(PatchUtil_Patch PATCH_ID PATCH_PATH DESTINATION_PATH PATCH_VERSION PATCH_RESULT)
    set(patch_variable_name "_${PATCH_ID}_patch_applied")
    set(_patch_applied ${${patch_variable_name}})

    if (NOT "${_patch_applied}" STREQUAL "${PATCH_VERSION}")
        execute_process(COMMAND git apply --reverse --whitespace=fix --check "${PATCH_PATH}"
                        WORKING_DIRECTORY "${DESTINATION_PATH}"
                        RESULT_VARIABLE _openfbx_patch_reverse_check_result
                        OUTPUT_QUIET ERROR_QUIET)
        if (_openfbx_patch_reverse_check_result EQUAL 0)
            set(${PATCH_RESULT} TRUE PARENT_SCOPE)
            return()
        endif()
        if (DEFINED "${patch_variable_name}")
            execute_process(COMMAND git restore .
                            WORKING_DIRECTORY "${DESTINATION_PATH}"
                            RESULT_VARIABLE _openfbx_patch_result)
        endif()
        execute_process(COMMAND git apply --whitespace=fix "${PATCH_PATH}"
                        WORKING_DIRECTORY "${DESTINATION_PATH}"
                        RESULT_VARIABLE _openfbx_patch_result)
        if (_openfbx_patch_result EQUAL 0)
            set("${patch_variable_name}" "${PATCH_VERSION}" CACHE INTERNAL "" FORCE)
        else()
            set(${PATCH_RESULT} FALSE PARENT_SCOPE)
            return()
        endif()
    endif()
    set(${PATCH_RESULT} TRUE PARENT_SCOPE)
endfunction()
