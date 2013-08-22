/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SUL_STRUCTS_H
#define SUL_STRUCTS_H

#include <QCoreApplication>
#include <QString>
#include <QUrl>

#include "software-update_global.h"

namespace SUL
{
    class SOFTWAREUPDATESHARED_EXPORT Structs
    {
        public:
            struct Application
            {
                QString installedVersion;
                QUrl updateXmlUrl;
            };
            struct UpdateInformation
            {
                QString applicationName;
                QString availableVersion;
                bool isUpdateRequired;
                QUrl updatePackageUrl;
                QString releaseNotes;
            };
    };
}

#endif // SUL_STRUCTS_H
