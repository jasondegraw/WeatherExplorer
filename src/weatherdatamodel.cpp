/**********************************************************************
 *  Copyright (c) 2014, Jason W. DeGraw.
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
#include <QDateTime>

#include "logging.h"

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

bool WeatherDataModel::readLocation(QString line)
{
    QStringList list = line.split(',');
    // Require 10 items in the list
    if(list.size() > 10) {
        LOG(warning) << "Location: Expected 10 entries, got " << list.size();
    } else if(list.size() != 10) {
        LOG(error) << "Location: Expected 10 entries, got " << list.size();
        return false;
    }
    setCity(list[1].toStdString());
    setStateProvinceRegion(list[2].toStdString());
    setCountry(list[3].toStdString());
    setSource(list[4].toStdString());
    setWMO(list[5].toStdString());
    if(!setLatitude(list[6].toStdString())) {
        LOG(error) << QString("Location: Bad latitude value '%1'").arg(list[6]).toStdString();
        return false;
    }
    if(!setLongitude(list[7].toStdString())) {
        LOG(error) << QString("Location: Bad latitude value '%1'").arg(list[7]).toStdString();
        return false;
    }
    if(!setTimeZone(list[8].toStdString())) {
        LOG(error) << QString("Location: Bad time zone value '%1'").arg(list[8]).toStdString();
        return false;
    }
    if(!setElevation(list[9].toStdString())) {
        LOG(error) << QString("Location: Bad elevation value '%1'").arg(list[9]).toStdString();
        return false;
    }
    return true;
}

bool WeatherDataModel::readDataPeriods(QString line)
{
    QStringList list = line.split(',');
    if(list.size()-3 <= 0 || (list.size()-3) % 4 != 0) {
        LOG(error) << "WeatherDataModel: Expected a multiple of 4 plus 3 entries, got " << list.size();
        return false;
    }
    if(list[0].toLower() != "data periods") {
        LOG(error) << "WeatherDataModel: Unexpected section name '" << list[0].toStdString() <<"'";
        return false;
    }
    bool ok;
    int nDataPeriods = list[1].toInt(&ok);
    if((list.size()-3)/4 != nDataPeriods) {
        LOG(error) << "WeatherDataModel: Expected data for " << nDataPeriods << " data periods, found data for "
                   << (list.size()-3)/4;
        return false;
    }
    m_recordsPerHour = list[2].toInt(&ok);
    if(!ok) {
        LOG(error) << "WeatherDataModel: Cannot convert records per hour value '" << list[2].toStdString()
                   << "' into an integer";
        return false;
    } else if(1 > m_recordsPerHour || 60 < m_recordsPerHour)
    {
        LOG(error) << "WeatherDataModel: Records per hour value " << m_recordsPerHour << " out of range";
        return false;
    }
    if(60 % m_recordsPerHour != 0) {
        LOG(error) << "WeatherDataModel: " << m_recordsPerHour << " records per hour does not evenly divide an hour";
        return false;
    }
    m_minutesBetweenRecords = 60/m_recordsPerHour;
    int i=2;
    QString names[7] = {QString("sunday"), QString("monday"), QString("tuesday"), QString("wednesday"),
                        QString("thursday"), QString("friday"), QString("saturday")};
    for(int n=0;n<nDataPeriods;n++){
        std::string name = list[++i].toStdString();
        QString startDay = list[++i].toLower();
        int intDay=0;
        while(startDay != names[intDay]) {
            intDay++;
            if(intDay==7) {
                LOG(error) << "WeatherDataModel: Invalid starting day '" << startDay.toStdString() << "'";
                return false;
            }
        }
        intDay++;
        QString dateString = list[++i].simplified();
        QDate startDate = QDate::fromString(dateString.replace(" ",""),"M/d");
        if(!startDate.isValid()) {
            LOG(error) << "WeatherDataModel: Invalid starting date string '" << list[i].toStdString() << "'";
            return false;
        }
        dateString = list[++i].simplified();
        QDate endDate = QDate::fromString(dateString.replace(" ",""),"M/d");
        if(!endDate.isValid()) {
            LOG(error) << "WeatherDataModel: Invalid ending date string '" << list[i].toStdString() << "'";
            return false;
        }
        // If we got to this point, everything checks out
        m_dataPeriods << WeatherDataPeriod(name,intDay,startDate.month(),startDate.day(),endDate.month(),endDate.day());
    }

    return true;
}

bool WeatherDataModel::loadEpw(QString filename)
{
    int lineNumber=0;
    QFile fp(filename);
    if(!fp.open(QFile::ReadOnly))
    {
        LOG(error) << "WeatherDataModel: Failed to open file '" << filename.toStdString() << "'";
        return false;
    }
    LOG(info) << "WeatherDataModel: Opening file '" << filename.toStdString() << "'";
    QTextStream stream(&fp);
    QString line = stream.readLine();
    lineNumber++;
    if(!readLocation(line)) {
        return false;
    }
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    lineNumber++;
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    lineNumber++;
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    lineNumber++;
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    lineNumber++;
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    lineNumber++;
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    lineNumber++;
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();
    lineNumber++;
    if(!readDataPeriods(line)) {
        LOG(error) << "WeatherDataModel: Failed to read data periods";
        return false;
    }
    LOG(info) << "Read " << m_dataPeriods.size() << " data period(s)";
    for(int i=0;i<m_dataPeriods.size();i++) {
        LOG(info) << "Period " << i+1 <<" : (" << m_dataPeriods[i].name() << ","
                  << m_dataPeriods[i].dayOfWeek() << "," << m_dataPeriods[i].startMonth()
                  << "/" <<  m_dataPeriods[i].startDay() << "," << m_dataPeriods[i].endMonth()
                  << "/" <<  m_dataPeriods[i].endDay() << ")";
    }
    //std::cout << line.toStdString() << std::endl;
    line = stream.readLine();

    beginResetModel();
    m_data.clear();
    int currentMinute = 0;
    while(!line.isNull()){
        lineNumber++;
        boost::optional<WeatherDataPoint> point = WeatherDataPoint::fromEpwString(line.toStdString());
        if(!point) {
            LOG(error) << "Failed to read input line " << lineNumber;
            endResetModel();
            return false;
        }
        if(m_recordsPerHour > 1) {
            point->setMinute(currentMinute);
            currentMinute += m_minutesBetweenRecords;
            if(currentMinute == 60) {
                currentMinute = 0;
            }
        }
        m_data << point.get();
        line = stream.readLine();
    }
    endResetModel();
    // Need to do checks or something
    //QModelIndex topLeft = index(0, 0);
    //QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);
    //emit dataChanged(topLeft, bottomRight);

    return true;
}

bool WeatherDataModel::writeWth(QString filename, int dataPeriodIndex)
{
    QFile fp(filename);
    QString description = "File generated by WeatherExplorer"; // Replace this with something better at some point
    if(!fp.open(QFile::WriteOnly))
    {
        LOG(error) << "WeatherDataModel: Failed to open file '" << filename.toStdString() << "'";
        return false;
    }
    LOG(info) << "WeatherDataModel: Opening file '" << filename.toStdString() << "'";

    QTextStream stream(&fp);
    // Write the header
    stream << "WeatherFile ContamW 2.0" << endl;
    stream << description << endl;
    int day = m_dataPeriods[dataPeriodIndex].startDay();
    int month = m_dataPeriods[dataPeriodIndex].startMonth();
    stream << QString("%1/%2\t!start date").arg(month).arg(day) << endl;
    day = m_dataPeriods[dataPeriodIndex].endDay();
    month = m_dataPeriods[dataPeriodIndex].endMonth();
    stream << QString("%1/%2\t!end date\n").arg(month).arg(day) << endl;
    // Write out the ground temps
    stream << "!Date\tDofW\tDtype\tDST\tTgrnd [K]" << endl;
    // Assume 1 year, hourly for now
    QDateTime endDate = QDateTime(QDate(1999,12,31),QTime(24,0));
    int dayofweek = m_dataPeriods[dataPeriodIndex].dayOfWeek();
    for(QDateTime current = QDateTime(QDate(1999,1,1),QTime(0,0));current<=endDate;current.addSecs(60*60)) {
        stream << QString("%1/%2\t%3\t%3\t0\t283.15\n")
                  .arg(current.date().month())
                  .arg(current.date().day())
                  .arg(dayofweek);
        dayofweek++;
        if(dayofweek > 7) {
            dayofweek=1;
        }
    }

    // Cheat to get data at the start time - this will need to change

    stream <<"!Date\tTime\tTa [K]\tPb [Pa]\tWs [m/s]\tWd [deg]\tHr [g/kg]\tIth [kJ/m^2]\tIdn [kJ/m^2]\tTs [K]\tRn [-]\tSn [-]\n";

    fp.close();
    return true;
}

bool WeatherDataModel::loadWth(QString filename)
{
    QString line;
    QFile fp(filename);
    if(!fp.open(QFile::ReadOnly))
    {
        LOG(error) << "WeatherDataModel: Failed to open file '" << filename.toStdString() << "'";
        return false;
    }

    LOG(info) << "WeatherDataModel: Opening file '" << filename.toStdString() << "'";

    QTextStream stream(&fp);
    // Read the header
    line = stream.readLine();
    if(line != "WeatherFile ContamW 2.0") {
        LOG(error) << "WeatherDataModel: Unrecognized header '" << line.toStdString() <<"'";
        return false;
    }
    stream.readLine(); // Skip the description
    WeatherDataPeriod dataPeriod;
    QStringList list;
    //int day = m_dataPeriods[dataPeriodIndex].startDay();
    //int month = m_dataPeriods[dataPeriodIndex].startMonth();
    line = stream.readLine();
    list = line.split('/');
    //<< QString("%1/%2\t!start date").arg(month).arg(day) << endl;
    //day = m_dataPeriods[dataPeriodIndex].endDay();
    //month = m_dataPeriods[dataPeriodIndex].endMonth();
    //stream << QString("%1/%2\t!end date\n").arg(month).arg(day) << endl;
    //stream << "!Date\tDofW\tDtype\tDST\tTgrnd [K]" << endl;

    LOG(info) << "WeatherDataModel: Clearing weather data";
    clear();
    return true;
}

void WeatherDataModel::clear()
{
    beginResetModel();
    m_city = std::string();
    m_stateProvinceRegion = std::string();
    m_country = std::string();
    m_source = std::string();
    m_WMO = std::string();
    m_latitude = QString();
    m_longitude = QString();
    m_timeZone = QString();
    m_elevation = QString();
    m_data.clear();
    m_dataPeriods.clear();
    endResetModel();
}

std::string WeatherDataModel::city() const
{
    return m_city;
}

void WeatherDataModel::setCity(std::string city)
{
    m_city = city;
}

std::string WeatherDataModel::stateProvinceRegion() const
{
    return m_stateProvinceRegion;
}

void WeatherDataModel::setStateProvinceRegion(std::string stateProvinceRegion)
{
    m_stateProvinceRegion = stateProvinceRegion;
}

std::string WeatherDataModel::country() const
{
    return m_country;
}

void WeatherDataModel::setCountry(std::string country)
{
    m_country = country;
}

std::string WeatherDataModel::source() const
{
    return m_source;
}

void WeatherDataModel::setSource(std::string source)
{
    m_source = source;
}

std::string WeatherDataModel::WMO() const
{
    return m_WMO;
}

void WeatherDataModel::setWMO(std::string WMO)
{
    m_WMO = WMO;
}

double WeatherDataModel::latitude() const
{
    return m_latitude.toDouble();
}

std::string WeatherDataModel::latitudeString() const
{
    return m_latitude.toStdString();
}

bool WeatherDataModel::setLatitude(double latitude)
{
    if(-90.0 > latitude || +90.0 < latitude)
    {
        return false;
    }
    m_latitude = QString("%1").arg(latitude);
    return true;
}

bool WeatherDataModel::setLatitude(std::string latitude)
{
    bool ok;
    double value = QString().fromStdString(latitude).toDouble(&ok);
    if(-90.0 > value || +90.0 < value || !ok)
    {
        return false;
    }
    m_latitude = QString().fromStdString(latitude);
    return true;
}

double WeatherDataModel::longitude() const
{
    return m_longitude.toDouble();
}

std::string WeatherDataModel::longitudeString() const
{
    return m_longitude.toStdString();
}

bool WeatherDataModel::setLongitude(double longitude)
{
    if(-180.0 > longitude || +180.0 < longitude)
    {
        return false;
    }
    m_longitude = QString("%1").arg(longitude);
    return true;
}

bool WeatherDataModel::setLongitude(std::string longitude)
{
    bool ok;
    double value = QString().fromStdString(longitude).toDouble(&ok);
    if(-180.0 > value || +180.0 < value || !ok)
    {
        return false;
    }
    m_longitude = QString().fromStdString(longitude);
    return true;
}

double WeatherDataModel::timeZone() const
{
    return m_timeZone.toDouble();
}

std::string WeatherDataModel::timeZoneString() const
{
    return m_timeZone.toStdString();
}

bool WeatherDataModel::setTimeZone(double timeZone)
{
    if(-12.0 > timeZone || +12.0 < timeZone)
    {
        return false;
    }
    m_timeZone = QString("%1").arg(timeZone);
    return true;
}

bool WeatherDataModel::setTimeZone(std::string timeZone)
{
    bool ok;
    double value = QString().fromStdString(timeZone).toDouble(&ok);
    if(-12.0 > value || +12.0 < value || !ok)
    {
        return false;
    }
    m_timeZone = QString().fromStdString(timeZone);
    return true;
}

double WeatherDataModel::elevation() const
{
    return m_elevation.toDouble();
}

std::string WeatherDataModel::elevationString() const
{
    return m_elevation.toStdString();
}

bool WeatherDataModel::setElevation(double elevation)
{
    if(-1000.0 > elevation)
    {
        return false;
    }
    m_elevation = QString("%1").arg(elevation);
    return true;
}

bool WeatherDataModel::setElevation(std::string elevation)
{
    bool ok;
    double value = QString().fromStdString(elevation).toDouble(&ok);
    if(-1000.0 > value || !ok)
    {
        return false;
    }
    m_elevation = QString().fromStdString(elevation);
    return true;
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
