/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Windows/updatewindow.h"
#include "Core/updatechecker.h"
#include "softwareupdate.h"

using namespace SUL;

SoftwareUpdate::SoftwareUpdate(Structs::Application app)
{
    this->application = app;
    UpdateChecker *updChecker = new UpdateChecker(app);
    connect(updChecker, SIGNAL(updateAvailable(Structs::UpdateInformation)),
                     this, SLOT(updateAvailable(Structs::UpdateInformation)));
    connect(updChecker, SIGNAL(updateIsNotAvailable()),
                     this, SLOT(updateCheckFinished()));
    updChecker->checkForUpdates();
}

void SoftwareUpdate::updateAvailable(Structs::UpdateInformation info)
{
    UpdateWindow *uw = new UpdateWindow(this->application, info);
    uw->show();
    connect(uw, SIGNAL(updateSkipped()),
            this, SLOT(updateCheckFinished()));
    UpdateChecker *uc = qobject_cast<UpdateChecker*>(sender());
    delete uc;
}

void SoftwareUpdate::updateCheckFinished()
{
    emit finished();
}
