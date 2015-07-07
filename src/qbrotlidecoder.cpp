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

#include "qbrotlidecoder.h"
#include <QIODevice>
#include "brotli.h"

QBrotliDecoder::QBrotliDecoder(QObject *parent) : QObject(parent)
{
    m_pInputDevice = nullptr;
    m_pOutputDevice = nullptr;
}

QBrotliDecoder::~QBrotliDecoder()
{

}

void QBrotliDecoder::setIO(QIODevice *in, QIODevice* out)
{
    m_pInputDevice = in;
    m_pOutputDevice = out;
}

void QBrotliDecoder::decode()
{
    if (m_pInputDevice == nullptr || m_pOutputDevice == nullptr)
    {
        emit onError("IO devices not set.");
        return;
    }

    if (m_pInputDevice->isReadable())
    {
        emit onError("Input not readable.");
        return;
    }

    if (m_pOutputDevice->isWritable())
    {
        emit onError("Output not writeable.");
        return;
    }


    BrotliState state;
    qint64 totalsize=-1;

    if (!m_pInputDevice->isSequential())
        total_size = m_pInputDevice->size();

    BrotliStateInit(&state);

    int finish = 0;
    BrotliResult r;

    BrotliInput input = initInput(m_pInputDevice);
    BrotliOutput output = initOutput(m_pOutputDevice);

    for (;;)
    {
        r = BrotliDecompressStreaming(input,output,finish,&state);
        if (r==0)
        {
            //error
            emit onError("Decoding error.");
            break;
        }
        else if (r==1)
        {
            //done
            break;
        }

        if (totalsize!=-1)
            emit onProgress(m_pInputDevice->pos()/totalsize);


        if (m_pInputDevice->atEnd())
            finish=1;
    }

    emit onProgress(1.0);
    emit onDone();

    BrotliStateCleanup(&state);
}
