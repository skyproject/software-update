/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QDesktopServices>
#include <QMessageBox>
#include <QProcess>

#include "Windows/downloadwindow.h"
#include "Core/updatedownloader.h"
#include "ui_downloadwindow.h"

using namespace SUL;

DownloadWindow::DownloadWindow ( Structs::Application app,
                                 QWidget *parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::DownloadWindow )
{
    ui->setupUi ( this );
    this->application = app;
    this->downloader = new UpdateDownloader ( app.updateFilesXmlUrl );
    connect ( this->downloader, SIGNAL ( updateDownloaded() ),
              this, SLOT ( downloadingFinished() ) );
    connect ( this->downloader, SIGNAL ( downloadFailed() ),
              this, SLOT ( downloadingFailed() ) );
}

DownloadWindow::~DownloadWindow()
{
    delete ui;
}

void DownloadWindow::downloadingFailed()
{
    QMessageBox::critical ( this, "Error", "Update was not installed" );
    QApplication::exit ( 0 );
}

void DownloadWindow::downloadingFinished()
{
    FileDownloader *downloader = new FileDownloader();
    connect ( downloader, SIGNAL ( downloadCompleted ( QByteArray ) ),
              this, SLOT ( updateTasksDownloaded() ) );
    connect ( downloader, SIGNAL ( downloadFailed() ),
              this, SLOT ( downloadingFailed() ) );
    downloader->startDownload ( this->application.updateTasksXmlUrl,
                                ( QApplication::applicationDirPath()
                                  + "/software-update-tasks.xml" ) );
}

void DownloadWindow::updateTasksDownloaded()
{
    QDesktopServices::openUrl ( QUrl::fromLocalFile ( "apply-update.exe" ) );
    QCoreApplication::exit ( 0 );
}
