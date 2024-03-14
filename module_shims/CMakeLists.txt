include(${PROJECT_SOURCE_DIR}/cmake/gencppm.cmake)

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

set(STD_HEADERS
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
add_library(std)
init_module_shim(
    # Target name
    std
    # Module name
    std
    # "Root" headers to include
    HEADERS ${STD_HEADERS}
    # namespaces to allow exporting symbols from
    WHITELIST_NAMESPACES std
)
