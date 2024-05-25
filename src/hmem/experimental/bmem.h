#pragma once
//bmem = Memory Chunking
//Send warning in preprocessor
#warning "EXPERIMENTAL libhydrix/hmem/experimental/bmem.h, features may be unstable or incomplete"
#include <limine.h>
#include <stdint.h>
#include <stddef.h>
#include "../../hlutil/hlmreq.h"
#include "../../sdefs.h"
#include "../smem/smem.h"

/// @brief A chunk of memory
typedef struct _mem_chunk {
    uint64_t start;
    uint64_t end;
    uint64_t size;
    MemChunk *next;
    MemChunk *prev;
    uint8_t *data;
} MemChunk;