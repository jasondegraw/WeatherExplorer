#include "weatherdataperiod.h"

WeatherDataPeriod::WeatherDataPeriod(std::string name, int dayOfWeek, int startMonth, int startDay, int endMonth, int endDay)
{
    m_name = name;
    setDayOfWeek(dayOfWeek);
    setStartDay(startDay);
    setStartMonth(startMonth);
    setEndDay(endDay);
    setEndMonth(endMonth);
}

void WeatherDataPeriod::setName(std::string name)
{
    m_name=name;
}

std::string WeatherDataPeriod::name() const
{
    return m_name;
}

bool WeatherDataPeriod::setDayOfWeek(int dayOfWeek)
{
    if(dayOfWeek<1 || dayOfWeek>7) {
        return false;
    }
    m_dayOfWeek = dayOfWeek;
    return true;
}

bool WeatherDataPeriod::setDayOfWeek(QString string)
{
    bool ok;
    int dayOfWeek = string.toInt(&ok);
    if(!ok) {
        return false;
    } else if(dayOfWeek<1 || dayOfWeek>7) {
        return false;
    }
    m_dayOfWeek = dayOfWeek;
    return true;
}

int WeatherDataPeriod::dayOfWeek() const
{
    return m_dayOfWeek;
}

bool WeatherDataPeriod::setStartDay(int startDay)
{
    if(startDay<1 || startDay>31) {
        return false;
    }
    m_startDay = startDay;
    return true;
}

bool WeatherDataPeriod::setStartDay(QString string)
{
    bool ok;
    int startDay = string.toInt(&ok);
    if(!ok) {
        return false;
    } else if(startDay<1 || startDay>31) {
        return false;
    }
    m_startDay = startDay;
    return true;
}

int WeatherDataPeriod::startDay() const
{
    return m_startDay;
}

bool WeatherDataPeriod::setStartMonth(int startMonth)
{
    if(startMonth<1 || startMonth>12) {
        return false;
    }
    m_startMonth = startMonth;
    return true;
}

bool WeatherDataPeriod::setStartMonth(QString string)
{
    bool ok;
    int startMonth = string.toInt(&ok);
    if(!ok) {
        return false;
    } else if(startMonth<1 || startMonth>12) {
        return false;
    }
    m_startMonth = startMonth;
    return true;
}

int WeatherDataPeriod::startMonth() const
{
    return m_startMonth;
}

bool WeatherDataPeriod::setEndDay(int endDay)
{
    if(endDay<1 || endDay>31) {
        return false;
    }
    m_endDay = endDay;
    return true;
}

bool WeatherDataPeriod::setEndDay(QString string)
{
    bool ok;
    int endDay = string.toInt(&ok);
    if(!ok) {
        return false;
    } else if(endDay<1 || endDay>31) {
        return false;
    }
    m_endDay = endDay;
    return true;
}

int WeatherDataPeriod::endDay() const
{
    return m_endDay;
}

bool WeatherDataPeriod::setEndMonth(int endMonth)
{
    if(endMonth<1 || endMonth>12) {
        return false;
    }
    m_endMonth = endMonth;
    return true;
}

bool WeatherDataPeriod::setEndMonth(QString string)
{
    bool ok;
    int endMonth = string.toInt(&ok);
    if(!ok) {
        return false;
    } else if(endMonth<1 || endMonth>12) {
        return false;
    }
    m_endMonth = endMonth;
    return true;
}

int WeatherDataPeriod::endMonth() const
{
    return m_endMonth;
}
