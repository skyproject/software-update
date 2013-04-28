/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QFile>
#include <QtXml>
#include <QCoreApplication>

#include "fileoperations.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile xml(QCoreApplication::applicationDirPath() + "/software-update-tasks.xml");

    if (xml.open(QFile::ReadOnly | QFile::Text) == true)
    {
        QDomDocument xmlDocument;
        xmlDocument.setContent(&xml);
        QDomElement root = xmlDocument.firstChildElement();
        QDomElement child = root.firstChildElement();
        std::vector<QString> removeTasks;
        std::map<QString, QString> renameTasks;
        std::map<QString, QString> copyTasks;
        while (child.isNull() != true)
        {
            if (child.tagName() == "removeFile")
            {
                removeTasks.push_back(QCoreApplication::applicationDirPath() + child.attribute("source"));
            }
            else if (child.tagName() == "renameFile")
            {
                renameTasks.insert(std::pair<QString, QString>(QCoreApplication::applicationDirPath()
                                                               + child.attribute("source"),
                                                               QCoreApplication::applicationDirPath()
                                                               + child.attribute("destination")));
            }
            else if (child.tagName() == "copyFile")
            {
                copyTasks.insert(std::pair<QString, QString>(QCoreApplication::applicationDirPath()
                                                             + child.attribute("source"),
                                                             QCoreApplication::applicationDirPath()
                                                             + child.attribute("destination")));
            }
            child = child.nextSiblingElement();
        }
        if (copyTasks.size() > 0)
        {
            FileOperations::copyFiles(copyTasks);
        }
        if (removeTasks.size() > 0)
        {
            FileOperations::removeFiles(removeTasks);
        }
        if (renameTasks.size() > 0)
        {
            FileOperations::renameFiles(renameTasks);
        }
        xml.remove();
    }
    return 0;
}
