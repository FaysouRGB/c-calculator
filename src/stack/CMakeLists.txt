add_library(stack stack.c)

# Include the header directory for this module.
target_include_directories(stack PUBLIC ${CMAKE_SOURCE_DIR}/src)
