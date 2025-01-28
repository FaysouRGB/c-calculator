add_library(utilities utilities.c)

# Include the header directory for this module.
target_include_directories(utilities PUBLIC ${CMAKE_SOURCE_DIR}/src)
