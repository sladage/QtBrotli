CONFIG += c++11

SOURCES += $$PWD/src/qbrotliencoder.cpp\
        $$PWD/src/qbrotlidecoder.cpp \
    $$PWD/brotli/enc/static_dict.cc \
    $$PWD/brotli/enc/metablock.cc \
    $$PWD/brotli/enc/literal_cost.cc \
    $$PWD/brotli/enc/histogram.cc \
    $$PWD/brotli/enc/entropy_encode.cc \
    $$PWD/brotli/enc/encode_parallel.cc \
    $$PWD/brotli/enc/encode.cc \
    $$PWD/brotli/enc/brotli_bit_stream.cc \
    $$PWD/brotli/enc/block_splitter.cc \
    $$PWD/brotli/enc/backward_references.cc \
    $$PWD/brotli/dec/streams.c \
    $$PWD/brotli/dec/state.c \
    $$PWD/brotli/dec/safe_malloc.c \
    $$PWD/brotli/dec/huffman.c \
    $$PWD/brotli/dec/decode.c \
    $$PWD/brotli/dec/bit_reader.c \
    $$PWD/brotli/enc/encstreams.cc

HEADERS  += $$PWD/src/qbrotliencoder.h\
        $$PWD/src/qbrotlidecoder.h \
    $$PWD/brotli/enc/write_bits.h \
    $$PWD/brotli/enc/transform.h \
    $$PWD/brotli/enc/streams.h \
    $$PWD/brotli/enc/static_dict_lut.h \
    $$PWD/brotli/enc/static_dict.h \
    $$PWD/brotli/enc/ringbuffer.h \
    $$PWD/brotli/enc/prefix.h \
    $$PWD/brotli/enc/port.h \
    $$PWD/brotli/enc/metablock.h \
    $$PWD/brotli/enc/literal_cost.h \
    $$PWD/brotli/enc/histogram.h \
    $$PWD/brotli/enc/hash.h \
    $$PWD/brotli/enc/find_match_length.h \
    $$PWD/brotli/enc/fast_log.h \
    $$PWD/brotli/enc/entropy_encode.h \
    $$PWD/brotli/enc/encode_parallel.h \
    $$PWD/brotli/enc/encode.h \
    $$PWD/brotli/enc/dictionary_hash.h \
    $$PWD/brotli/enc/dictionary.h \
    $$PWD/brotli/enc/context.h \
    $$PWD/brotli/enc/command.h \
    $$PWD/brotli/enc/cluster.h \
    $$PWD/brotli/enc/brotli_bit_stream.h \
    $$PWD/brotli/enc/block_splitter.h \
    $$PWD/brotli/enc/bit_cost.h \
    $$PWD/brotli/enc/backward_references.h \
    $$PWD/brotli/dec/types.h \
    $$PWD/brotli/dec/transform.h \
    $$PWD/brotli/dec/streams.h \
    $$PWD/brotli/dec/state.h \
    $$PWD/brotli/dec/safe_malloc.h \
    $$PWD/brotli/dec/prefix.h \
    $$PWD/brotli/dec/port.h \
    $$PWD/brotli/dec/huffman.h \
    $$PWD/brotli/dec/dictionary.h \
    $$PWD/brotli/dec/decode.h \
    $$PWD/brotli/dec/context.h \
    $$PWD/brotli/dec/bit_reader.h

INCLUDEPATH += $$PWD/src
