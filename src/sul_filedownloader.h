/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SUL_FILEDOWNLOADER_H
#define SUL_FILEDOWNLOADER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QTemporaryFile>
#include <QNetworkReply>
#include <QByteArray>
#include <QObject>

#include "software-update_global.h"

namespace SUL
{
    class SOFTWAREUPDATESHARED_EXPORT FileDownloader : public QObject
    {
            Q_OBJECT

        public:
            FileDownloader();
            ~FileDownloader();
            void startDownload(QUrl fileUrl, QString destinationFile = "");

        private slots:
            void fileDownloaded();

        signals:
            void downloadFailed();
            void downloadCompleted(QByteArray file);

        private:
            QNetworkAccessManager *network;
            QByteArray m_DownloadedData;
            QNetworkReply *reply;
            QString filePath;
    };
}

#endif // SUL_FILEDOWNLOADER_H
