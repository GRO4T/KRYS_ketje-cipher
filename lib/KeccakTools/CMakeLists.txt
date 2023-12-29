add_library(KeccakTools
  bitstring.cpp
  monkey.cpp
  transformations.cpp
  Keccak-f.cpp
)

target_include_directories(KeccakTools INTERFACE .)
