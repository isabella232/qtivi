/****************************************************************************
**
** Copyright (C) 2015 Pelagicore AG
** Contact: http://www.qt.io/ or http://www.pelagicore.com/
**
** This file is part of the QtIVI module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21-PELAGICORE$
** Commercial License Usage
** Licensees holding valid commercial Qt IVI licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Pelagicore. For licensing terms
** and conditions, contact us at http://www.pelagicore.com.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, Pelagicore gives you certain additional
** rights. These rights are described in Pelagicore LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
** SPDX-License-Identifier: LGPL-2.1
**
****************************************************************************/

#ifndef QDLT_H
#define QDLT_H

#include <QGlobalStatic>
#include <QtGlobal>
#include <QtGeniviExtras/qdltregistration.h>

QT_BEGIN_NAMESPACE

#define QDLT_REGISTER_APPLICATION(APP, DESCRIPTION) \
QT_BEGIN_NAMESPACE \
struct QDltAppRegistrator { \
    QDltAppRegistrator() { globalDltRegistration()->registerApplication(APP, DESCRIPTION); } \
}; \
static QDltAppRegistrator qdltAppRegistrator; \
QT_END_NAMESPACE \


#define QDLT_LOGGING_CATEGORY(CATEGORY, CATEGORYNAME, DLT_CTX_NAME, DLT_CTX_DESCRIPTION) \
Q_LOGGING_CATEGORY(CATEGORY, CATEGORYNAME) \
QDLT_REGISTER_LOGGING_CATEGORY(CATEGORY, CATEGORYNAME, DLT_CTX_NAME, DLT_CTX_DESCRIPTION) \

#define QDLT_REGISTER_LOGGING_CATEGORY(CATEGORY, CATEGORYNAME, DLT_CTX_NAME, DLT_CTX_DESCRIPTION) \
QT_BEGIN_NAMESPACE \
struct QDlt ## CATEGORY ## Registrator { \
    QDlt ## CATEGORY ## Registrator() { globalDltRegistration()->registerCategory(&CATEGORY() , DLT_CTX_NAME, DLT_CTX_DESCRIPTION); } \
}; \
static QDlt ## CATEGORY ## Registrator qdlt ## CATEGORY ## registrator; \
QT_END_NAMESPACE \

#define QDLT_FALLBACK_CATEGORY(CATEGORY) \
QT_BEGIN_NAMESPACE \
struct QDltDefaultRegistrator { \
    QDltDefaultRegistrator() { globalDltRegistration()->setDefaultContext(CATEGORY().categoryName()); } \
}; \
static QDltDefaultRegistrator qdltDefaultRegistrator; \
QT_END_NAMESPACE \

QT_END_NAMESPACE

#endif // QDLT_H

