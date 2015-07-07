#include "brotli.h"

int QIOInputFunction(void* data, uint8_t* buf, size_t count)
{
    QIODevice* io = data;
    if (io->atEnd())
        return 0;
    return io->read((char*)buf,count);
}

BrotliInput initInput(QIODevice* input)
{
    BrotliInput b;
    b.cb_ = &QIOInputFunction;
    b.data_ = input;
}

int QIOOutputFunction(void* data, const uint8_t* buf, size_t count)
{
    QIODevice* io = data;
    return io->write((const char*)buf,count);
}

BrotliInput initOutput(QIODevice* output)
{
    BrotliInput b;
    b.cb_ = &QIOOutputFunction;
    b.data_ = output;
}
