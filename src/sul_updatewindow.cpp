/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "ui_sul_updatewindow.h"
#include "sul_downloadwindow.h"
#include "sul_updatewindow.h"

using namespace SUL;

UpdateWindow::UpdateWindow(Structs::UpdateInformation info,
                           QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateWindow)
{
    ui->setupUi(this);
    this->updatePackageUrl = info.updatePackageUrl;
    ui->labelApplicationName->setText(info.applicationName);
    ui->labelUpdate->setText("A new version (" + info.availableVersion
                             + ") of " + info.applicationName
                             + " is available. Do you want to install it?");
    ui->textReleaseNotes->setHtml(info.releaseNotes);
    if (info.isUpdateRequired == true)
    {
        ui->buttonSkip->setEnabled(false);
        ui->buttonSkip->setToolTip("This update is required. You cannot skip it.");
        this->setWindowFlags(((this->windowFlags() | Qt::CustomizeWindowHint)
                              & ~Qt::WindowCloseButtonHint));
    }
    connect(ui->buttonInstall, SIGNAL(clicked()),
            this, SLOT(download()));
    connect(ui->buttonSkip, SIGNAL(clicked()),
            this, SLOT(skip()));
}

UpdateWindow::~UpdateWindow()
{
    delete ui;
}

void UpdateWindow::download()
{
    DownloadWindow *dw = new DownloadWindow(this->updatePackageUrl);
    dw->show();
    this->close();
    this->destroy();
}

void UpdateWindow::skip()
{
    this->close();
    this->destroy();
    emit updateSkipped();
}
