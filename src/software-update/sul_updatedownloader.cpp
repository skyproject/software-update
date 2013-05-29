/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QApplication>
#include <algorithm>
#include <vector>
#include <QtXml>

#include "sul_updatedownloader.h"
#include "sul_filedownloader.h"

using namespace SUL;

UpdateDownloader::UpdateDownloader ( QUrl updateFilesXmlUrl )
{
    FileDownloader *downloader = new FileDownloader();
    connect ( downloader, SIGNAL ( downloadCompleted ( QByteArray ) ),
              this, SLOT ( xmlDownloaded ( QByteArray ) ) );
    connect ( downloader, SIGNAL ( downloadFailed() ),
              this, SIGNAL ( downloadFailed() ) );
    downloader->startDownload ( updateFilesXmlUrl );
}

void UpdateDownloader::xmlDownloaded ( QByteArray xml )
{
    QDomDocument xmlDocument;
    xmlDocument.setContent ( xml );
    QDomElement root = xmlDocument.firstChildElement();
    QDomElement child = root.firstChildElement();
    std::map<QString, QString> files;
    while ( child.isNull() != true )
    {
        if ( child.tagName() == "file" )
        {
            files.insert ( std::pair<QString, QString> ( child.attribute ( "url" ),
                           ( QApplication::applicationDirPath()
                             + child.attribute ( "destination" ) ) ) );
        }
        child = child.nextSiblingElement();
    }
    for ( std::map<QString, QString>::const_iterator it = files.begin();
          it != files.end(); ++it )
    {
        FileDownloader *download = new FileDownloader();
        connect ( download, SIGNAL ( downloadCompleted ( QByteArray ) ),
                  this, SLOT ( fileDownloaded() ) );
        connect ( download, SIGNAL ( downloadFailed() ),
                  this, SIGNAL ( downloadFailed() ) );
        download->startDownload ( it->first, it->second );
        this->downloads.push_back ( download );
    }
    emit downloadStarted();
}

void UpdateDownloader::fileDownloaded()
{
    std::vector<FileDownloader *>::iterator it = std::find ( this->downloads.begin(),
            this->downloads.end(),
            qobject_cast<FileDownloader *> ( sender() ) );
    this->downloads.erase ( it );
    this->downloads.shrink_to_fit();
    if ( this->downloads.size() == 0 )
    {
        emit updateDownloaded();
    }
}
