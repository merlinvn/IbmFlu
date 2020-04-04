include_directories("Core" ${YAMLCPP_INCLUDE_DIR} ${GSL_INCLUDE_DIR})
link_directories(${YAMLCPP_LIBRARY_DIR} ${GSL_LIBRARY_DIR})

file(GLOB SRC_FILES *.cpp
    Core/*.cpp
    Core/*.h
    )
add_executable(IbmFlu ${SRC_FILES})

if (WIN32)
  add_dependencies(IbmFlu yaml-cpp_project gsl_project)
endif ()

target_link_libraries(IbmFlu
    yaml-cpp$<$<CONFIG:Debug>:d>
    gsl
    gslcblas
    )

install(TARGETS IbmFlu DESTINATION ${PROJECT_SOURCE_DIR}/bin)