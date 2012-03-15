#ifndef QTCONFIG_H
#define QTCONFIG_H

#include <QObject>
#include <QString>

class QSettings;

class QtConfig : public QObject
{
public:
    QtConfig();

public:
    // Set write entry
    void writeEntry (const QString&, const QString&);
    // Set active group
    void setGroup (const QString&);

private:
    QSettings*   m_settings;
    QString m_currentGroup;

};

#endif // QTCONFIG_H
