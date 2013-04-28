/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SUL_UPDATESCHECK_H
#define SUL_UPDATESCHECK_H

#include <QByteArray>
#include <QObject>

#include "structs.h"

namespace SUL
{
class SOFTWAREUPDATESHARED_EXPORT UpdateChecker : public QObject
{

Q_OBJECT

public:
    UpdateChecker(Structs::Application app);
    void checkForUpdates();

private slots:
    void xmlDownloaded(QByteArray xml);

signals:
    void updateAvailable(Structs::UpdateInformation info);
    void updateIsNotAvailable();

private:
    bool isUpdateAvailable(QString currentVersion);
    bool isUpdateRequired(QString requiredVersion);
    Structs::Application application;
};
}

#endif // SUL_UPDATESCHECK_H
