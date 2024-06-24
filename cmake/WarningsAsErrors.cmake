if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")
  target_compile_options(${PROJECT_NAME} INTERFACE /W4 /WX)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(
    ${PROJECT_NAME} INTERFACE -Wall -Wextra -Wpedantic # FIXME -Werror
                                                       -Wshadow
  )

  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 10.0)
    target_compile_options(
      ${PROJECT_NAME} INTERFACE -Wdeprecated-copy-dtor -Wdeprecated-copy -Warray-bounds -Wunused-value -Wnewline-eof
    )
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # TODO: string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  # FIXME target_compile_options(${PROJECT_NAME} INTERFACE /W4 /WX)
endif()
