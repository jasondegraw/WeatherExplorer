/**********************************************************************
 *  Copyright (c) 2013, Jason W. DeGraw.
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
#include "weatherexplorer.h"

#include <QFileDialog>
#include <QMessageBox>
#include "locationdialog.h"
#include "logging.h"

WeatherExploder::WeatherExploder(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    // Turn on logging
    logging::initialize(m_log);
    // Set up the model
    tableView->setModel(&m_model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //tableView->horizontalHeader()->resizeSection(0, 200);
    //tableView->horizontalHeader()->setMinimumSectionSize(150);
}

WeatherExploder::~WeatherExploder()
{
}

void WeatherExploder::setupUi()
{
    if (objectName().isEmpty())
    {
        setObjectName(QStringLiteral("WeatherExploder"));
    }
    resize(400, 300);
    actionNew = new QAction(this);
    actionNew->setObjectName(QStringLiteral("actionNew"));
    QIcon icon;
    icon.addFile(QStringLiteral(":/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionNew->setIcon(icon);
    actionOpen = new QAction(this);
    actionOpen->setObjectName(QStringLiteral("actionOpen"));
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionOpen->setIcon(icon1);
    actionSave = new QAction(this);
    actionSave->setObjectName(QStringLiteral("actionSave"));
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionSave->setIcon(icon2);
    actionImport = new QAction(this);
    actionImport->setObjectName(QStringLiteral("actionImport"));
    //QIcon icon3;
    //icon3.addFile(QStringLiteral(":/images/export.png"), QSize(), QIcon::Normal, QIcon::Off);
    //actionExport->setIcon(icon3);
    actionExport = new QAction(this);
    actionExport->setObjectName(QStringLiteral("actionExport"));
    QIcon icon3;
    icon3.addFile(QStringLiteral(":/images/export.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionExport->setIcon(icon3);
    actionExit = new QAction(this);
    actionExit->setObjectName(QStringLiteral("actionExit"));
    actionContents = new QAction(this);
    actionContents->setObjectName(QStringLiteral("actionContents"));
    actionAbout = new QAction(this);
    actionAbout->setObjectName(QStringLiteral("actionAbout"));
    actionShowLog = new QAction(this);
    actionShowLog->setObjectName(QStringLiteral("actionShowLog"));
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    tableView = new QTableView(centralWidget);
    tableView->setObjectName(QStringLiteral("tableView"));

    gridLayout->addWidget(tableView, 0, 0, 1, 1);

    setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 400, 21));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QStringLiteral("menuFile"));
    menuEdit = new QMenu(menuBar);
    menuEdit->setObjectName(QStringLiteral("menuEdit"));
    menuWindow = new QMenu(menuBar);
    menuWindow->setObjectName(QStringLiteral("menuWindow"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QStringLiteral("menuHelp"));
    setMenuBar(menuBar);
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    setStatusBar(statusBar);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    menuBar->addAction(menuWindow->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionExport);
    menuFile->addAction(actionImport);
    menuFile->addAction(actionExit);
    menuWindow->addAction(actionShowLog);
    menuHelp->addAction(actionContents);
    menuHelp->addAction(actionAbout);
    mainToolBar->addAction(actionNew);
    mainToolBar->addAction(actionOpen);
    mainToolBar->addAction(actionSave);
    mainToolBar->addAction(actionExport);

    m_log = new LoggingDialog(this);

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void WeatherExploder::retranslateUi()
{
    setWindowTitle(QApplication::translate("WeatherExploder", "WeatherExplorer", 0));
    actionNew->setText(QApplication::translate("WeatherExploder", "&New", 0));
    actionNew->setShortcut(QApplication::translate("WeatherExploder", "Ctrl+N", 0));
    actionOpen->setText(QApplication::translate("WeatherExploder", "&Open...", 0));
    actionOpen->setShortcut(QApplication::translate("WeatherExploder", "Ctrl+O", 0));
    actionSave->setText(QApplication::translate("WeatherExploder", "&Save", 0));
    actionSave->setShortcut(QApplication::translate("WeatherExploder", "Ctrl+S", 0));
    actionImport->setText(QApplication::translate("WeatherExploder", "Import...", 0));
    actionExport->setText(QApplication::translate("WeatherExploder", "Export...", 0));
    actionExit->setText(QApplication::translate("WeatherExploder", "E&xit", 0));
    actionExit->setShortcut(QApplication::translate("WeatherExploder", "Ctrl+Q", 0));
    actionContents->setText(QApplication::translate("WeatherExploder", "Contents", 0));
    actionAbout->setText(QApplication::translate("WeatherExploder", "About...", 0));
    actionShowLog->setText(QApplication::translate("WeatherExploder", "Show Log...", 0));
    menuFile->setTitle(QApplication::translate("WeatherExploder", "&File", 0));
    menuEdit->setTitle(QApplication::translate("WeatherExploder", "&Edit", 0));
    menuWindow->setTitle(QApplication::translate("WeatherExploder", "&Window", 0));
    menuHelp->setTitle(QApplication::translate("WeatherExploder", "&Help", 0));
}

void WeatherExploder::on_actionNew_triggered()
{
    m_model.clear();
}

void WeatherExploder::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Weather File"),
                                                    "", tr("Weather Files (*.epw)"));
    if(!fileName.isNull())
    {
        tableView->reset();
        if(!m_model.loadEpw(fileName)) {
            m_model.clear();
            QMessageBox::critical(this, QApplication::translate("WeatherExploder", "File Read Failed"),
                                  QApplication::translate("WeatherExploder", "The selected file could not be read.\n"
                                                          "Check the log for details"),QMessageBox::Ok);
        }
        //ui->tableView->reset();
        //ui->tableView->update();
        //ui->tableView->repaint();
        //ui->tableView->setModel(&m_model);
    }
}

void WeatherExploder::on_actionSave_triggered()
{
    /*
    LocationDialog dialog(QString().fromStdString(m_model.city()),
                          QString().fromStdString(m_model.stateProvinceRegion()),
                          QString().fromStdString(m_model.country()),
                          QString().fromStdString(m_model.source()),
                          QString().fromStdString(m_model.WMO()),
                          QString().fromStdString(m_model.latitudeString()),
                          QString().fromStdString(m_model.longitudeString()),
                          QString().fromStdString(m_model.timeZoneString()),
                          QString().fromStdString(m_model.elevationString()),this);
    if(dialog.exec() == QDialog::Accepted)
    {

    }*/
    //LOG(info) << "Well, I hope this works";
    //LOG(info) << "Hello?";
}


void WeatherExploder::on_actionImport_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import File"),
                                                    "", tr("ASHRAE IWEC (*.iwc);;CONTAM WTH (*.wth);;Radiance WEA (*.wea)"));
    std::cout << fileName.toStdString() << std::endl;
}

void WeatherExploder::on_actionExport_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                    "", tr("CONTAM WTH (*.wth);;Radiance WEA (*.wea)"));
    std::cout << fileName.toStdString() << std::endl;
}

void WeatherExploder::on_actionShowLog_triggered()
{
    m_log->show();
}
