/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QString>
#include <vector>
#include <map>

class FileOperations
{
    public:
        static void removeFiles ( std::vector<QString> files );
        static void renameFiles ( std::map<QString, QString> files );
        static void copyFiles ( std::map<QString, QString> files );
};

#endif // FILEOPERATIONS_H
