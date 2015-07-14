/****************************************************************************
**
** Brotli library for Qt
**
** Copyright (C) 2015 Stefan Ladage <sladage@gmail.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "qbrotliencoder.h"
#include <QIODevice>
#include "../brotli/enc/encode.h"

#define BUFFER_SIZE 4096

QBrotliEncoder::QBrotliEncoder(QObject *parent) : QObject(parent)
{
    m_pInputDevice = nullptr;
    m_pOutputDevice = nullptr;
}

QBrotliEncoder::~QBrotliEncoder()
{

}

void QBrotliEncoder::init(QIODevice *in, QIODevice* out)
{
    m_pInputDevice = in;
    m_pOutputDevice = out;
}

void QBrotliEncoder::encode(int quality)
{
    if (m_pInputDevice == nullptr || m_pOutputDevice == nullptr)
    {
        emit onError("IO devices not set.");
        return;
    }

    if (!m_pInputDevice->isReadable())
    {
        emit onError("Input not readable.");
        return;
    }

    if (!m_pOutputDevice->isWritable())
    {
        emit onError("Output not writeable.");
        return;
    }

    qint64 totalsize=-1;

    brotli::BrotliParams params;
    params.quality = quality;

    if (!m_pInputDevice->isSequential())
        totalsize = m_pInputDevice->size();

    size_t in_bytes = 0;
    size_t out_bytes = 0;
    uint8_t* input = new uint8_t[BUFFER_SIZE];
    uint8_t* output;
    bool final_block = false;
    brotli::BrotliCompressor compressor(params);

    while (!final_block) {
      qint64 read = m_pInputDevice->read(reinterpret_cast<char*>(input),BUFFER_SIZE);
      if (read == -1)
      {
          emit onError("Read error.");
          break;
      }
      in_bytes = read;
      compressor.CopyInputToRingBuffer(in_bytes,input);
      final_block = in_bytes == 0 || m_pInputDevice->atEnd();
      out_bytes = 0;
      if (!compressor.WriteBrotliData(final_block,
                                      /* force_flush = */ false,
                                      &out_bytes, &output)) {
          //error
          emit onError("Decoding error.");
          break;
      }
      if (out_bytes > 0 && m_pOutputDevice->write(reinterpret_cast<const char*>(output),out_bytes) != out_bytes) {
          //error
          emit onError("Write error.");
          break;
      }

      if (totalsize!=-1)
          emit onProgress((double)m_pInputDevice->pos()/(double)totalsize);
    }

    delete [] input;

    emit onProgress(1.0);
    emit onDone();
}
