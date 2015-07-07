#ifndef Q_BROTLI_ENCODER
#define Q_BROTLI_ENCODER

#include <QObject>

class QIODevice;

class QBrotliEncoder : public QObject
{
public:
    QBrotliEncoder(QObject* parent=0);
    ~QBrotliEncoder();

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
