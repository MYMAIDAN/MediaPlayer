cmake_minimum_required(VERSION 3.5)

project(MediaPlayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets multimedia Core REQUIRED)
add_subdirectory("fftreal\\")
include_directories(Headers/)

file(GLOB HEADER
      "Headers/*.h"
)
file(GLOB SOURCE
  "Sources/*.cpp"
  )

    add_executable(MediaPlayer ${HEADER}
     ${SOURCE}
    )
  target_include_directories(MediaPlayer
      PRIVATE
          ${PROJECT_SOURCE_DIR}/Header
  )

  target_link_libraries(MediaPlayer PRIVATE Qt5::Widgets Qt5::Multimedia Qt5::Core fftreadLib)
