/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SUL_UPDATEWINDOW_H
#define SUL_UPDATEWINDOW_H

#include <QCoreApplication>
#include <QMainWindow>

#include "structs.h"

namespace Ui {
class UpdateWindow;
}

namespace SUL
{
class SOFTWAREUPDATESHARED_EXPORT UpdateWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit UpdateWindow(Structs::Application app,
                          Structs::UpdateInformation info,
                          QWidget *parent = 0);
    ~UpdateWindow();
    
private slots:
    void skip();
    void download();

signals:
    void updateSkipped();

private:
    Ui::UpdateWindow *ui;
    Structs::Application application;
};
}

#endif // SUL_UPDATEWINDOW_H
