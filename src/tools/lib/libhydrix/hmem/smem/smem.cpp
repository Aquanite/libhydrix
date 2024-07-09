#include <libhydrix/hmem/smem/smem.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *pdest = static_cast<uint8_t *>(dest);
    const uint8_t *psrc = static_cast<const uint8_t *>(src);

    // Copy in chunks of uint64_t when possible
    size_t num_words = n / sizeof(uint64_t);
    size_t num_bytes = n % sizeof(uint64_t);
    uint64_t *pdest64 = reinterpret_cast<uint64_t *>(pdest);
    const uint64_t *psrc64 = reinterpret_cast<const uint64_t *>(psrc);

    for (size_t i = 0; i < num_words; i++) {
        pdest64[i] = psrc64[i];
    }

    pdest += num_words * sizeof(uint64_t);
    psrc += num_words * sizeof(uint64_t);

    for (size_t i = 0; i < num_bytes; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *p = static_cast<uint8_t *>(s);

    // Fill in chunks of uint64_t when possible
    size_t num_words = n / sizeof(uint64_t);
    size_t num_bytes = n % sizeof(uint64_t);
    uint64_t fill = (uint8_t)c;
    fill |= fill << 8;
    fill |= fill << 16;
    fill |= fill << 32;
    uint64_t *p64 = reinterpret_cast<uint64_t *>(p);

    for (size_t i = 0; i < num_words; i++) {
        p64[i] = fill;
    }

    p += num_words * sizeof(uint64_t);

    for (size_t i = 0; i < num_bytes; i++) {
        p[i] = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = static_cast<uint8_t *>(dest);
    const uint8_t *psrc = static_cast<const uint8_t *>(src);

    if (src > dest) {
        // Forward copy
        size_t num_words = n / sizeof(uint64_t);
        size_t num_bytes = n % sizeof(uint64_t);
        uint64_t *pdest64 = reinterpret_cast<uint64_t *>(pdest);
        const uint64_t *psrc64 = reinterpret_cast<const uint64_t *>(psrc);

        for (size_t i = 0; i < num_words; i++) {
            pdest64[i] = psrc64[i];
        }

        pdest += num_words * sizeof(uint64_t);
        psrc += num_words * sizeof(uint64_t);

        for (size_t i = 0; i < num_bytes; i++) {
            pdest[i] = psrc[i];
        }
    } else if (src < dest) {
        // Backward copy
        pdest += n;
        psrc += n;
        size_t num_words = n / sizeof(uint64_t);
        size_t num_bytes = n % sizeof(uint64_t);
        uint64_t *pdest64 = reinterpret_cast<uint64_t *>(pdest);
        const uint64_t *psrc64 = reinterpret_cast<const uint64_t *>(psrc);

        for (size_t i = 0; i < num_words; i++) {
            pdest64[-i-1] = psrc64[-i-1];
        }

        pdest -= num_words * sizeof(uint64_t);
        psrc -= num_words * sizeof(uint64_t);

        for (size_t i = 0; i < num_bytes; i++) {
            pdest[-i-1] = psrc[-i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = static_cast<const uint8_t *>(s1);
    const uint8_t *p2 = static_cast<const uint8_t *>(s2);

    // Compare in chunks of uint64_t when possible
    size_t num_words = n / sizeof(uint64_t);
    size_t num_bytes = n % sizeof(uint64_t);
    const uint64_t *p1_64 = reinterpret_cast<const uint64_t *>(p1);
    const uint64_t *p2_64 = reinterpret_cast<const uint64_t *>(p2);

    for (size_t i = 0; i < num_words; i++) {
        if (p1_64[i] != p2_64[i]) {
            p1 = reinterpret_cast<const uint8_t *>(&p1_64[i]);
            p2 = reinterpret_cast<const uint8_t *>(&p2_64[i]);
            for (size_t j = 0; j < sizeof(uint64_t); j++) {
                if (p1[j] != p2[j]) {
                    return p1[j] < p2[j] ? -1 : 1;
                }
            }
        }
    }

    p1 = reinterpret_cast<const uint8_t *>(p1_64 + num_words);
    p2 = reinterpret_cast<const uint8_t *>(p2_64 + num_words);

    for (size_t i = 0; i < num_bytes; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

#ifdef __cplusplus
}
#endif
uint64_t _retrieve_total_memory(limine_memmap_response *memmap) {
    uint64_t memsize = 0;
    for (size_t i = 0; i < memmap->entry_count; i++)
    {
        if (memmap->entries[i]->type == 0)
        {
            memsize += memmap->entries[i]->length;
        }
    }
    return memsize;
}