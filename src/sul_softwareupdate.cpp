/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "sul_softwareupdate.h"
#include "sul_updatechecker.h"
#include "sul_updatewindow.h"

using namespace SUL;

SoftwareUpdate::SoftwareUpdate(Structs::Application app)
{
    UpdateChecker *updChecker = new UpdateChecker(app);
    connect(updChecker, SIGNAL(updateAvailable(Structs::UpdateInformation)),
            this, SLOT(updateAvailable(Structs::UpdateInformation)));
    connect(updChecker, SIGNAL(updateIsNotAvailable()),
            this, SIGNAL(finished()));

    /* the application should start even if an exception has been thrown during update check */
    try
    {
        updChecker->checkForUpdates();
    }
    catch (...)
    {
        emit finished();
    }
}

void SoftwareUpdate::updateAvailable(Structs::UpdateInformation info)
{
    UpdateWindow *uw = new UpdateWindow(info);
    uw->show();
    connect(uw, SIGNAL(updateSkipped()),
            this, SIGNAL(finished()));
    UpdateChecker *uc = qobject_cast<UpdateChecker *> (sender());
    delete uc;
}
