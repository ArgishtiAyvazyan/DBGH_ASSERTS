cmake_minimum_required(VERSION 3.0.0)
project(DBG_ASSERTS_LIB VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(
        # -Wswitch-default
        -finstrument-functions
        -fpermissive
        -ftrapv
        -fverbose-asm
        -pedantic
        -Waddress
        -Wall
        -Warray-bounds=1
        -Wbool-compare
        -Wbool-operation
        -Wc++11-compat  -Wc++14-compat -Wc++17-compat
        -Wcast-align
        -Wcast-qual
        -Wcatch-value
        -Wchar-subscripts
        -Wcomment
        -Wconversion
        -Wenum-compare
        -Werror
        -Wextra
        -Wfloat-equal
        -Wformat
        -Winit-self
        -Wint-in-bool-context
        -Wlogical-not-parentheses
        -Wmain
        -Wmaybe-uninitialized
        -Wmemset-elt-size
        -Wmemset-transposed-args
        -Wmisleading-indentation
        -Wmissing-attributes
        -Wmultistatement-macros
        -Wnarrowing
        -Wnonnull
        -Wnonnull-compare
        -Wopenmp-simd
        -Wparentheses
        -Wpessimizing-move
        -Wpointer-arith
        -Wreorder
        -Wrestrict
        -Wreturn-type
        -Wsequence-point
        -Wshadow
        -Wsign-compare
        -Wsizeof-pointer-div
        -Wsizeof-pointer-memaccess
        -Wstrict-aliasing
        -Wstrict-overflow=1
        -Wstrict-overflow=5
        -Wswitch
        -Wswitch-enum
        -Wtautological-compare
        -Wtrigraphs
        -Wuninitialized
        -Wunknown-pragmas
        -Wunreachable-code
        -Wunused-function
        -Wunused-label
        -Wunused-value
        -Wunused-variable
        -Wvolatile-register-var
        -Wwrite-strings
#        -Wmissing-braces
    )
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory("include")
add_subdirectory("example")
