/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "sul_filedownloader.h"

using namespace SUL;

FileDownloader::FileDownloader()
{
    this->network = new QNetworkAccessManager();
}

FileDownloader::~FileDownloader()
{
    delete this->network;
}

void FileDownloader::startDownload ( QUrl fileUrl, QString destinationFile )
{
    this->filePath = destinationFile;
    QNetworkRequest request ( fileUrl );
    this->reply = this->network->get ( request );
    connect ( this->reply, SIGNAL ( finished() ),
              this, SLOT ( fileDownloaded() ) );
}

void FileDownloader::fileDownloaded()
{
    if ( this->reply->error() != QNetworkReply::NoError )
    {
        emit downloadFailed();
    }
    else
    {
        if ( this->filePath != NULL )
        {
            QFile output ( this->filePath );
            output.open ( QIODevice::WriteOnly );
            QByteArray data = this->reply->readAll();
            output.write ( data );
            output.close();
            emit downloadCompleted ( NULL );
        }
        else
        {
            emit downloadCompleted ( this->reply->readAll() );
        }
    }
}
