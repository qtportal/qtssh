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
// along with this library; see the file COPYING.LIB.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.

#ifndef PROCESSHARNESS_H
#define PROCESSHARNESS_H

#include <QObject>
#include <QProcess>

class ProcessHarness : public QObject
{
    Q_OBJECT
public:
    ProcessHarness(QObject *parent = 0);
    ~ProcessHarness();

signals:
    void processDied (ProcessHarness* p);

public:
    void startProcess(const QString& metaUrl);

public slots:
    void stateChanged(QProcess::ProcessState state);
    void error(QProcess::ProcessError error);
    void finished(int st, QProcess::ExitStatus es);
private:
    QProcess*   m_process;

};

#endif // PROCESSHARNESS_H
