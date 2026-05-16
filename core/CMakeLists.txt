cmake_minimum_required(VERSION 3.15)
project(secure_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")

find_package(OpenSSL REQUIRED)

add_library(secure_core SHARED
  src/auth.cpp
  src/crypto.cpp
)

target_include_directories(secure_core
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(secure_core
  PRIVATE OpenSSL::SSL OpenSSL::Crypto
)
