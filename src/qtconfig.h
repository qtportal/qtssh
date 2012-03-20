// Copyright (c) 2012 Olli-Pekka Wallin
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License version 2.1 as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along <ith this library; see the file COPYING.LIB.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.

#ifndef QTCONFIG_H
#define QTCONFIG_H

#include <QObject>
#include <QString>

class QSettings;

class QtConfig : public QObject
{
public:
    QtConfig();
    ~QtConfig ();

public:
    // Set write entry
    void writeEntry (const QString&, const QString&);
    // Write group list
    void writeEntry (const QString&, const QStringList&);
    // Read list of entrys from settings store.
    void readEntry (const QString&, QStringList&);
    // Read a single entry from settings store
    QString readEntry (const QString& key) const;
    // Set active group
    void setGroup (const QString&);

private:
    QSettings*   m_settings;
    QString m_currentGroup;

};

#endif // QTCONFIG_H
