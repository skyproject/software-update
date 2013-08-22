/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QDesktopServices>
#include <QStandardPaths>
#include <QMessageBox>
#include <windows.h>

#include "ui_sul_downloadwindow.h"
#include "sul_filedownloader.h"
#include "sul_downloadwindow.h"

using namespace SUL;

DownloadWindow::DownloadWindow(QUrl updatePackage,
                               QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DownloadWindow)
{
    ui->setupUi(this);
    FileDownloader *downloader = new FileDownloader();
    connect(downloader, SIGNAL(downloadCompleted(QByteArray)),
            this, SLOT(downloadingFinished()));
    connect(downloader, SIGNAL(downloadFailed()),
            this, SLOT(downloadingFailed()));
    downloader->startDownload(updatePackage,
                              QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                              + "/software-update-package.exe");
}

DownloadWindow::~DownloadWindow()
{
    delete ui;
}

void DownloadWindow::downloadingFailed()
{
    QMessageBox::critical(this, "Error", "Update was not downloaded.");
    QApplication::exit(0);
}

void DownloadWindow::downloadingFinished()
{
    QString exec = QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                   + "/software-update-package.exe";
    ShellExecute(NULL, L"runas", reinterpret_cast<const WCHAR *>(exec.utf16()),
                 NULL, NULL, SW_SHOWNORMAL);
    QCoreApplication::exit(0);
}
