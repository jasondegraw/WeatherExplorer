#ifndef LOGGINGDIALOG_H
#define LOGGINGDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class LoggingDialog;
}

class LoggingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoggingDialog(QWidget *parent = 0);
    ~LoggingDialog();

    void store(std::string message);

private:
    Ui::LoggingDialog *ui;
};

#endif // LOGGINGDIALOG_H
