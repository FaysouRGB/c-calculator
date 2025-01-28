add_library(infix infix.c)

# Include the header directory for this module.
target_include_directories(infix PUBLIC ${CMAKE_SOURCE_DIR}/src)
