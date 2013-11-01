/**********************************************************************
 *  Copyright (c) 2013, Jason W. DeGraw.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/
#ifndef WEATHERDATAMODEL_H
#define WEATHERDATAMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>
#include "weatherdatapoint.h"

class WeatherDataModel : public QAbstractTableModel
{
public:
    WeatherDataModel();
    bool loadEpw(QString filename);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const
    {
        return 31;
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    //Qt::ItemFlags flags(const QModelIndex & index) const;
    //bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

private:
    QStringList m_headers;
    QVector<WeatherDataPoint> m_data;
};

#endif // WEATHERDATAMODEL_H
