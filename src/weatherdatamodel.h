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
#include <QProgressDialog>
#include "weatherdatapoint.h"
#include "weatherdataperiod.h"

class WeatherDataModel : public QAbstractTableModel
{
public:
    WeatherDataModel();
    bool loadEpw(QString filename);
    bool writeEpw(QString filename);
    bool writeWth(QString filename);
    bool writeWea(QString filename);
    void clear();

    std::string city() const;
    void setCity(std::string city);
    std::string stateProvinceRegion() const;
    void setStateProvinceRegion(std::string stateProvinceRegion);
    std::string country() const;
    void setCountry(std::string country);
    std::string source() const;
    void setSource(std::string source);
    std::string WMO() const;
    void setWMO(std::string WMO);
    double latitude() const;
    std::string latitudeString() const;
    bool setLatitude(double latitude);
    bool setLatitude(std::string latitude);
    double longitude() const;
    std::string longitudeString() const;
    bool setLongitude(double longitude);
    bool setLongitude(std::string longitude);
    double timeZone() const;
    std::string timeZoneString() const;
    bool setTimeZone(double timeZone);
    bool setTimeZone(std::string timeZone);
    double elevation() const;
    std::string elevationString() const;
    bool setElevation(double elevation);
    bool setElevation(std::string elevation);

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
    bool readLocation(QString line);
    bool readDataPeriods(QString line);

    int m_recordsPerHour;
    QVector<WeatherDataPeriod> m_dataPeriods;
    std::string m_city;
    std::string m_stateProvinceRegion;
    std::string m_country;
    std::string m_source;
    std::string m_WMO;
    QString m_latitude;
    QString m_longitude;
    QString m_timeZone;
    QString m_elevation;

    QStringList m_headers;
    QVector<WeatherDataPoint> m_data;
};

#endif // WEATHERDATAMODEL_H
