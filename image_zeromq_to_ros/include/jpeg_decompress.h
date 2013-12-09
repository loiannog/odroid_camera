#ifndef JPEG_DECOMPRESS_H
#define JPEG_DECOMPRESS_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

// If decompressed is NULL, it is automatically allocated
// Responsibility of freeing decompressed is with the user
void jpeg_decompress(const uint8_t *compressed, size_t len, uint8_t **decompressed, int *width, int *height, int *channels);

#ifdef __cplusplus
}
#endif

#endif
