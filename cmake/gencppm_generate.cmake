# SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
# SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
#
# SPDX-License-Identifier: LGPL-3.0-only

file(WRITE "${OUT_FILE}" "#include \"${HEADER_FILE}\"\n")

message(STATUS "Running ${FULL_COMMAND_LINE}")
execute_process(
	COMMAND ${FULL_COMMAND_LINE}
	OUTPUT_VARIABLE OUTPUT
	ERROR_VARIABLE ERROR_OUTPUT
	RESULT_VARIABLE RESULT
)

if(NOT RESULT EQUAL 0)
	message(FATAL_ERROR "gencppm failed: ${ERROR_OUTPUT}")
endif()

message(STATUS "Output: ${OUTPUT}")

file(WRITE "${OUT_FILE}" "${OUTPUT}")
