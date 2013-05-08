/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Windows/downloadwindow.h"
#include "Windows/updatewindow.h"
#include "ui_updatewindow.h"

using namespace SUL;

UpdateWindow::UpdateWindow ( Structs::Application app,
                             Structs::UpdateInformation info,
                             QWidget *parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::UpdateWindow )
{
    ui->setupUi ( this );
    this->application = app;
    ui->labelApplicationName->setText ( info.applicationName );
    ui->labelUpdate->setText ( "A new version (" + info.currentVersion
                               + ") of " + info.applicationName
                               + " is available. Do you want to install it?" );
    ui->textReleaseNotes->setHtml ( info.releaseNotes );
    if ( info.isUpdateRequired == true )
    {
        ui->buttonSkip->setEnabled ( false );
        ui->buttonSkip->setToolTip ( "This update is required. You cannot skip it." );
    }
    connect ( ui->buttonInstall, SIGNAL ( clicked() ),
              this, SLOT ( download() ) );
    connect ( ui->buttonSkip, SIGNAL ( clicked() ),
              this, SLOT ( skip() ) );
}

UpdateWindow::~UpdateWindow()
{
    delete ui;
}

void UpdateWindow::download()
{
    DownloadWindow *dw = new DownloadWindow ( this->application );
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
