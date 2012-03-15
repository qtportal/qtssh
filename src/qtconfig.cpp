#include <QSettings>
#include "qtconfig.h"

QtConfig::QtConfig()
{
    m_settings = new QSettings("qtssh", QSettings::IniFormat );
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
    }
}
