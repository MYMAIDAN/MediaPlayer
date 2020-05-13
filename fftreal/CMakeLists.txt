cmake_minimum_required(VERSION 3.5)

project(fftreadLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})

set(HDR
  Array.h
  Array.hpp
  DynArray.h
  DynArray.hpp
  FFTRealFixLen.h
  FFTRealFixLen.hpp
  FFTRealFixLenParam.h
  FFTRealPassDirect.h
  FFTRealPassDirect.hpp
  FFTRealPassInverse.h
  FFTRealPassInverse.hpp
  FFTRealSelect.h
  FFTRealSelect.hpp
  FFTRealUseTrigo.h
  FFTRealUseTrigo.hpp
  OscSinCos.h
  OscSinCos.hpp
  def.h
  )

set(SRC fftreal_wrapper.cpp)

add_library(${PROJECT_NAME} ${SRC} ${HDR} )

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core )
  
