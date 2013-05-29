/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QFile>

#include "fileoperations.h"

void FileOperations::copyFiles ( std::map<QString, QString> files )
{
    for ( std::map<QString, QString>::const_iterator it = files.begin();
          it != files.end(); ++it )
    {
        QFile file ( it->first );
        file.copy ( it->second );
    }
}

void FileOperations::removeFiles ( std::vector<QString> files )
{
    for ( std::vector<QString>::const_iterator it = files.begin();
          it != files.end(); ++it )
    {
        QFile file ( *it );
        file.remove();
    }
}

void FileOperations::renameFiles ( std::map<QString, QString> files )
{
    for ( std::map<QString, QString>::const_iterator it = files.begin();
          it != files.end(); ++it )
    {
        QFile file ( it->first );
        file.rename ( it->second );
    }
}
