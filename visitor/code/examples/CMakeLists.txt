# One subdirectory + one binary per demo: examples/<name>/main.cpp.
# Register each demo explicitly (no GLOB), e.g.:
#   add_executable(my_demo my_demo/main.cpp)
#   target_compile_features(my_demo PRIVATE cxx_std_17)
#
add_executable(basic_shapes basic_shapes/main.cpp)
target_compile_features(basic_shapes PRIVATE cxx_std_17)

add_executable(banking banking/main.cpp)
target_compile_features(banking PRIVATE cxx_std_17)

add_executable(document document/main.cpp)
target_compile_features(document PRIVATE cxx_std_17)
