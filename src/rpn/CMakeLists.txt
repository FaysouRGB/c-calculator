add_library(rpn rpn.c)

# Include the header directory for this module.
target_include_directories(rpn PUBLIC ${CMAKE_SOURCE_DIR}/src)
