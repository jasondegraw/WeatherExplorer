/**********************************************************************
 *  Copyright (c) 2013, The Pennsylvania State University.
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
#include "weatherdatapoint.h"
#include <QStringList>
#include <math.h>

#include "logging.h"

WeatherDataPoint::WeatherDataPoint(int year,int month,int day,int hour,int minute,
                                   std::string dataSourceandUncertaintyFlags,double dryBulbTemperature,
                                   double dewPointTemperature,double relativeHumidity,
                                   double atmosphericStationPressure,
                                   double extraterrestrialHorizontalRadiation,
                                   double extraterrestrialDirectNormalRadiation,
                                   double horizontalInfraredRadiationIntensity,
                                   double globalHorizontalRadiation,double directNormalRadiation,
                                   double diffuseHorizontalRadiation,double globalHorizontalIlluminance,
                                   double directNormalIlluminance,double diffuseHorizontalIlluminance,
                                   double zenithLuminance,double windDirection,double windSpeed,
                                   int totalSkyCover,int opaqueSkyCover,double visibility,
                                   double ceilingHeight,int presentWeatherObservation,
                                   int presentWeatherCodes,double precipitableWater,
                                   double aerosolOpticalDepth,double snowDepth,double daysSinceLastSnowfall,
                                   double albedo,double liquidPrecipitationDepth,
                                   double liquidPrecipitationQuantity)
{
    setYear(year);
    setMonth(month);
    setDay(day);
    setHour(hour);
    setMinute(minute);
    setDataSourceandUncertaintyFlags(dataSourceandUncertaintyFlags);
    setDryBulbTemperature(dryBulbTemperature);
    setDewPointTemperature(dewPointTemperature);
    setRelativeHumidity(relativeHumidity);
    setAtmosphericStationPressure(atmosphericStationPressure);
    setExtraterrestrialHorizontalRadiation(extraterrestrialHorizontalRadiation);
    setExtraterrestrialDirectNormalRadiation(extraterrestrialDirectNormalRadiation);
    setHorizontalInfraredRadiationIntensity(horizontalInfraredRadiationIntensity);
    setGlobalHorizontalRadiation(globalHorizontalRadiation);
    setDirectNormalRadiation(directNormalRadiation);
    setDiffuseHorizontalRadiation(diffuseHorizontalRadiation);
    setGlobalHorizontalIlluminance(globalHorizontalIlluminance);
    setDirectNormalIlluminance(directNormalIlluminance);
    setDiffuseHorizontalIlluminance(diffuseHorizontalIlluminance);
    setZenithLuminance(zenithLuminance);
    setWindDirection(windDirection);
    setWindSpeed(windSpeed);
    setTotalSkyCover(totalSkyCover);
    setOpaqueSkyCover(opaqueSkyCover);
    setVisibility(visibility);
    setCeilingHeight(ceilingHeight);
    setPresentWeatherObservation(presentWeatherObservation);
    setPresentWeatherCodes(presentWeatherCodes);
    setPrecipitableWater(precipitableWater);
    setAerosolOpticalDepth(aerosolOpticalDepth);
    setSnowDepth(snowDepth);
    setDaysSinceLastSnowfall(daysSinceLastSnowfall);
    setAlbedo(albedo);
    setLiquidPrecipitationDepth(liquidPrecipitationDepth);
    setLiquidPrecipitationQuantity(liquidPrecipitationQuantity);
}

boost::optional<WeatherDataPoint> WeatherDataPoint::fromEpwString(std::string line, bool readMinutes)
{
    WeatherDataPoint point;
    QStringList list = QString().fromStdString(line).split(',');
    // Require 35 items in the list
    if(list.size() < 35) {
        LOG(error) << "WeatherDataPoint: Expected 35 fields, got " << list.size();
        return boost::optional<WeatherDataPoint>();
    } else if(list.size() > 35) {
        LOG(warning) << "WeatherDataPoint: Expected 35 fields, got " << list.size() <<", additional data ignored";
        return boost::optional<WeatherDataPoint>();
    }
    // Use the appropriate setter on each field
    if(!point.setYear(list[0].toStdString())) {
        return boost::optional<WeatherDataPoint>();
    }
    if(!point.setMonth(list[1].toStdString())) {
        return boost::optional<WeatherDataPoint>();
    }
    if(!point.setDay(list[2].toStdString())) {
        return boost::optional<WeatherDataPoint>();
    }
    if(!point.setHour(list[3].toStdString())) {
        return boost::optional<WeatherDataPoint>();
    }
    if(readMinutes) {
        if(!point.setMinute(list[4].toStdString())) {
            return boost::optional<WeatherDataPoint>();
        }
    }
    point.setDataSourceandUncertaintyFlags(list[5].toStdString());
    point.setDryBulbTemperature(list[6].toStdString());
    point.setDewPointTemperature(list[7].toStdString());
    point.setRelativeHumidity(list[8].toStdString());
    point.setAtmosphericStationPressure(list[9].toStdString());
    point.setExtraterrestrialHorizontalRadiation(list[10].toStdString());
    point.setExtraterrestrialDirectNormalRadiation(list[11].toStdString());
    point.setHorizontalInfraredRadiationIntensity(list[12].toStdString());
    point.setGlobalHorizontalRadiation(list[13].toStdString());
    point.setDirectNormalRadiation(list[14].toStdString());
    point.setDiffuseHorizontalRadiation(list[15].toStdString());
    point.setGlobalHorizontalIlluminance(list[16].toStdString());
    point.setDirectNormalIlluminance(list[17].toStdString());
    point.setDiffuseHorizontalIlluminance(list[18].toStdString());
    point.setZenithLuminance(list[19].toStdString());
    point.setWindDirection(list[20].toStdString());
    point.setWindSpeed(list[21].toStdString());
    point.setTotalSkyCover(list[22].toStdString());
    point.setOpaqueSkyCover(list[23].toStdString());
    point.setVisibility(list[24].toStdString());
    point.setCeilingHeight(list[25].toStdString());
    point.setPresentWeatherObservation(list[26].toStdString());
    point.setPresentWeatherCodes(list[27].toStdString());
    point.setPrecipitableWater(list[28].toStdString());
    point.setAerosolOpticalDepth(list[29].toStdString());
    point.setSnowDepth(list[30].toStdString());
    point.setDaysSinceLastSnowfall(list[31].toStdString());
    point.setAlbedo(list[32].toStdString());
    point.setLiquidPrecipitationDepth(list[33].toStdString());
    point.setLiquidPrecipitationQuantity(list[34].toStdString());
    return boost::optional<WeatherDataPoint>(point);
}

static double psat(double T)
{
    // Compute water vapor saturation pressure, eqns 5 and 6 from ASHRAE Fundamentals 2009 Ch. 1
    double C1 =-5.6745359e+03;
    double C2 = 6.3925247e+00;
    double C3 =-9.6778430e-03;
    double C4 = 6.2215701e-07;
    double C5 = 2.0747825e-09;
    double C6 =-9.4840240e-13;
    double C7 = 4.1635019e+00;
    double C8 =-5.8002206e+03;
    double C9 = 1.3914993e+00;
    double C10=-4.8640239e-02;
    double C11= 4.1764768e-05;
    double C12=-1.4452093e-08;
    double C13= 6.5459673e+00;
    double rhs;
    if(T<273.15)
    {
        rhs = C1/T + C2 + T*(C3 + T*(C4 + T*(C5 + T*C6))) + C7*log(T);
    }
    else
    {
        rhs = C8/T + C9 + T*(C10 + T*(C11 + T*C12)) + C13*log(T);
        rhs = C8/T + C9 + T*C10 + T*T*C11 + T*T*T*C12 + C13*log(T);
    }
    return exp(rhs);
}

boost::optional<std::string> WeatherDataPoint::toWthString()
{
    QStringList output;
    QString date = QString("%1/%2").arg(m_month).arg(m_day);
    output << date;
    QString hms = QString().sprintf("%02d:%02d:00",m_hour,m_minute);
    output << hms;
    boost::optional<double> value = dryBulbTemperature();
    if(!value) {
        LOG(warning) << QString("Missing dry bulb temperature on %1 at %2").arg(date).arg(hms).toStdString();
        return boost::optional<std::string>();
    }
    double drybulb = value.get()+273.15;
    output << QString("%1").arg(drybulb);
    value = atmosphericStationPressure();
    if(!value) {
        LOG(warning) << QString("Missing atmospheric station pressure on %1 at %2").arg(date).arg(hms).toStdString();
        return boost::optional<std::string>();
    }
    double p = value.get();
    output << m_atmosphericStationPressure;
    if(!windSpeed()) {
        LOG(warning) << QString("Missing wind speed on %1 at %2").arg(date).arg(hms).toStdString();
        return boost::optional<std::string>();
    }
    output << m_windSpeed;
    if(!windDirection()) {
        LOG(warning) << QString("Missing wind direction on %1 at %2").arg(date).arg(hms).toStdString();
        return boost::optional<std::string>();
    }
    output << m_windDirection;
    double pw;
    value = relativeHumidity();
    if(!value) { // Don't have relative humidity - this has not been tested
        value = dewPointTemperature();
        if(!value) {
            LOG(warning) << QString("Cannot compute humidity ratio on %1 at %2").arg(date).arg(hms).toStdString();
            return boost::optional<std::string>();
        }
        double dewpoint = value.get()+273.15;
        pw = psat(dewpoint);
    }
    else { // Have relative humidity
        double pws = psat(drybulb);
        pw = 0.01*value.get()*pws;
    }
    double W = 0.621945*pw/(p-pw);
    output << QString("%1").arg(W*1000); // need g/kg
    // Pass on solar flux quantities
    output << "0" << "0";
    // Pass on Tsky
    output << "0";
    // Pass on snow and rain
    output << "0" << "0";
    return boost::optional<std::string>(output.join('\t').toStdString());
}

int WeatherDataPoint::year() const
{
    return m_year;
}

void WeatherDataPoint::setYear(int year)
{
    m_year = year;
}

bool WeatherDataPoint::setYear(std::string year)
{
    bool ok;
    int value = QString().fromStdString(year).toInt(&ok);
    if(!ok) {
        return false;
    }
    m_year = value;
    return true;
}

int WeatherDataPoint::month() const
{
    return m_month;
}

bool WeatherDataPoint::setMonth(int month)
{
    if(1 > month || 12 < month)
    {
        LOG(error) << "WeatherDataPoint: Month value " << month << " out of range.";
        return false;
    }
    m_month = month;
    return true;
}

bool WeatherDataPoint::setMonth(std::string month)
{
    bool ok;
    int value = QString().fromStdString(month).toInt(&ok);
    if(!ok) {
        LOG(error) << "WeatherDataPoint: Cannot convert month value '" << month << "' into an integer.";
        return false;
    } else if(1 > value || 12 < value || !ok)
    {
        LOG(error) << "WeatherDataPoint: Month value " << month << " out of range.";
        return false;
    }
    m_month = value;
    return true;
}

int WeatherDataPoint::day() const
{
    return m_day;
}

bool WeatherDataPoint::setDay(int day)
{
    if(1 > day || 31 < day)
    {
        LOG(error) << "WeatherDataPoint: Day value " << day << " out of range.";
        return false;
    }
    m_day = day;
    return true;
}

bool WeatherDataPoint::setDay(std::string day)
{
    bool ok;
    int value = QString().fromStdString(day).toInt(&ok);
    if(!ok) {
        LOG(error) << "WeatherDataPoint: Cannot convert day value '" << day << "' into an integer.";
        return false;
    } else if(1 > value || 31 < value || !ok)
    {
        LOG(error) << "WeatherDataPoint: Day value " << day << " out of range.";
        return false;
    }
    m_day = value;
    return true;
}

int WeatherDataPoint::hour() const
{
    return m_hour;
}

bool WeatherDataPoint::setHour(int hour)
{
    if(1 > hour || 24 < hour)
    {
        LOG(error) << "WeatherDataPoint: Minute value " << hour << " out of range.";
        return false;
    }
    m_hour = hour;
    return true;
}

bool WeatherDataPoint::setHour(std::string hour)
{
    bool ok;
    int value = QString().fromStdString(hour).toInt(&ok);
    if(!ok) {
        LOG(error) << "WeatherDataPoint: Cannot convert hour value '" << hour << "' into an integer.";
        return false;
    } else if(1 > value || 24 < value || !ok)
    {
        LOG(error) << "WeatherDataPoint: Hour value " << hour << " out of range.";
        return false;
    }
    m_hour = value;
    return true;
}

int WeatherDataPoint::minute() const
{
    return m_minute;
}

bool WeatherDataPoint::setMinute(int minute)
{
    if(0 > minute || 59 < minute) {
        LOG(error) << "WeatherDataPoint: Minute value " << minute << " out of range.";
        return false;
    }
    m_minute = minute;
    return true;
}

bool WeatherDataPoint::setMinute(std::string minute)
{
    bool ok;
    int value = QString().fromStdString(minute).toInt(&ok);
    if(!ok) {
        LOG(error) << "WeatherDataPoint: Cannot convert minute value '" << minute << "' into an integer.";
        return false;
    } else if(0 > value || 59 < value || !ok) {
        LOG(error) << "WeatherDataPoint: Minute value " << minute << " out of range.";
        return false;
    }
    m_minute = value;
    return true;
}

std::string WeatherDataPoint::dataSourceandUncertaintyFlags() const
{
    return m_dataSourceandUncertaintyFlags;
}

void WeatherDataPoint::setDataSourceandUncertaintyFlags(std::string dataSourceandUncertaintyFlags)
{
    m_dataSourceandUncertaintyFlags = dataSourceandUncertaintyFlags;
}

boost::optional<double> WeatherDataPoint::dryBulbTemperature() const
{
    double value = m_dryBulbTemperature.toDouble();
    if(value == 99.9)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setDryBulbTemperature(double dryBulbTemperature)
{
    if(-70 >= dryBulbTemperature)
    {
        m_dryBulbTemperature = "99.9";
        return false;
    }
    m_dryBulbTemperature = QString("%1").arg(dryBulbTemperature);
    return true;
}

bool WeatherDataPoint::setDryBulbTemperature(std::string dryBulbTemperature)
{
    bool ok;
    double value = QString().fromStdString(dryBulbTemperature).toDouble(&ok);
    if(-70 >= value || !ok)
    {
        m_dryBulbTemperature = "99.9";
        return false;
    }
    m_dryBulbTemperature = QString().fromStdString(dryBulbTemperature);
    return true;
}

boost::optional<double> WeatherDataPoint::dewPointTemperature() const
{
    double value = m_dewPointTemperature.toDouble();
    if(value == 99.9)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setDewPointTemperature(double dewPointTemperature)
{
    if(-70 >= dewPointTemperature)
    {
        m_dewPointTemperature = "99.9";
        return false;
    }
    m_dewPointTemperature = QString("%1").arg(dewPointTemperature);
    return true;
}

bool WeatherDataPoint::setDewPointTemperature(std::string dewPointTemperature)
{
    bool ok;
    double value = QString().fromStdString(dewPointTemperature).toDouble(&ok);
    if(-70 >= value || !ok)
    {
        m_dewPointTemperature = "99.9";
        return false;
    }
    m_dewPointTemperature = QString().fromStdString(dewPointTemperature);
    return true;
}

boost::optional<double> WeatherDataPoint::relativeHumidity() const
{
    double value = m_relativeHumidity.toDouble();
    if(value == 999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setRelativeHumidity(double relativeHumidity)
{
    if(0 > relativeHumidity || 110 < relativeHumidity)
    {
        m_relativeHumidity = "999";
        return false;
    }
    m_relativeHumidity = QString("%1").arg(relativeHumidity);
    return true;
}

bool WeatherDataPoint::setRelativeHumidity(std::string relativeHumidity)
{
    bool ok;
    double value = QString().fromStdString(relativeHumidity).toDouble(&ok);
    if(0 > value || 110 < value || !ok)
    {
        m_relativeHumidity = "999";
        return false;
    }
    m_relativeHumidity = QString().fromStdString(relativeHumidity);
    return true;
}

boost::optional<double> WeatherDataPoint::atmosphericStationPressure() const
{
    double value = m_atmosphericStationPressure.toDouble();
    if(value == 999999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setAtmosphericStationPressure(double atmosphericStationPressure)
{
    if(31000 >= atmosphericStationPressure)
    {
        m_atmosphericStationPressure = "999999";
        return false;
    }
    m_atmosphericStationPressure = QString("%1").arg(atmosphericStationPressure);
    return true;
}

bool WeatherDataPoint::setAtmosphericStationPressure(std::string atmosphericStationPressure)
{
    bool ok;
    double value = QString().fromStdString(atmosphericStationPressure).toDouble(&ok);
    if(31000 >= value || !ok)
    {
        m_atmosphericStationPressure = "999999";
        return false;
    }
    m_atmosphericStationPressure = QString().fromStdString(atmosphericStationPressure);
    return true;
}

boost::optional<double> WeatherDataPoint::extraterrestrialHorizontalRadiation() const
{
    double value = m_extraterrestrialHorizontalRadiation.toDouble();
    if(value == 9999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setExtraterrestrialHorizontalRadiation(double extraterrestrialHorizontalRadiation)
{
    if(0 > extraterrestrialHorizontalRadiation)
    {
        m_extraterrestrialHorizontalRadiation = "9999";
        return false;
    }
    m_extraterrestrialHorizontalRadiation = QString("%1").arg(extraterrestrialHorizontalRadiation);
    return true;
}

bool WeatherDataPoint::setExtraterrestrialHorizontalRadiation(std::string extraterrestrialHorizontalRadiation)
{
    bool ok;
    double value = QString().fromStdString(extraterrestrialHorizontalRadiation).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_extraterrestrialHorizontalRadiation = "9999";
        return false;
    }
    m_extraterrestrialHorizontalRadiation = QString().fromStdString(extraterrestrialHorizontalRadiation);
    return true;
}

boost::optional<double> WeatherDataPoint::extraterrestrialDirectNormalRadiation() const
{
    double value = m_extraterrestrialDirectNormalRadiation.toDouble();
    if(value == 9999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setExtraterrestrialDirectNormalRadiation(double extraterrestrialDirectNormalRadiation)
{
    if(0 > extraterrestrialDirectNormalRadiation)
    {
        m_extraterrestrialDirectNormalRadiation = "9999";
        return false;
    }
    m_extraterrestrialDirectNormalRadiation = QString("%1").arg(extraterrestrialDirectNormalRadiation);
    return true;
}

bool WeatherDataPoint::setExtraterrestrialDirectNormalRadiation(std::string extraterrestrialDirectNormalRadiation)
{
    bool ok;
    double value = QString().fromStdString(extraterrestrialDirectNormalRadiation).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_extraterrestrialDirectNormalRadiation = "9999";
        return false;
    }
    m_extraterrestrialDirectNormalRadiation = QString().fromStdString(extraterrestrialDirectNormalRadiation);
    return true;
}

boost::optional<double> WeatherDataPoint::horizontalInfraredRadiationIntensity() const
{
    double value = m_horizontalInfraredRadiationIntensity.toDouble();
    if(value == 9999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setHorizontalInfraredRadiationIntensity(double horizontalInfraredRadiationIntensity)
{
    if(0 > horizontalInfraredRadiationIntensity)
    {
        m_horizontalInfraredRadiationIntensity = "9999";
        return false;
    }
    m_horizontalInfraredRadiationIntensity = QString("%1").arg(horizontalInfraredRadiationIntensity);
    return true;
}

bool WeatherDataPoint::setHorizontalInfraredRadiationIntensity(std::string horizontalInfraredRadiationIntensity)
{
    bool ok;
    double value = QString().fromStdString(horizontalInfraredRadiationIntensity).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_horizontalInfraredRadiationIntensity = "9999";
        return false;
    }
    m_horizontalInfraredRadiationIntensity = QString().fromStdString(horizontalInfraredRadiationIntensity);
    return true;
}

boost::optional<double> WeatherDataPoint::globalHorizontalRadiation() const
{
    double value = m_globalHorizontalRadiation.toDouble();
    if(value == 9999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setGlobalHorizontalRadiation(double globalHorizontalRadiation)
{
    if(0 > globalHorizontalRadiation)
    {
        m_globalHorizontalRadiation = "9999";
        return false;
    }
    m_globalHorizontalRadiation = QString("%1").arg(globalHorizontalRadiation);
    return true;
}

bool WeatherDataPoint::setGlobalHorizontalRadiation(std::string globalHorizontalRadiation)
{
    bool ok;
    double value = QString().fromStdString(globalHorizontalRadiation).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_globalHorizontalRadiation = "9999";
        return false;
    }
    m_globalHorizontalRadiation = QString().fromStdString(globalHorizontalRadiation);
    return true;
}

boost::optional<double> WeatherDataPoint::directNormalRadiation() const
{
    double value = m_directNormalRadiation.toDouble();
    if(value == 9999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setDirectNormalRadiation(double directNormalRadiation)
{
    if(0 > directNormalRadiation)
    {
        m_directNormalRadiation = "9999";
        return false;
    }
    m_directNormalRadiation = QString("%1").arg(directNormalRadiation);
    return true;
}

bool WeatherDataPoint::setDirectNormalRadiation(std::string directNormalRadiation)
{
    bool ok;
    double value = QString().fromStdString(directNormalRadiation).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_directNormalRadiation = "9999";
        return false;
    }
    m_directNormalRadiation = QString().fromStdString(directNormalRadiation);
    return true;
}

boost::optional<double> WeatherDataPoint::diffuseHorizontalRadiation() const
{
    double value = m_diffuseHorizontalRadiation.toDouble();
    if(value == 9999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setDiffuseHorizontalRadiation(double diffuseHorizontalRadiation)
{
    if(0 > diffuseHorizontalRadiation)
    {
        m_diffuseHorizontalRadiation = "9999";
        return false;
    }
    m_diffuseHorizontalRadiation = QString("%1").arg(diffuseHorizontalRadiation);
    return true;
}

bool WeatherDataPoint::setDiffuseHorizontalRadiation(std::string diffuseHorizontalRadiation)
{
    bool ok;
    double value = QString().fromStdString(diffuseHorizontalRadiation).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_diffuseHorizontalRadiation = "9999";
        return false;
    }
    m_diffuseHorizontalRadiation = QString().fromStdString(diffuseHorizontalRadiation);
    return true;
}

boost::optional<double> WeatherDataPoint::globalHorizontalIlluminance() const
{
    double value = m_globalHorizontalIlluminance.toDouble();
    if(value == 999999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setGlobalHorizontalIlluminance(double globalHorizontalIlluminance)
{
    if(0 > globalHorizontalIlluminance)
    {
        m_globalHorizontalIlluminance = "999999";
        return false;
    }
    m_globalHorizontalIlluminance = QString("%1").arg(globalHorizontalIlluminance);
    return true;
}

bool WeatherDataPoint::setGlobalHorizontalIlluminance(std::string globalHorizontalIlluminance)
{
    bool ok;
    double value = QString().fromStdString(globalHorizontalIlluminance).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_globalHorizontalIlluminance = "999999";
        return false;
    }
    m_globalHorizontalIlluminance = QString().fromStdString(globalHorizontalIlluminance);
    return true;
}

boost::optional<double> WeatherDataPoint::directNormalIlluminance() const
{
    double value = m_directNormalIlluminance.toDouble();
    if(value == 999999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setDirectNormalIlluminance(double directNormalIlluminance)
{
    if(0 > directNormalIlluminance)
    {
        m_directNormalIlluminance = "999999";
        return false;
    }
    m_directNormalIlluminance = QString("%1").arg(directNormalIlluminance);
    return true;
}

bool WeatherDataPoint::setDirectNormalIlluminance(std::string directNormalIlluminance)
{
    bool ok;
    double value = QString().fromStdString(directNormalIlluminance).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_directNormalIlluminance = "999999";
        return false;
    }
    m_directNormalIlluminance = QString().fromStdString(directNormalIlluminance);
    return true;
}

boost::optional<double> WeatherDataPoint::diffuseHorizontalIlluminance() const
{
    double value = m_diffuseHorizontalIlluminance.toDouble();
    if(value == 999999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setDiffuseHorizontalIlluminance(double diffuseHorizontalIlluminance)
{
    if(0 > diffuseHorizontalIlluminance)
    {
        m_diffuseHorizontalIlluminance = "999999";
        return false;
    }
    m_diffuseHorizontalIlluminance = QString("%1").arg(diffuseHorizontalIlluminance);
    return true;
}

bool WeatherDataPoint::setDiffuseHorizontalIlluminance(std::string diffuseHorizontalIlluminance)
{
    bool ok;
    double value = QString().fromStdString(diffuseHorizontalIlluminance).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_diffuseHorizontalIlluminance = "999999";
        return false;
    }
    m_diffuseHorizontalIlluminance = QString().fromStdString(diffuseHorizontalIlluminance);
    return true;
}

boost::optional<double> WeatherDataPoint::zenithLuminance() const
{
    double value = m_zenithLuminance.toDouble();
    if(value == 9999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setZenithLuminance(double zenithLuminance)
{
    if(0 > zenithLuminance)
    {
        m_zenithLuminance = "9999";
        return false;
    }
    m_zenithLuminance = QString("%1").arg(zenithLuminance);
    return true;
}

bool WeatherDataPoint::setZenithLuminance(std::string zenithLuminance)
{
    bool ok;
    double value = QString().fromStdString(zenithLuminance).toDouble(&ok);
    if(0 > value || !ok)
    {
        m_zenithLuminance = "9999";
        return false;
    }
    m_zenithLuminance = QString().fromStdString(zenithLuminance);
    return true;
}

boost::optional<double> WeatherDataPoint::windDirection() const
{
    double value = m_windDirection.toDouble();
    if(value == 999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setWindDirection(double windDirection)
{
    if(0 > windDirection || 360 < windDirection)
    {
        m_windDirection = "999";
        return false;
    }
    m_windDirection = QString("%1").arg(windDirection);
    return true;
}

bool WeatherDataPoint::setWindDirection(std::string windDirection)
{
    bool ok;
    double value = QString().fromStdString(windDirection).toDouble(&ok);
    if(0 > value || 360 < value || !ok)
    {
        m_windDirection = "999";
        return false;
    }
    m_windDirection = QString().fromStdString(windDirection);
    return true;
}

boost::optional<double> WeatherDataPoint::windSpeed() const
{
    double value = m_windSpeed.toDouble();
    if(value == 999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

bool WeatherDataPoint::setWindSpeed(double windSpeed)
{
    if(0 > windSpeed || 40 < windSpeed)
    {
        m_windSpeed = "999";
        return false;
    }
    m_windSpeed = QString("%1").arg(windSpeed);
    return true;
}

bool WeatherDataPoint::setWindSpeed(std::string windSpeed)
{
    bool ok;
    double value = QString().fromStdString(windSpeed).toDouble(&ok);
    if(0 > value || 40 < value || !ok)
    {
        m_windSpeed = "999";
        return false;
    }
    m_windSpeed = QString().fromStdString(windSpeed);
    return true;
}

boost::optional<double> WeatherDataPoint::totalSkyCover() const
{
  double value = m_totalSkyCover.toDouble();
  if(value == 99)
  {
      return boost::optional<double>();
  }
  return boost::optional<double>(value);
}

bool WeatherDataPoint::setTotalSkyCover(double totalSkyCover)
{
    if(0 > totalSkyCover || 10 < totalSkyCover)
    {
        m_totalSkyCover = "99";
        return false;
    }
    m_totalSkyCover = QString("%1").arg(totalSkyCover);
    return true;
}

bool WeatherDataPoint::setTotalSkyCover(std::string totalSkyCover)
{
    bool ok;
    int value = QString().fromStdString(totalSkyCover).toInt(&ok);
    if(0 > value || 10 < value || !ok)
    {
        m_totalSkyCover = 99;
        return false;
    }
    m_totalSkyCover = value;
    return true;
}

boost::optional<double> WeatherDataPoint::opaqueSkyCover() const
{
  double value = m_opaqueSkyCover.toDouble();
  if(value == 99)
  {
      return boost::optional<double>();
  }
  return boost::optional<double>(value);
}

bool WeatherDataPoint::setOpaqueSkyCover(double opaqueSkyCover)
{
    if(0 > opaqueSkyCover || 10 < opaqueSkyCover)
    {
        m_opaqueSkyCover = "99";
        return false;
    }
    m_opaqueSkyCover = opaqueSkyCover;
    return true;
}

bool WeatherDataPoint::setOpaqueSkyCover(std::string opaqueSkyCover)
{
    bool ok;
    int value = QString().fromStdString(opaqueSkyCover).toInt(&ok);
    if(0 > value || 10 < value || !ok)
    {
        m_opaqueSkyCover = 99;
        return false;
    }
    m_opaqueSkyCover = value;
    return true;
}

boost::optional<double> WeatherDataPoint::visibility() const
{
    double value = m_visibility.toDouble();
    if(value == 9999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

void WeatherDataPoint::setVisibility(double visibility)
{
    m_visibility = QString("%1").arg(visibility);
}

bool WeatherDataPoint::setVisibility(std::string visibility)
{
    bool ok;
    QString().fromStdString(visibility).toDouble(&ok);
    if(!ok)
    {
        m_visibility = "9999";
        return false;
    }
    m_visibility = QString().fromStdString(visibility);
    return true;
}

boost::optional<double> WeatherDataPoint::ceilingHeight() const
{
    double value = m_ceilingHeight.toDouble();
    if(value == 99999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

void WeatherDataPoint::setCeilingHeight(double ceilingHeight)
{
    m_ceilingHeight = QString("%1").arg(ceilingHeight);
}

bool WeatherDataPoint::setCeilingHeight(std::string ceilingHeight)
{
    bool ok;
    QString().fromStdString(ceilingHeight).toDouble(&ok);
    if(!ok)
    {
        m_ceilingHeight = "99999";
        return false;
    }
    m_ceilingHeight = QString().fromStdString(ceilingHeight);
    return true;
}

int WeatherDataPoint::presentWeatherObservation() const
{
    return m_presentWeatherObservation;
}

void WeatherDataPoint::setPresentWeatherObservation(int presentWeatherObservation)
{
    m_presentWeatherObservation = presentWeatherObservation;
}

bool WeatherDataPoint::setPresentWeatherObservation(std::string presentWeatherObservation)
{
    bool ok;
    int value = QString().fromStdString(presentWeatherObservation).toInt(&ok);
    if(!ok)
    {
        return false;
    }
    m_presentWeatherObservation = value;
    return true;
}

int WeatherDataPoint::presentWeatherCodes() const
{
    return m_presentWeatherCodes;
}

void WeatherDataPoint::setPresentWeatherCodes(int presentWeatherCodes)
{
    m_presentWeatherCodes = presentWeatherCodes;
}

bool WeatherDataPoint::setPresentWeatherCodes(std::string presentWeatherCodes)
{
    bool ok;
    int value = QString().fromStdString(presentWeatherCodes).toInt(&ok);
    if(!ok)
    {
        return false;
    }
    m_presentWeatherCodes = value;
    return true;
}

boost::optional<double> WeatherDataPoint::precipitableWater() const
{
    double value = m_precipitableWater.toDouble();
    if(value == 999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

void WeatherDataPoint::setPrecipitableWater(double precipitableWater)
{
    m_precipitableWater = QString("%1").arg(precipitableWater);
}

bool WeatherDataPoint::setPrecipitableWater(std::string precipitableWater)
{
    bool ok;
    QString().fromStdString(precipitableWater).toDouble(&ok);
    if(!ok)
    {
        m_precipitableWater = "999";
        return false;
    }
    m_precipitableWater = QString().fromStdString(precipitableWater);
    return true;
}

boost::optional<double> WeatherDataPoint::aerosolOpticalDepth() const
{
    double value = m_aerosolOpticalDepth.toDouble();
    if(value == .999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

void WeatherDataPoint::setAerosolOpticalDepth(double aerosolOpticalDepth)
{
    m_aerosolOpticalDepth = QString("%1").arg(aerosolOpticalDepth);
}

bool WeatherDataPoint::setAerosolOpticalDepth(std::string aerosolOpticalDepth)
{
    bool ok;
    QString().fromStdString(aerosolOpticalDepth).toDouble(&ok);
    if(!ok)
    {
        m_aerosolOpticalDepth = ".999";
        return false;
    }
    m_aerosolOpticalDepth = QString().fromStdString(aerosolOpticalDepth);
    return true;
}

boost::optional<double> WeatherDataPoint::snowDepth() const
{
    double value = m_snowDepth.toDouble();
    if(value == 999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

void WeatherDataPoint::setSnowDepth(double snowDepth)
{
    m_snowDepth = QString("%1").arg(snowDepth);
}

bool WeatherDataPoint::setSnowDepth(std::string snowDepth)
{
    bool ok;
    QString().fromStdString(snowDepth).toDouble(&ok);
    if(!ok)
    {
        m_snowDepth = "999";
        return false;
    }
    m_snowDepth = QString().fromStdString(snowDepth);
    return true;
}

boost::optional<double> WeatherDataPoint::daysSinceLastSnowfall() const
{
    double value = m_daysSinceLastSnowfall.toDouble();
    if(value == 99)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

void WeatherDataPoint::setDaysSinceLastSnowfall(double daysSinceLastSnowfall)
{
    m_daysSinceLastSnowfall = QString("%1").arg(daysSinceLastSnowfall);
}

bool WeatherDataPoint::setDaysSinceLastSnowfall(std::string daysSinceLastSnowfall)
{
    bool ok;
    QString().fromStdString(daysSinceLastSnowfall).toDouble(&ok);
    if(!ok)
    {
        m_daysSinceLastSnowfall = "99";
        return false;
    }
    m_daysSinceLastSnowfall = QString().fromStdString(daysSinceLastSnowfall);
    return true;
}

boost::optional<double> WeatherDataPoint::albedo() const
{
    double value = m_albedo.toDouble();
    if(value == 999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

void WeatherDataPoint::setAlbedo(double albedo)
{
    m_albedo = QString("%1").arg(albedo);
}

bool WeatherDataPoint::setAlbedo(std::string albedo)
{
    bool ok;
    QString().fromStdString(albedo).toDouble(&ok);
    if(!ok)
    {
        m_albedo = "999";
        return false;
    }
    m_albedo = QString().fromStdString(albedo);
    return true;
}

boost::optional<double> WeatherDataPoint::liquidPrecipitationDepth() const
{
    double value = m_liquidPrecipitationDepth.toDouble();
    if(value == 999)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

void WeatherDataPoint::setLiquidPrecipitationDepth(double liquidPrecipitationDepth)
{
    m_liquidPrecipitationDepth = QString("%1").arg(liquidPrecipitationDepth);
}

bool WeatherDataPoint::setLiquidPrecipitationDepth(std::string liquidPrecipitationDepth)
{
    bool ok;
    QString().fromStdString(liquidPrecipitationDepth).toDouble(&ok);
    if(!ok)
    {
        m_liquidPrecipitationDepth = "999";
        return false;
    }
    m_liquidPrecipitationDepth = QString().fromStdString(liquidPrecipitationDepth);
    return true;
}

boost::optional<double> WeatherDataPoint::liquidPrecipitationQuantity() const
{
    double value = m_liquidPrecipitationQuantity.toDouble();
    if(value == 99)
    {
        return boost::optional<double>();
    }
    return boost::optional<double>(value);
}

void WeatherDataPoint::setLiquidPrecipitationQuantity(double liquidPrecipitationQuantity)
{
    m_liquidPrecipitationQuantity = QString("%1").arg(liquidPrecipitationQuantity);
}

bool WeatherDataPoint::setLiquidPrecipitationQuantity(std::string liquidPrecipitationQuantity)
{
    bool ok;
    QString().fromStdString(liquidPrecipitationQuantity).toDouble(&ok);
    if(!ok)
    {
        m_liquidPrecipitationQuantity = "99";
        return false;
    }
    m_liquidPrecipitationQuantity = QString().fromStdString(liquidPrecipitationQuantity);
    return true;
}

std::string WeatherDataPoint::fieldUnits(WeatherDataFieldId id)
{
    std::string string;
    switch(id)
    {
    case WeatherDataPoint::DryBulbTemperature:
        string = "C";
        break;
    case WeatherDataPoint::DewPointTemperature:
        string = "C";
        break;
    case WeatherDataPoint::RelativeHumidity:
        string = "None";
        break;
    case WeatherDataPoint::AtmosphericStationPressure:
        string = "Pa";
        break;
    case WeatherDataPoint::ExtraterrestrialHorizontalRadiation:
        string = "Wh/m2";
        break;
    case WeatherDataPoint::ExtraterrestrialDirectNormalRadiation:
        string = "Wh/m2";
        break;
    case WeatherDataPoint::HorizontalInfraredRadiationIntensity:
        string = "Wh/m2";
        break;
    case WeatherDataPoint::GlobalHorizontalRadiation:
        string = "Wh/m2";
        break;
    case WeatherDataPoint::DirectNormalRadiation:
        string = "Wh/m2";
        break;
    case WeatherDataPoint::DiffuseHorizontalRadiation:
        string = "Wh/m2";
        break;
    case WeatherDataPoint::GlobalHorizontalIlluminance:
        string = "lux";
        break;
    case WeatherDataPoint::DirectNormalIlluminance:
        string = "lux";
        break;
    case WeatherDataPoint::DiffuseHorizontalIlluminance:
        string = "lux";
        break;
    case WeatherDataPoint::ZenithLuminance:
        string = "Cd/m2";
        break;
    case WeatherDataPoint::WindDirection:
        string = "degrees";
        break;
    case WeatherDataPoint::WindSpeed:
        string = "m/s";
        break;
    case WeatherDataPoint::TotalSkyCover:
        string = "None";
        break;
    case WeatherDataPoint::OpaqueSkyCover:
        string = "None";
        break;
    case WeatherDataPoint::Visibility:
        string = "km";
        break;
    case WeatherDataPoint::CeilingHeight:
        string = "m";
        break;
    case WeatherDataPoint::PresentWeatherObservation:
        string = "None";
        break;
    case WeatherDataPoint::PresentWeatherCodes:
        string = "None";
        break;
    case WeatherDataPoint::PrecipitableWater:
        string = "mm";
        break;
    case WeatherDataPoint::AerosolOpticalDepth:
        string = "thousandths";
        break;
    case WeatherDataPoint::SnowDepth:
        string = "cm";
        break;
    case WeatherDataPoint::DaysSinceLastSnowfall:
        string = "None";
        break;
    case WeatherDataPoint::Albedo:
        string = "None";
        break;
    case WeatherDataPoint::LiquidPrecipitationDepth:
        string = "mm";
        break;
    case WeatherDataPoint::LiquidPrecipitationQuantity:
        string = "hr";
        break;
    default:
        break;
    }
    return string;
}
