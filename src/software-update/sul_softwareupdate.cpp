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

SoftwareUpdate::SoftwareUpdate ( Structs::Application app )
{
    this->application = app;
    UpdateChecker *updChecker = new UpdateChecker ( app );
    connect ( updChecker, SIGNAL ( updateAvailable ( Structs::UpdateInformation ) ),
              this, SLOT ( updateAvailable ( Structs::UpdateInformation ) ) );
    connect ( updChecker, SIGNAL ( updateIsNotAvailable() ),
              this, SIGNAL ( finished() ) );
    updChecker->checkForUpdates();
}

void SoftwareUpdate::updateAvailable ( Structs::UpdateInformation info )
{
    UpdateWindow *uw = new UpdateWindow ( this->application, info );
    uw->show();
    connect ( uw, SIGNAL ( updateSkipped() ),
              this, SIGNAL ( finished() ) );
    UpdateChecker *uc = qobject_cast<UpdateChecker *> ( sender() );
    delete uc;
}
