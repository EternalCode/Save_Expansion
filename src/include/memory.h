#ifndef POKEAGB_CORE_MEMORY_H_
#define POKEAGB_CORE_MEMORY_H_

#include "types.h"

#define ADDR_VRAM 0x06000000

void malloc_init(void* mem_start, u32 mem_size);
void* malloc(u32 size);
void* malloc_and_clear(u32 size);
void free(void* ptr);
void* memcpy(void* dst, const void* src, u32 size);
void memset(void* dst, u8 value, u32 size);


#endif /* POKEAGB_CORE_MEMORY_H_ */
