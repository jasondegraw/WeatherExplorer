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

WeatherExploder::WeatherExploder(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
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
    actionExport = new QAction(this);
    actionExport->setObjectName(QStringLiteral("actionSave"));
    QIcon icon3;
    icon3.addFile(QStringLiteral(":/images/export.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionExport->setIcon(icon3);
    actionExit = new QAction(this);
    actionExit->setObjectName(QStringLiteral("actionExit"));
    actionContents = new QAction(this);
    actionContents->setObjectName(QStringLiteral("actionContents"));
    actionAbout = new QAction(this);
    actionAbout->setObjectName(QStringLiteral("actionAbout"));
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
    menuBar->addAction(menuHelp->menuAction());
    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionExport);
    menuFile->addAction(actionExit);
    menuHelp->addAction(actionContents);
    menuHelp->addAction(actionAbout);
    mainToolBar->addAction(actionNew);
    mainToolBar->addAction(actionOpen);
    mainToolBar->addAction(actionSave);
    mainToolBar->addAction(actionExport);

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
    actionExport->setText(QApplication::translate("WeatherExploder", "Export...", 0));
    actionExit->setText(QApplication::translate("WeatherExploder", "E&xit", 0));
    actionExit->setShortcut(QApplication::translate("WeatherExploder", "Ctrl+Q", 0));
    actionContents->setText(QApplication::translate("WeatherExploder", "Contents", 0));
    actionAbout->setText(QApplication::translate("WeatherExploder", "About...", 0));
    menuFile->setTitle(QApplication::translate("WeatherExploder", "&File", 0));
    menuEdit->setTitle(QApplication::translate("WeatherExploder", "&Edit", 0));
    menuHelp->setTitle(QApplication::translate("WeatherExploder", "&Help", 0));
}

void WeatherExploder::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Weather File"),
                                                    "", tr("Weather Files (*.epw)"));
    if(!fileName.isNull())
    {
        tableView->reset();
        m_model.loadEpw(fileName);
        //ui->tableView->reset();
        //ui->tableView->update();
        //ui->tableView->repaint();
        //ui->tableView->setModel(&m_model);
    }
}

void WeatherExploder::on_actionNew_triggered()
{
}
