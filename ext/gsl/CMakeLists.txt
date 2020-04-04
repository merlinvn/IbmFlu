project(gsl_builder C CXX)
include(ExternalProject)

ExternalProject_Add(gsl_project
    GIT_REPOSITORY https://github.com/ampl/gsl.git
    CMAKE_ARGS -DGSL_DISABLE_TESTS=ON -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
    UPDATE_DISCONNECTED 1
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    # Disable install step
    INSTALL_COMMAND ""
    )

# Specify include dir
ExternalProject_Get_Property(gsl_project binary_dir)
set(GSL_INCLUDE_DIR ${binary_dir} PARENT_SCOPE)
set(GSL_LIBRARY_DIR ${binary_dir} PARENT_SCOPE)
