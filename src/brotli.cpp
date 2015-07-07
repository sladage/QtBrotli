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
