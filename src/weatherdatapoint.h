/**********************************************************************
 *  Copyright (c) 2013, The Pennsylvania State University.
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

#include <iostream>
#define ERROR(a) std::cout<<a<<std::endl;exit(EXIT_FAILURE)

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

    WeatherDataPoint();
    WeatherDataPoint(std::string line);
    WeatherDataPoint(int year,int month,int day,int hour,int minute,
                     std::string dataSourceandUncertaintyFlags,double dryBulbTemperature,
                     double dewPointTemperature,double relativeHumidity,double atmosphericStationPressure,
                     double extraterrestrialHorizontalRadiation,double extraterrestrialDirectNormalRadiation,
                     double horizontalInfraredRadiationIntensity,double globalHorizontalRadiation,
                     double directNormalRadiation,double diffuseHorizontalRadiation,
                     double globalHorizontalIlluminance,double directNormalIlluminance,
                     double diffuseHorizontalIlluminance,double zenithLuminance,double windDirection,
                     double windSpeed,int totalSkyCover,int opaqueSkyCover,double visibility,
                     double ceilingHeight,int presentWeatherObservation,int presentWeatherCodes,
                     double precipitableWater,double aerosolOpticalDepth,double snowDepth,
                     double daysSinceLastSnowfall,double albedo,double liquidPrecipitationDepth,
                     double liquidPrecipitationQuantity);
    // Conversion
    std::string toWthString();
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
    int totalSkyCover() const;
    bool setTotalSkyCover(int totalSkyCover);
    bool setTotalSkyCover(std::string totalSkyCover);
    int opaqueSkyCover() const;
    bool setOpaqueSkyCover(int opaqueSkyCover);
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

    std::string fieldUnits(WeatherDataFieldId id);

private:
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    std::string m_dataSourceandUncertaintyFlags;
    QString m_dryBulbTemperature;
    QString m_dewPointTemperature;
    QString m_relativeHumidity;
    QString m_atmosphericStationPressure;
    QString m_extraterrestrialHorizontalRadiation;
    QString m_extraterrestrialDirectNormalRadiation;
    QString m_horizontalInfraredRadiationIntensity;
    QString m_globalHorizontalRadiation;
    QString m_directNormalRadiation;
    QString m_diffuseHorizontalRadiation;
    QString m_globalHorizontalIlluminance;
    QString m_directNormalIlluminance;
    QString m_diffuseHorizontalIlluminance;
    QString m_zenithLuminance;
    QString m_windDirection;
    QString m_windSpeed;
    int m_totalSkyCover;
    int m_opaqueSkyCover;
    QString m_visibility;
    QString m_ceilingHeight;
    int m_presentWeatherObservation;
    int m_presentWeatherCodes;
    QString m_precipitableWater;
    QString m_aerosolOpticalDepth;
    QString m_snowDepth;
    QString m_daysSinceLastSnowfall;
    QString m_albedo;
    QString m_liquidPrecipitationDepth;
    QString m_liquidPrecipitationQuantity;
};

#endif // WEATHERDATAPOINT_H