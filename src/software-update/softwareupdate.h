/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SUL_SOFTWAREUPDATE_H
#define SUL_SOFTWAREUPDATE_H

#include <QObject>

#include "software-update_global.h"
#include "structs.h"

namespace SUL
{
    class SOFTWAREUPDATESHARED_EXPORT SoftwareUpdate : public QObject
    {

            Q_OBJECT

        public:
            SoftwareUpdate ( Structs::Application app );

        private slots:
            void updateAvailable ( Structs::UpdateInformation info );

        signals:
            void finished();

        private:
            Structs::Application application;
    };
}

#endif // SUL_SOFTWAREUPDATE_H
