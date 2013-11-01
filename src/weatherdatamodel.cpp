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
#include "weatherdatamodel.h"

#include <QFile>
#include <QTextStream>

bool WeatherDataModel::loadEpw(QString filename)
{
    QFile fp(filename);
    if(!fp.open(QFile::ReadOnly))
    {
        std::cout << "Failed to open file '" << filename.toStdString() << "'.";
        return false;
    }
    QTextStream stream(&fp);
    QString line = stream.readLine();
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();

    beginResetModel();
    m_data.clear();
    while(!line.isNull())
    {
        m_data << WeatherDataPoint(line.toStdString());
        line = stream.readLine();
    }
    endResetModel();
    // Need to do checks or something
    //QModelIndex topLeft = index(0, 0);
    //QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);
    //emit dataChanged(topLeft, bottomRight);

    return true;
}

WeatherDataModel::WeatherDataModel()
{
    m_headers << "Date" << "Time" << "Dry Bulb\nTemperature (C)"
              << "Dew Point\nTemperature (C)" << "Relative\nHumidity" << "Atmospheric Station\nPressure (Pa)"
              << "Extraterrestrial\nHorizontal\nRadiation (Wh/m^2)"
              << "Extraterrestrial\nDirect Normal\nRadiation (Wh/m^2)"
              << "Horizontal\nInfrared Radiation\nIntensity (Wh/m^2)" << "Global Horizontal\nRadiation (Wh/m^2)"
              << "Direct Normal\nRadiation (Wh/m^2)" << "Diffuse Horizontal\nRadiation (Wh/m^2)"
              << "Global Horizontal\nIlluminance (lux)" << "Direct Normal\nIlluminance (lux)"
              << "Diffuse Horizontal\nIlluminance (lux)" << "Zenith Luminance\n(Cd/m^2)"
              << "Wind Direction\n(degrees)" << "Wind Speed\n(m/s)" << "Total Sky\nCover"
              << "Opaque Sky\nCover" << "Visibility\n(km)" << "Ceiling Height\n(m)"
              << "Present Weather\nObservation" << "Present Weather\nCodes"
              << "Precipitable\nWater (mm)" << "Aerosol Optical\nDepth (thousanths)" << "Snow Depth\n(cm)"
              << "Days Since\nLast Snowfall" << "Albedo" << "Liquid Precipitation\nDepth (mm)"
              << "Liquid Precipitation\nQuantity (hr)";
}

int WeatherDataModel::rowCount(const QModelIndex & parent) const
{
    return m_data.size();
}

QVariant WeatherDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if (orientation == Qt::Horizontal)
    {
        if(section < 0 || section >= m_headers.size())
        {
            return QVariant();
        }
        return m_headers[section];
    }
    else
    {
        return QString("%1").arg(section+1);
    }
}

QVariant WeatherDataModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }
    switch(index.column())
    {
    case 0:
        return QString("%1/%2").arg(m_data[index.row()].month()).arg(m_data[index.row()].day());
    case 1:
        return QString().sprintf("%02d:%02d",m_data[index.row()].hour(),m_data[index.row()].minute());
    }

    WeatherDataPoint::WeatherDataFieldId id = static_cast<WeatherDataPoint::WeatherDataFieldId>(index.column()+4);
    switch(id)
    {
    case WeatherDataPoint::DryBulbTemperature:
    {
        boost::optional<double> value = m_data[index.row()].dryBulbTemperature();
        if(value)
        {
            //std::cout << value.get() << std::endl;
            return QVariant(value.get());
        }
        break;
    }
    case WeatherDataPoint::DewPointTemperature:
    {
        boost::optional<double> value = m_data[index.row()].dewPointTemperature();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::RelativeHumidity:
    {
        boost::optional<double> value = m_data[index.row()].relativeHumidity();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::AtmosphericStationPressure:
    {
        boost::optional<double> value = m_data[index.row()].atmosphericStationPressure();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::ExtraterrestrialHorizontalRadiation:
    {
        boost::optional<double> value = m_data[index.row()].extraterrestrialHorizontalRadiation();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::ExtraterrestrialDirectNormalRadiation:
    {
        boost::optional<double> value = m_data[index.row()].extraterrestrialDirectNormalRadiation();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::HorizontalInfraredRadiationIntensity:
    {
        boost::optional<double> value = m_data[index.row()].horizontalInfraredRadiationIntensity();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::GlobalHorizontalRadiation:
    {
        boost::optional<double> value = m_data[index.row()].globalHorizontalRadiation();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::DirectNormalRadiation:
    {
        boost::optional<double> value = m_data[index.row()].directNormalRadiation();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::DiffuseHorizontalRadiation:
    {
        boost::optional<double> value = m_data[index.row()].diffuseHorizontalRadiation();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::GlobalHorizontalIlluminance:
    {
        boost::optional<double> value = m_data[index.row()].globalHorizontalIlluminance();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::DirectNormalIlluminance:
    {
        boost::optional<double> value = m_data[index.row()].directNormalIlluminance();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::DiffuseHorizontalIlluminance:
    {
        boost::optional<double> value = m_data[index.row()].diffuseHorizontalIlluminance();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::ZenithLuminance:
    {
        boost::optional<double> value = m_data[index.row()].zenithLuminance();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::WindDirection:
    {
        boost::optional<double> value = m_data[index.row()].windDirection();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::WindSpeed:
    {
        boost::optional<double> value = m_data[index.row()].windSpeed();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::TotalSkyCover:
    {
        boost::optional<double> value = m_data[index.row()].totalSkyCover();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::OpaqueSkyCover:
    {
        boost::optional<double> value = m_data[index.row()].opaqueSkyCover();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::Visibility:
    {
        boost::optional<double> value = m_data[index.row()].visibility();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::CeilingHeight:
    {
        boost::optional<double> value = m_data[index.row()].ceilingHeight();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::PresentWeatherObservation:
    {
        boost::optional<double> value = m_data[index.row()].presentWeatherObservation();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::PresentWeatherCodes:
    {
        boost::optional<int> value = m_data[index.row()].presentWeatherCodes();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::PrecipitableWater:
    {
        boost::optional<double> value = m_data[index.row()].precipitableWater();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::AerosolOpticalDepth:
    {
        boost::optional<double> value = m_data[index.row()].aerosolOpticalDepth();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::SnowDepth:
    {
        boost::optional<double> value = m_data[index.row()].snowDepth();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::DaysSinceLastSnowfall:
    {
        boost::optional<double> value = m_data[index.row()].daysSinceLastSnowfall();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::Albedo:
    {
        boost::optional<double> value = m_data[index.row()].albedo();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::LiquidPrecipitationDepth:
    {
        boost::optional<double> value = m_data[index.row()].liquidPrecipitationDepth();
        if(value)
        {
            return value.get();
        }
        break;
    }
    case WeatherDataPoint::LiquidPrecipitationQuantity:
    {
        boost::optional<double> value = m_data[index.row()].liquidPrecipitationQuantity();
        if(value)
        {
            return value.get();
        }
        break;
    }
    }
/*
    if (index.row() >= stringList.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return stringList.at(index.row());
    else
        return QVariant();
        */
    return QVariant();
}
/*
Qt::ItemFlags WeatherDataModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool WeatherDataModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        //stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}
*/
