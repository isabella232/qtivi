/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Copyright (C) 2019 Luxoft Sweden AB
** Copyright (C) 2018 Pelagicore AG
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtIvi module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <private/qgeniviextrasglobal_p.h>
#include <qdltregistration.h>
#include <QString>
#include <QHash>
#include <QMutex>

#include <dlt.h>

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

QT_BEGIN_NAMESPACE

void qtGeniviLogLevelChangedHandler(char context_id[], uint8_t log_level, uint8_t trace_status);

class QDltRegistrationPrivate
{
private:
    struct CategoryInfo {
        CategoryInfo() = default;

        QByteArray m_ctxName;
        QByteArray m_ctxDescription;
        QLoggingCategory *m_category = nullptr;
        DltContext *m_context = nullptr;
        bool m_registered = false;
    };

public:
    QDltRegistrationPrivate(QDltRegistration *parent);

    void registerCategory(const QLoggingCategory *category, DltContext *dltContext, const char *dltCtxName, const char *dltCtxDescription);
    void registerCategory(CategoryInfo &info);
    void unregisterCategories();
    void registerApplication();
    void unregisterApplication();
    void setDefaultCategory(const QString &category);

    DltContext *context(const char *categoryName);
    const QLoggingCategory *dltLogLevelChanged(char context_id[], uint8_t log_level, uint8_t trace_status);

    static DltLogLevelType category2dltLevel(const QLoggingCategory *category);
    static DltLogLevelType severity2dltLevel(QtMsgType type);

private:
    mutable QMutex m_mutex;
    QDltRegistration *const q_ptr;
    Q_DECLARE_PUBLIC(QDltRegistration)
    QString m_dltAppID;
    QString m_dltAppDescription;
    bool m_dltAppRegistered;
    QString m_defaultCategory;
    QHash<QString, CategoryInfo> m_categoryInfoHash;
    bool m_registerOnFirstUse;
    QDltRegistration::LongMessageBehavior m_longMessageBehavior;

    friend void qtGeniviLogLevelChangedHandler(char context_id[], uint8_t log_level, uint8_t trace_status);
};

QT_END_NAMESPACE
