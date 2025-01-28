add_library(queue queue.c)

# Include the header directory for this module.
target_include_directories(queue PUBLIC ${CMAKE_SOURCE_DIR}/src)
