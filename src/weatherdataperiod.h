#ifndef WEATHERDATAPERIOD_H
#define WEATHERDATAPERIOD_H

class WeatherDataPeriod
{
public:
    WeatherDataPeriod(int dayOfWeek=1, int startDay=1, int startMonth=1, int endDay=1, int endMonth=1);
private:
    int m_dayOfWeek;
    int m_startDay;
    int m_startMonth;
    int m_endDay;
    int m_endMonth;
};

#endif // WEATHERDATAPERIOD_H
