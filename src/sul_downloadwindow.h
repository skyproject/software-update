/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SUL_DOWNLOADWINDOW_H
#define SUL_DOWNLOADWINDOW_H

#include <QMainWindow>
#include <QUrl>

#include "sul_structs.h"

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
            explicit DownloadWindow(QUrl updatePackage, QWidget *parent = 0);
            ~DownloadWindow();

        private slots:
            void downloadingFailed();
            void downloadingFinished();

        private:
            Ui::DownloadWindow *ui;
            Structs::Application application;
    };
}

#endif // SUL_DOWNLOADWINDOW_H
