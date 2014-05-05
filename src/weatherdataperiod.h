#ifndef WEATHERDATAPERIOD_H
#define WEATHERDATAPERIOD_H

#include <QString>

class WeatherDataPeriod
{
public:
    WeatherDataPeriod(int dayOfWeek=1, int startDay=1, int startMonth=1, int endDay=1, int endMonth=1);
    void setName(QString name);
    QString name() const;
    bool setDayOfWeek(int dayOfWeek);
    bool setDayOfWeek(QString string);
    int dayOfWeek() const;
    bool setStartDay(int startDay);
    bool setStartDay(QString string);
    int startDay() const;
    bool setStartMonth(int startMonth);
    bool setStartMonth(QString string);
    int startMonth() const;
    bool setEndDay(int endDay);
    bool setEndDay(QString string);
    int endDay() const;
    bool setEndMonth(int endMonth);
    bool setEndMonth(QString string);
    int endMonth() const;
private:
    QString m_name;
    int m_dayOfWeek;
    int m_startDay;
    int m_startMonth;
    int m_endDay;
    int m_endMonth;
};

#endif // WEATHERDATAPERIOD_H
