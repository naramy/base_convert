#pragma once

inline void asm_memset(void *dst, const unsigned char src, const unsigned int cnt) {
    #if defined (unix) && !defined (WIN32)
    __asm__ ( "TEST $0x3, %%ecx\n\t"
              "jz _stosl\n\t"
              "TEST $0x1, %%ecx\n\t"
              "jz _stosw\n\t"
              "rep stosb\n\t"
              "jmp _end\n\t"
              "_stosl: movb %1, %%ah\n\t"
              "shl $0x10, %%eax\n\t"
              "movb %1, %%ah\n\t"
              "movb %1, %%al\n\t"
              "shr $0x2, %%ecx\n\t"
              "rep stosl\n\t"
              "jmp _end\n\t"
              "_stosw: movb %1, %%ah\n\t"
              "shr $0x1, %%ecx\n\t"
              "rep stosw\n\t"
              "_end: "            :
                                  : "D" (dst), "a" (src), "c" (cnt));
    #elif defined (WIN32) && !defined (unix)
    __asm {
        mov  eax, src
        mov  ecx, cnt
        mov  edi, dst

        TEST ecx, 03h
        jz   _stosd
        TEST ecx, 01h
        jz   _stosw

        rep  stosb
        jmp  _end

_stosd: mov  ah, src
        shl  eax, 16
        mov  ah, src
        mov  al, src
        shr  ecx, 2

        rep  stosd
        jmp  _end

_stosw: mov  ah, src
        shr  ecx, 1
        rep  stosw
_end:
    }
  #else
    unsigned char *dst_ptr = static_cast<unsigned char *>(dst);
    for(unsigned int i = 0; i < cnt; i++)
        dst_ptr[i] = src;
  #endif
}
