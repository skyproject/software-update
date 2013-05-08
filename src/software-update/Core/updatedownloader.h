/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SUL_UPDATEDOWNLOADER_H
#define SUL_UPDATEDOWNLOADER_H

#include <QObject>
#include <vector>
#include <QUrl>

#include "Core/filedownloader.h"

namespace SUL
{
    class SOFTWAREUPDATESHARED_EXPORT UpdateDownloader : public QObject
    {

            Q_OBJECT

        public:
            UpdateDownloader ( QUrl updateFilesXmlUrl );
            void downloadUpdates();

        private slots:
            void fileDownloaded();
            void xmlDownloaded ( QByteArray xml );

        signals:
            void downloadFailed();
            void downloadStarted();
            void updateDownloaded();

        private:
            std::vector<FileDownloader *> downloads;
    };
}

#endif // SUL_UPDATEDOWNLOADER_H
