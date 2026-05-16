pybind11_add_module(auth_module auth_module.cpp)
target_include_directories(auth_module PRIVATE
  ${CMAKE_SOURCE_DIR}/core/include
)
target_link_libraries(auth_module PRIVATE
  secure_core
)

pybind11_add_module(crypto_module crypto_module.cpp)
target_include_directories(crypto_module PRIVATE
  ${CMAKE_SOURCE_DIR}/core/include
)
target_link_libraries(crypto_module PRIVATE
  secure_core
)
