project(yaml_cpp_builder C CXX)
include(ExternalProject)

ExternalProject_Add(yaml-cpp_project
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    CMAKE_ARGS -DYAML_CPP_BUILD_TESTS=OFF -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
    UPDATE_DISCONNECTED 1
    #    PREFIX ${CMAKE_BINARY_DIR}/ext
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    # Disable install step
    INSTALL_COMMAND ""
    )

# Specify include dir
ExternalProject_Get_Property(yaml-cpp_project source_dir)
set(YAMLCPP_INCLUDE_DIR ${source_dir}/include PARENT_SCOPE)

# Specify MainTest's link libraries
ExternalProject_Get_Property(yaml-cpp_project binary_dir)
set(YAMLCPP_LIBRARY_DIR ${binary_dir} PARENT_SCOPE)
