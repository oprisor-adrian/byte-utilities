#[[ 
  Copyright (C) 2023 Oprișor Adrian-Ilie
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
   
  Contact: contact@dev-adrian.com
]]

cmake_minimum_required(VERSION 3.22)
project(byte_utils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_INSTALL_PREFIX /usr/local/${CMAKE_PROJECT_NAME})

add_library(_${CMAKE_PROJECT_NAME} SHARED
  src/byte.cpp
  src/word.cpp
  src/byte_vector.cpp
)

target_include_directories(_${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

install(
  TARGETS _${CMAKE_PROJECT_NAME}
  LIBRARY DESTINATION lib
)
install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
)
install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/cmake/
  DESTINATION cmake
  FILES_MATCHING PATTERN "*.cmake"
)

enable_testing()
add_subdirectory(test/)