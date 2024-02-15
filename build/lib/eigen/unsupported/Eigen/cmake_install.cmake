# Install script for directory: /home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/AdolcForward"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/AlignedVector3"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/ArpackSupport"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/AutoDiff"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/BVH"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/EulerAngles"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/FFT"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/IterativeSolvers"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/KroneckerProduct"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/LevenbergMarquardt"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/MatrixFunctions"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/MPRealSupport"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/NNLS"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/NonLinearOptimization"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/NumericalDiff"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/OpenGLSupport"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/Polynomials"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/SparseExtra"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/SpecialFunctions"
    "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/Splines"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "/home/brandon/RayTracingInOneWeekend/RayTracer/lib/eigen/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/brandon/RayTracingInOneWeekend/RayTracer/build/lib/eigen/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

