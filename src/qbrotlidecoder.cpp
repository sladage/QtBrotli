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
