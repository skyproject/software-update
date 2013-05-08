/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SUL_DOWNLOADWINDOW_H
#define SUL_DOWNLOADWINDOW_H

#include <QMainWindow>
#include <QUrl>

#include "Core\updatedownloader.h"
#include "structs.h"

namespace Ui
{
    class DownloadWindow;
}

namespace SUL
{
    class SOFTWAREUPDATESHARED_EXPORT DownloadWindow : public QMainWindow
    {
            Q_OBJECT

        public:
            explicit DownloadWindow ( Structs::Application app,
                                      QWidget *parent = 0 );
            ~DownloadWindow();

        private slots:
            void downloadingFailed();
            void downloadingFinished();
            void updateTasksDownloaded();

        private:
            Ui::DownloadWindow *ui;
            UpdateDownloader *downloader;
            Structs::Application application;
    };
}

#endif // SUL_DOWNLOADWINDOW_H
