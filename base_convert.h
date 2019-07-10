#pragma once
#include "asm_memset.h"

#define MAX_LEN 64

template <typename T, typename U>
void convert(T &operand, U &base, char *result) {
    constexpr static char base_table[62]
                        {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                        'U', 'V', 'W', 'X', 'Y', 'Z',
                        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                        'u', 'v', 'w', 'x', 'y', 'z'
                       };
    static char tmp[MAX_LEN];
    static unsigned int len{};
    unsigned int i{};

    asm_memset(result, '\0', (len + 1) * sizeof(char));

    for(int idx = 0; operand; i++) {
        #if defined (unix) && !defined (WIN32)
        __asm__ ( "xor  %%edx, %%edx\n\t"
                  "div  %%ebx\n\t"
                         : "=a" (operand), "=d" (idx)
                         : "a" (operand), "b" (base));
        #elif defined (WIN32) && !defined (unix)
        __asm {
            mov eax, operand
            mov ebx, base
            xor edx, edx
            div ebx
            mov operand, eax
            mov idx, edx
        }
        #else
        idx = operand % base;
        operand /= base;
        #endif
        tmp[i] = base_table[idx];
    }

    len = --i;

    do {
        result[len - i] = tmp[i];
    } while(i--);
}
