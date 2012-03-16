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
#include <QSettings>
#include "qtconfig.h"

QtConfig::QtConfig()
{
    m_settings = new QSettings("qtssh.ini", QSettings::IniFormat );
    qDebug () << m_settings->fileName();
    m_currentGroup = "";
}

void QtConfig::setGroup(const QString &sg)
{
    if (sg.length())  {
        m_currentGroup = sg;
    } else  {
        m_currentGroup.clear();
    }

}

void QtConfig::writeEntry(const QString &wk, const QString& data)
{
    if (m_currentGroup.length())  {
        m_settings->beginGroup(m_currentGroup);
        m_settings->setValue(wk,data);
        m_settings->endGroup();
        qDebug () << "writeentry";
    }
}
