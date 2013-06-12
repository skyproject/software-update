/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of software-update library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SUL_SOFTWAREUPDATE_GLOBAL_H
#define SUL_SOFTWAREUPDATE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SOFTWAREUPDATE_LIBRARY)
#  define SOFTWAREUPDATESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SOFTWAREUPDATESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SUL_SOFTWAREUPDATE_GLOBAL_H
