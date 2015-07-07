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
