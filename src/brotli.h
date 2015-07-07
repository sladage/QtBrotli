#ifndef IOUTIL_H
#define IOUTIL_H

#include "../brotli/dec/decode.h"
#include "../brotli/enc/encode.h"

int QIOInputFunction(void* data, uint8_t* buf, size_t count);

BrotliInput initInput(QIODevice* input);

int QIOOutputFunction(void* data, const uint8_t* buf, size_t count);

BrotliInput initOutput(QIODevice* output);

#endif // IOUTIL_H
