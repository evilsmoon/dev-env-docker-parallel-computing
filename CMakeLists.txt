cmake_minimum_required(VERSION 3.0.0)
project(mpi-test VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DicomClassifier STATIC IMPORTED)
set_target_properties(DicomClassifier PROPERTIES
    IMPORTED_LOCATION "/home/dicom-classifier/build/libDicomClassifier.a"
    INTERFACE_INCLUDE_DIRECTORIES "/home/dicom-classifier/DicomClassifier"
)

add_executable(mpi-test main.cpp)
target_link_libraries(mpi-test DicomClassifier -ldcmdata -ldcmimgle -ldcmimage -ldcmjpeg -lpthread)

