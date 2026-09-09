cmake_minimum_required(VERSION 3.22)
project(cpp_tutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)          # c++20, not gnu++20
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # feeds clang-tidy, cppcheck, IntelliSense

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

option(ENABLE_SANITIZERS       "AddressSanitizer + UndefinedBehaviorSanitizer" ON)
option(ENABLE_STDLIB_ASSERTIONS "Bounds-check vector/string operator[]"        ON)
option(ENABLE_CLANG_TIDY       "Run clang-tidy during every compile"           OFF)

# --------------------------------------------------------------------------
# Shared flags. Anything linking `tutorial_flags` inherits all of this.
# --------------------------------------------------------------------------
add_library(tutorial_flags INTERFACE)

target_compile_options(tutorial_flags INTERFACE
    -Wall -Wextra -Wpedantic
    -Wshadow                # a local/param hiding a member (your lesson_2 ctor)
    -Wconversion -Wsign-conversion   # silent narrowing / signed<->unsigned
    -Wold-style-cast        # forces static_cast<> over C casts
    -Wnon-virtual-dtor      # deleting through a base ptr without virtual dtor
    -Woverloaded-virtual    # accidentally hiding instead of overriding
    -Wnull-dereference
    -Wdouble-promotion      # matters on MCUs with no double FPU
    -Wformat=2
    -Wimplicit-fallthrough
    -Wcast-qual
    -Wunused
    -g
)

if(ENABLE_STDLIB_ASSERTIONS)
    target_compile_definitions(tutorial_flags INTERFACE _GLIBCXX_ASSERTIONS)
endif()

if(ENABLE_SANITIZERS)
    target_compile_options(tutorial_flags INTERFACE
        -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(tutorial_flags INTERFACE
        -fsanitize=address,undefined)
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

# --------------------------------------------------------------------------
# One executable per lesson_* directory. New lessons need no edits here.
# --------------------------------------------------------------------------
file(GLOB lesson_dirs RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
     CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/lesson_*")

foreach(lesson IN LISTS lesson_dirs)
    if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${lesson}")
        continue()
    endif()
    file(GLOB lesson_srcs CONFIGURE_DEPENDS
         "${CMAKE_CURRENT_SOURCE_DIR}/${lesson}/*.cpp")
    if(NOT lesson_srcs)
        continue()
    endif()
    add_executable(${lesson} ${lesson_srcs})
    target_link_libraries(${lesson} PRIVATE tutorial_flags)
    message(STATUS "lesson target: ${lesson}")
endforeach()
