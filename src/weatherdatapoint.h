/**********************************************************************
 *  Copyright (c) 2014, Jason W. DeGraw
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
#ifndef WEATHERDATAPOINT_H
#define WEATHERDATAPOINT_H

#include <QString>
#include <string>

#include <boost/optional.hpp>
#include "../qdecnumber/qdecnumber.h"

#include <iostream>

class WeatherDataPoint
{
public:
    enum WeatherDataFieldId {DryBulbTemperature=6,DewPointTemperature,RelativeHumidity,
                             AtmosphericStationPressure,ExtraterrestrialHorizontalRadiation,
                             ExtraterrestrialDirectNormalRadiation,HorizontalInfraredRadiationIntensity,
                             GlobalHorizontalRadiation,DirectNormalRadiation,DiffuseHorizontalRadiation,
                             GlobalHorizontalIlluminance,DirectNormalIlluminance,DiffuseHorizontalIlluminance,
                             ZenithLuminance,WindDirection,WindSpeed,TotalSkyCover,OpaqueSkyCover,Visibility,
                             CeilingHeight,PresentWeatherObservation,PresentWeatherCodes,PrecipitableWater,
                             AerosolOpticalDepth,SnowDepth,DaysSinceLastSnowfall,Albedo,
                             LiquidPrecipitationDepth,LiquidPrecipitationQuantity};

    WeatherDataPoint(int year=1,int month=1,int day=1,int hour=0,int minute=0,
                     std::string dataSourceandUncertaintyFlags="",double dryBulbTemperature=99.9,
                     double dewPointTemperature=99.9, double relativeHumidity=999,double atmosphericStationPressure=999999,
                     double extraterrestrialHorizontalRadiation=9999,double extraterrestrialDirectNormalRadiation=9999,
                     double horizontalInfraredRadiationIntensity=9999,double globalHorizontalRadiation=9999,
                     double directNormalRadiation=9999,double diffuseHorizontalRadiation=9999,
                     double globalHorizontalIlluminance=999999,double directNormalIlluminance=999999,
                     double diffuseHorizontalIlluminance=999999,double zenithLuminance=9999,double windDirection=999,
                     double windSpeed=999,int totalSkyCover=99,int opaqueSkyCover=99,double visibility=9999,
                     double ceilingHeight=99999,int presentWeatherObservation=0,int presentWeatherCodes=0,
                     double precipitableWater=999,double aerosolOpticalDepth=.999,double snowDepth=999,
                     double daysSinceLastSnowfall=99,double albedo=999,double liquidPrecipitationDepth=999,
                     double liquidPrecipitationQuantity=99);
    // Conversion
    static boost::optional<WeatherDataPoint> fromEpwString(std::string line, bool readMinutes=false);
    boost::optional<std::string> toWthString();
    // One billion getters and setters
    int year() const;
    void setYear(int year);
    bool setYear(std::string year);
    int month() const;
    bool setMonth(int month);
    bool setMonth(std::string month);
    int day() const;
    bool setDay(int day);
    bool setDay(std::string day);
    int hour() const;
    bool setHour(int hour);
    bool setHour(std::string hour);
    int minute() const;
    bool setMinute(int minute);
    bool setMinute(std::string minute);
    std::string dataSourceandUncertaintyFlags() const;
    void setDataSourceandUncertaintyFlags(std::string dataSourceandUncertaintyFlags);
    boost::optional<double> dryBulbTemperature() const;
    bool setDryBulbTemperature(double dryBulbTemperature);
    bool setDryBulbTemperature(std::string dryBulbTemperature);
    boost::optional<double> dewPointTemperature() const;
    bool setDewPointTemperature(double dewPointTemperature);
    bool setDewPointTemperature(std::string dewPointTemperature);
    boost::optional<double> relativeHumidity() const;
    bool setRelativeHumidity(double relativeHumidity);
    bool setRelativeHumidity(std::string relativeHumidity);
    boost::optional<double> atmosphericStationPressure() const;
    bool setAtmosphericStationPressure(double atmosphericStationPressure);
    bool setAtmosphericStationPressure(std::string atmosphericStationPressure);
    boost::optional<double> extraterrestrialHorizontalRadiation() const;
    bool setExtraterrestrialHorizontalRadiation(double extraterrestrialHorizontalRadiation);
    bool setExtraterrestrialHorizontalRadiation(std::string extraterrestrialHorizontalRadiation);
    boost::optional<double> extraterrestrialDirectNormalRadiation() const;
    bool setExtraterrestrialDirectNormalRadiation(double extraterrestrialDirectNormalRadiation);
    bool setExtraterrestrialDirectNormalRadiation(std::string extraterrestrialDirectNormalRadiation);
    boost::optional<double> horizontalInfraredRadiationIntensity() const;
    bool setHorizontalInfraredRadiationIntensity(double horizontalInfraredRadiationIntensity);
    bool setHorizontalInfraredRadiationIntensity(std::string horizontalInfraredRadiationIntensity);
    boost::optional<double> globalHorizontalRadiation() const;
    bool setGlobalHorizontalRadiation(double globalHorizontalRadiation);
    bool setGlobalHorizontalRadiation(std::string globalHorizontalRadiation);
    boost::optional<double> directNormalRadiation() const;
    bool setDirectNormalRadiation(double directNormalRadiation);
    bool setDirectNormalRadiation(std::string directNormalRadiation);
    boost::optional<double> diffuseHorizontalRadiation() const;
    bool setDiffuseHorizontalRadiation(double diffuseHorizontalRadiation);
    bool setDiffuseHorizontalRadiation(std::string diffuseHorizontalRadiation);
    boost::optional<double> globalHorizontalIlluminance() const;
    bool setGlobalHorizontalIlluminance(double globalHorizontalIlluminance);
    bool setGlobalHorizontalIlluminance(std::string globalHorizontalIlluminance);
    boost::optional<double> directNormalIlluminance() const;
    bool setDirectNormalIlluminance(double directNormalIlluminance);
    bool setDirectNormalIlluminance(std::string directNormalIlluminance);
    boost::optional<double> diffuseHorizontalIlluminance() const;
    bool setDiffuseHorizontalIlluminance(double diffuseHorizontalIlluminance);
    bool setDiffuseHorizontalIlluminance(std::string diffuseHorizontalIlluminance);
    boost::optional<double> zenithLuminance() const;
    bool setZenithLuminance(double zenithLuminance);
    bool setZenithLuminance(std::string zenithLuminance);
    boost::optional<double> windDirection() const;
    bool setWindDirection(double windDirection);
    bool setWindDirection(std::string windDirection);
    boost::optional<double> windSpeed() const;
    bool setWindSpeed(double windSpeed);
    bool setWindSpeed(std::string windSpeed);
    boost::optional<double> totalSkyCover() const;
    bool setTotalSkyCover(double totalSkyCover);
    bool setTotalSkyCover(std::string totalSkyCover);
    boost::optional<double> opaqueSkyCover() const;
    bool setOpaqueSkyCover(double opaqueSkyCover);
    bool setOpaqueSkyCover(std::string opaqueSkyCover);
    boost::optional<double> visibility() const;
    void setVisibility(double visibility);
    bool setVisibility(std::string visibility);
    boost::optional<double> ceilingHeight() const;
    void setCeilingHeight(double ceilingHeight);
    bool setCeilingHeight(std::string ceilingHeight);
    int presentWeatherObservation() const;
    void setPresentWeatherObservation(int presentWeatherObservation);
    bool setPresentWeatherObservation(std::string presentWeatherObservation);
    int presentWeatherCodes() const;
    void setPresentWeatherCodes(int presentWeatherCodes);
    bool setPresentWeatherCodes(std::string presentWeatherCodes);
    boost::optional<double> precipitableWater() const;
    void setPrecipitableWater(double precipitableWater);
    bool setPrecipitableWater(std::string precipitableWater);
    boost::optional<double> aerosolOpticalDepth() const;
    void setAerosolOpticalDepth(double aerosolOpticalDepth);
    bool setAerosolOpticalDepth(std::string aerosolOpticalDepth);
    boost::optional<double> snowDepth() const;
    void setSnowDepth(double snowDepth);
    bool setSnowDepth(std::string snowDepth);
    boost::optional<double> daysSinceLastSnowfall() const;
    void setDaysSinceLastSnowfall(double daysSinceLastSnowfall);
    bool setDaysSinceLastSnowfall(std::string daysSinceLastSnowfall);
    boost::optional<double> albedo() const;
    void setAlbedo(double albedo);
    bool setAlbedo(std::string albedo);
    boost::optional<double> liquidPrecipitationDepth() const;
    void setLiquidPrecipitationDepth(double liquidPrecipitationDepth);
    bool setLiquidPrecipitationDepth(std::string liquidPrecipitationDepth);
    boost::optional<double> liquidPrecipitationQuantity() const;
    void setLiquidPrecipitationQuantity(double liquidPrecipitationQuantity);
    bool setLiquidPrecipitationQuantity(std::string liquidPrecipitationQuantity);

    std::string getUnits(WeatherDataFieldId id);
    // Need to think about the string getter more
    //boost::optional<std::string> getString(WeatherDataFieldId id);
    boost::optional<double> getDouble(WeatherDataFieldId id);
    boost::optional<int> getInt(WeatherDataFieldId id);

private:
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    std::string m_dataSourceandUncertaintyFlags;
    QDecNumber m_dryBulbTemperature;
    QDecNumber m_dewPointTemperature;
    QDecNumber m_relativeHumidity;
    QDecNumber m_atmosphericStationPressure;
    QDecNumber m_extraterrestrialHorizontalRadiation;
    QDecNumber m_extraterrestrialDirectNormalRadiation;
    QDecNumber m_horizontalInfraredRadiationIntensity;
    QDecNumber m_globalHorizontalRadiation;
    QDecNumber m_directNormalRadiation;
    QDecNumber m_diffuseHorizontalRadiation;
    QDecNumber m_globalHorizontalIlluminance;
    QDecNumber m_directNormalIlluminance;
    QDecNumber m_diffuseHorizontalIlluminance;
    QDecNumber m_zenithLuminance;
    QDecNumber m_windDirection;
    QDecNumber m_windSpeed;
    QDecNumber m_totalSkyCover;
    QDecNumber m_opaqueSkyCover;
    QDecNumber m_visibility;
    QDecNumber m_ceilingHeight;
    int m_presentWeatherObservation;
    int m_presentWeatherCodes;
    QDecNumber m_precipitableWater;
    QDecNumber m_aerosolOpticalDepth;
    QDecNumber m_snowDepth;
    QDecNumber m_daysSinceLastSnowfall;
    QDecNumber m_albedo;
    QDecNumber m_liquidPrecipitationDepth;
    QDecNumber m_liquidPrecipitationQuantity;
};

#endif // WEATHERDATAPOINT_H
