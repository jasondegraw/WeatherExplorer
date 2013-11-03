#ifndef LOCATIONDIALOG_H
#define LOCATIONDIALOG_H

#include <QDialog>
#include <QDoubleValidator>
#include <QMap>

namespace Ui {
class LocationDialog;
}

class LocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocationDialog(QString city,QString stateProvinceRegion,QString country,QString source,
                            QString WMO,QString latitude,QString longitude,QString timeZone,QString elevation,
                            QWidget *parent = 0);
    ~LocationDialog();
    QMap<QString,QString> changes();

private:
    Ui::LocationDialog *ui;

    QString m_city;
    QString m_stateProvinceRegion;
    QString m_country;
    QString m_source;
    QString m_WMO;
    QString m_latitude;
    QString m_longitude;
    QString m_timeZone;
    QString m_elevation;
};

class DoubleLTValidator : public QDoubleValidator
{
public:
    DoubleLTValidator(QObject * parent = 0);
    DoubleLTValidator(double bottom, double top, int decimals, QObject * parent = 0);
    ~DoubleLTValidator()
    {}
    virtual QValidator::State validate(QString & input, int & pos) const;
};

#endif // LOCATIONDIALOG_H
