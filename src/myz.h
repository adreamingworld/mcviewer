#ifndef MYZ_H
#define MYZ_H

#include <zlib.h>
#include <stdio.h>
#include <string.h>

#define CHUNK 16384

int inf(void *source, void **dest, unsigned int uncompressed_length);

#endif /* MYZ_H */
