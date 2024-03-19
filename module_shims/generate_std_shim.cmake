# SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
# SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
#
# SPDX-License-Identifier: LGPL-3.0-only

if (NOT DEFINED GENCPPM_PATH)
    message(FATAL_ERROR "GENCPPM_PATH is not defined")
endif()

set(includes
    cstddef
    cstdint
    compare

    concepts
    # coroutine
    any
    bitset
    chrono
    compare
    csetjmp
    csignal
    cstdarg
    cstddef
    cstdlib
    ctime
    # debugging
    expected
    functional
    initializer_list
    optional
    source_location
    tuple
    type_traits
    typeindex
    typeinfo
    utility
    variant
    version
    memory
    memory_resource
    new
    scoped_allocator
    cfloat
    cinttypes
    climits
    cstdint
    limits
    stdfloat
    cassert
    cerrno
    exception
    # stacktrace
    stdexcept
    system_error
    cctype
    charconv
    cstring
    cuchar
    cwchar
    cwctype
    format
    string
    string_view
    array
    deque
    # flat_map
    # flat_set
    forward_list
    list
    map
    # mdspan
    queue
    set
    span
    stack
    unordered_map
    unordered_set
    vector
    iterator
    # generator
    ranges
    algorithm
    execution
    bit
    cfenv
    cmath
    complex
    # linalg
    numbers
    numeric
    random
    ratio
    valarray
    clocale
    codecvt
    locale
    text_encoding
    cstdio
    fstream
    iomanip
    ios
    iosfwd
    iostream
    istream
    ostream
    print
    spanstream
    sstream
    streambuf
    # strstream
    syncstream
    filesystem
    regex
    atomic
    barrier
    condition_variable
    future
    # hazard_pointer
    latch
    mutex
    # rcu
    semaphore
    shared_mutex
    stop_token
    thread
)

set(generated_base_dir ${CMAKE_CURRENT_LIST_DIR}/std_generated)
set(generated_cmakelists_path ${generated_base_dir}/CMakeLists.txt)

file(WRITE ${generated_cmakelists_path} "# Auto generated CMakeLists.txt\n")

set(lib_name_under "gencppm_std")
set(generated_dir ${generated_base_dir}/${lib_name_under})
set(generated_hpp_name ${lib_name_under}.hpp)
set(generated_hpp_path ${generated_dir}/${generated_hpp_name})
set(generated_cppm_name ${lib_name_under}.cppm)
set(generated_cppm_path ${generated_dir}/${generated_cppm_name})
file(MAKE_DIRECTORY ${generated_dir})
file(WRITE ${generated_hpp_path} "// Auto generated inclusion directives for ${lib_full_name}\n")
foreach(header ${includes})
    file(APPEND ${generated_hpp_path} "#include <${header}>\n")
endforeach()

execute_process(
    COMMAND ${GENCPPM_PATH} -M=std -I=${generated_hpp_name} -w=std -w=__gnu_cxx ${generated_hpp_path} -extra-arg=-std=c++23
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GENCPPM_OUTPUT
    RESULT_VARIABLE GENCPPM_RESULT
)
if (NOT GENCPPM_RESULT EQUAL 0)
    message(FATAL_ERROR "gencppm failed for library ${lib_name_under} with code ${GENCPPM_RESULT}")
endif()

file(WRITE ${generated_cppm_path} "${GENCPPM_OUTPUT}")

file(APPEND ${generated_cmakelists_path} "\
add_library(${lib_name_under})\n\
target_sources(${lib_name_under} PUBLIC FILE_SET CXX_MODULES FILES ${lib_name_under}/${generated_cppm_name})\n\
llvm_update_compile_flags(${lib_name_under})\n")
