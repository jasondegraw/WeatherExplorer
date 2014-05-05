#include "weatherdataperiod.h"

WeatherDataPeriod::WeatherDataPeriod(int dayOfWeek, int startDay, int startMonth, int endDay, int endMonth)
    :  m_dayOfWeek(dayOfWeek), m_startDay(startDay), m_startMonth(startMonth), m_endDay(endDay), m_endMonth(endMonth)
{
}
