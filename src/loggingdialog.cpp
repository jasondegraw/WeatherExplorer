#include "loggingdialog.h"
#include "ui_loggingdialog.h"

LoggingDialog::LoggingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoggingDialog)
{
    ui->setupUi(this);
}

LoggingDialog::~LoggingDialog()
{
    delete ui;
}

void LoggingDialog::store(std::string message)
{
    ui->textEdit->append(QString::fromStdString(message));
}
