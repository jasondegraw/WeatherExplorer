#ifndef LOGGINGDIALOG_H
#define LOGGINGDIALOG_H

#include <QDialog>

namespace Ui {
class LoggingDialog;
}

class LoggingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoggingDialog(QWidget *parent = 0);
    ~LoggingDialog();

private:
    Ui::LoggingDialog *ui;
};

#endif // LOGGINGDIALOG_H
