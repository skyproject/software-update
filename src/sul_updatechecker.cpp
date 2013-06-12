/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QtXml>

#include "sul_filedownloader.h"
#include "sul_updatechecker.h"

using namespace SUL;

UpdateChecker::UpdateChecker ( Structs::Application app )
{
    this->application = app;
}

void UpdateChecker::checkForUpdates()
{
    FileDownloader *downloader = new FileDownloader();
    connect ( downloader, SIGNAL ( downloadCompleted ( QByteArray ) ),
              this, SLOT ( xmlDownloaded ( QByteArray ) ) );
    connect ( downloader, SIGNAL ( downloadFailed() ),
              this, SIGNAL ( updateIsNotAvailable() ) );
    downloader->startDownload ( application.updateXmlUrl );
}

void UpdateChecker::xmlDownloaded ( QByteArray xml )
{
    QDomDocument xmlDocument;
    xmlDocument.setContent ( xml );
    QString application, currentVersion, requiredVersion, releaseNotes, updatePackage;
    QDomElement root = xmlDocument.firstChildElement();
    QDomElement child = root.firstChildElement();
    while ( child.isNull() != true )
    {
        if ( child.tagName() == "name" )
        {
            application = child.text();
        }
        else if ( child.tagName() == "version" )
        {
            currentVersion = child.text();
        }
        else if ( child.tagName() == "minVersion" )
        {
            requiredVersion = child.text();
        }
        else if ( child.tagName() == "update" )
        {
            updatePackage = child.text();
        }
        else if ( child.tagName() == "notes" )
        {
            releaseNotes = child.text();
        }
        child = child.nextSiblingElement();
    }
    if ( isUpdateAvailable ( currentVersion ) == true )
    {
        Structs::UpdateInformation info;
        info.applicationName = application;
        info.currentVersion = currentVersion;
        info.isUpdateRequired = isUpdateRequired ( requiredVersion );
        info.updatePackageUrl = QUrl ( updatePackage );
        info.releaseNotes = releaseNotes;
        emit updateAvailable ( info );
    }
    else
    {
        emit updateIsNotAvailable();
    }
}

bool UpdateChecker::isUpdateAvailable ( QString currentVersion )
{
    QStringList current = currentVersion.split ( "." );
    QStringList installed = this->application.installedVersion.split ( "." );
    if ( current[0] > installed[0] )
    {
        return true;
    }
    else if ( current[1] > installed[1] )
    {
        return true;
    }
    else if ( current[2] > installed[2] )
    {
        return true;
    }
    else if ( current[3] > installed[3] )
    {
        return true;
    }
    return false;
}

bool UpdateChecker::isUpdateRequired ( QString requiredVersion )
{
    QStringList required = requiredVersion.split ( "." );
    QStringList installed = this->application.installedVersion.split ( "." );
    if ( required[0] > installed[0] )
    {
        return true;
    }
    else if ( required[1] > installed[1] )
    {
        return true;
    }
    else if ( required[2] > installed[2] )
    {
        return true;
    }
    else if ( required[3] > installed[3] )
    {
        return true;
    }
    return false;
}
