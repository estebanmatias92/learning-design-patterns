# Merged header placement (Pitchfork): public headers live next to their
# sources under src/, in subdirectories mirroring the namespace.
#
# Example once the first component lands:
#   src/visitor/shapes/circle.hpp
#   src/visitor/shapes/circle.cpp
#
# No library target yet (scaffolding only). Register sources explicitly here,
# e.g.:
#   add_library(visitor_shapes visitor/shapes/circle.cpp)
#   target_include_directories(visitor_shapes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
