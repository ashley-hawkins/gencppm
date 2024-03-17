file(WRITE "${OUT_FILE}" "#include \"${HEADER_FILE}\"\n")

message(STATUS "Running ${FULL_COMMAND_LINE}")
execute_process(COMMAND ${FULL_COMMAND_LINE} OUTPUT_VARIABLE OUTPUT)

message(STATUS "Output: ${OUTPUT}")

file(WRITE "${OUT_FILE}" "${OUTPUT}")
