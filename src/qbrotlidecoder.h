#ifndef Q_BROTLI_DECODER
#define Q_BROTLI_DECODER

#include <QObject>

class QIODevice;

class QBrotliDecoder : public QObject
{
    Q_OBJECT
public:
    QBrotliDecoder(QObject* parent=0);
    ~QBrotliDecoder();

    void setIO(QIODevice* input, QIODevice* output);

public slots:
    void decode();

signals:
    void onProgress(double progress);
    void onDone();
    void onError(QString error);

private:
    QIODevice* m_pInputDevice;
    QIODevice* m_pOutputDevice;

};


#endif
