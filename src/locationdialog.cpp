#include "locationdialog.h"
#include "ui_locationdialog.h"

DoubleLTValidator::DoubleLTValidator(QObject * parent) : QDoubleValidator(parent)
{}

DoubleLTValidator::DoubleLTValidator(double bottom, double top, int decimals, QObject * parent)
    : QDoubleValidator(bottom, top, decimals, parent)
{}

QValidator::State DoubleLTValidator::validate(QString & input, int & pos) const
{
    QValidator::State state = QDoubleValidator::validate(input, pos);
    if(state == QValidator::Acceptable)
    {
        if(input.toDouble() >= top())
        {
            return QValidator::Intermediate;
        }
    }
    return state;
}

LocationDialog::LocationDialog(QString city, QString stateProvinceRegion, QString country, QString source,
                               QString WMO, QString latitude, QString longitude, QString timeZone,
                               QString elevation, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocationDialog)
{
    ui->setupUi(this);
    ui->lineElevation->setValidator(new DoubleLTValidator(-1000.0,9999.9,16,ui->lineElevation));

    m_city = city;
    m_stateProvinceRegion = stateProvinceRegion;
    m_country = country;
    m_source = source;
    m_WMO = WMO;
    m_latitude = latitude;
    m_longitude = longitude;
    m_timeZone = timeZone;
    m_elevation = elevation;

    ui->lineCity->setText(m_city);
    ui->lineRegion->setText(m_stateProvinceRegion);
    ui->lineCountry->setText(m_country);
    ui->lineSource->setText(m_source);
    ui->lineWMO->setText(m_WMO);
    ui->lineLatitude->setText(m_latitude);
    ui->lineLongitude->setText(m_longitude);
    ui->lineTimeZone->setText(m_timeZone);
    ui->lineElevation->setText(m_elevation);
}

QMap<QString,QString> LocationDialog::changes()
{
    QMap<QString,QString> map;
    if(ui->lineCity->text() != m_city)
    {
        map["city"] = ui->lineCity->text();
    }
    if(ui->lineRegion->text() != m_stateProvinceRegion)
    {
        map["stateProvinceRegion"] = ui->lineRegion->text();
    }
    if(ui->lineCountry->text() != m_country)
    {
        map["country"] = ui->lineCountry->text();
    }
    if(ui->lineSource->text() != m_source)
    {
        map["source"] = ui->lineSource->text();
    }
    if(ui->lineWMO->text() != m_WMO)
    {
        map["WMO"] = ui->lineWMO->text();
    }
    if(ui->lineLatitude->text() != m_latitude)
    {
        map["latitude"] = ui->lineLatitude->text();
    }
    if(ui->lineLongitude->text() != m_longitude)
    {
        map["longitude"] = ui->lineLongitude->text();
    }
    if(ui->lineTimeZone->text() != m_timeZone)
    {
        map["timeZone"] = ui->lineTimeZone->text();
    }
    if(ui->lineElevation->text() != m_elevation)
    {
        map["elevation"] = ui->lineElevation->text();
    }
    return map;
}

LocationDialog::~LocationDialog()
{
    delete ui;
}
