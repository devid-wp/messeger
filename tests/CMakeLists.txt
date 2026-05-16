cmake_minimum_required(VERSION 3.15)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.10
)
FetchContent_MakeAvailable(Catch2)

add_executable(auth_tests test_auth.cpp)

target_include_directories(auth_tests PRIVATE
  ${CMAKE_SOURCE_DIR}/core/include
)

target_link_libraries(auth_tests PRIVATE
  secure_core
  Catch2::Catch2
)

enable_testing()
add_test(NAME AuthManagerTests COMMAND auth_tests)
