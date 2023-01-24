cmake_minimum_required(VERSION 3.0.0)
project(second-order VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(classification STATIC IMPORTED)
set_target_properties(classification PROPERTIES
    IMPORTED_LOCATION "/home/dip/build/libclassification.a"
    INTERFACE_INCLUDE_DIRECTORIES "/home/dip/classification"
)
add_library(featureExtraction STATIC IMPORTED)
set_target_properties(featureExtraction PROPERTIES
    IMPORTED_LOCATION "/home/dip/build/libfeatureExtraction.a"
    INTERFACE_INCLUDE_DIRECTORIES "/home/dip/feature_ext_sel"
)

add_library(classificationMetrics  STATIC IMPORTED)
set_target_properties(classificationMetrics  PROPERTIES
    IMPORTED_LOCATION "/home/dip/build/libclassificationMetrics.a"
    INTERFACE_INCLUDE_DIRECTORIES "/home/dip/metrics"
)


find_package(OpenMP)

if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(second-order src/main.cpp )
target_link_libraries(second-order classification featureExtraction  classificationMetrics -ldcmdata -ldcmimgle -ldcmimage -ldcmjpeg -lpthread)

