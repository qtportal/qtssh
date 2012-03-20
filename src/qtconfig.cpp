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

#include <QDebug>
#include <QStringList>
#include <QSettings>
#include "qtconfig.h"

QtConfig::QtConfig()
{
    m_settings = new QSettings("qtssh.ini", QSettings::IniFormat );
    // qDebug () << m_settings->fileName();
    m_currentGroup = "";
}

QtConfig::~QtConfig ()
{
    delete m_settings;
}

void QtConfig::setGroup(const QString &sg)
{
    if (sg.length())  {
        m_currentGroup = sg;
    } else  {
        m_currentGroup.clear();
    }

}

QString QtConfig::readEntry(const QString& key) const
{
    QVariant data;
    if (m_currentGroup.length())  {
        m_settings->beginGroup(m_currentGroup);
        qDebug () << key;
        if (m_settings->contains(key))  {
            data = m_settings->value(key);
        }
        m_settings->endGroup();
    }
    return data.toString();
}

void QtConfig::readEntry(const QString &key, QStringList& list)
{
    if (m_currentGroup.length())  {
        m_settings->beginGroup(m_currentGroup);
        int count = m_settings->beginReadArray(key);
        for (int i = 0; i < count; ++i) {
            m_settings->setArrayIndex(i);
            QString host = m_settings->setValue(key);
            qDebug () << host;
            list.append(host);
        }
        m_settings->endArray();
        m_settings->endGroup();
        m_settings->sync();
    }
}

void QtConfig::writeEntry(const QString &wk, const QStringList& list)
{
    if (m_currentGroup.length())  {
        m_settings->beginGroup(m_currentGroup);
        m_settings->beginWriteArray(wk);
        for (int i = 0; i < list.size(); ++i) {
            m_settings->setArrayIndex(i);
            m_settings->setValue(wk, list.at(i));
        }
        m_settings->endArray();
        m_settings->endGroup();
        m_settings->sync();
    }
}

void QtConfig::writeEntry(const QString &wk, const QString& data)
{
    if (m_currentGroup.length())  {
        m_settings->beginGroup(m_currentGroup);
        m_settings->setValue(wk,data);
        m_settings->endGroup();
        m_settings->sync();
    }
}
