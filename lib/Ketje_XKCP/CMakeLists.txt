add_library(KetjeXKCPImpl
    encrypt.c
    KeccakP-200-compact.c
    Ketjev2.c
    Ket.c
    Ketjev2.inc
    Ket.inc
)

target_include_directories(KetjeXKCPImpl INTERFACE .)