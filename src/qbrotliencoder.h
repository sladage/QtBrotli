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

#ifndef Q_BROTLI_ENCODER
#define Q_BROTLI_ENCODER

#include <QObject>

class QIODevice;

class QBrotliEncoder : public QObject
{
    Q_OBJECT
public:
    QBrotliEncoder(QObject* parent=0);
    ~QBrotliEncoder();

    /*!
     * \brief Initialize the encoder.
     * \param input Set the input QIODevice
     * \param output Set the output QIODevice
     */
    void init(QIODevice* input, QIODevice* output);

public slots:
    /*!
     * \brief Start encoding the data from the input device.
     * \param quality Default is 11
     */
    void encode(int quality=11);

signals:
    /*!
     * \brief Reports the current progress.
     * \param progress Value between 0 and 1.
     */
    void onProgress(double progress);
    /*!
     * \brief Called when done.
     */
    void onDone();
    /*!
     * \brief Called when an error occurred. (onDone will also be called)
     * \param error The error message.
     */
    void onError(QString error);

private:
    QIODevice* m_pInputDevice;
    QIODevice* m_pOutputDevice;
};



#endif
