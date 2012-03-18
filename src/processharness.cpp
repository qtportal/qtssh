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

#include <QLocale>
#include <QDebug>
#include "processharness.h"

ProcessHarness::ProcessHarness(QObject *parent) :
    QObject(parent)
{
    m_process = new QProcess(this);
    connect(m_process, SIGNAL(stateChanged(QProcess::ProcessState)),
        this, SLOT(stateChanged(QProcess::ProcessState)));
    connect(m_process, SIGNAL(finished (int, QProcess::ExitStatus)), this,
            SLOT (finished(int, QProcess::ExitStatus)));
}

ProcessHarness::~ProcessHarness()
    {
    if (m_process->state() != QProcess::NotRunning)
        {
        // Close process if it is running
        m_process->close();
        }
    delete m_process;
    }

void ProcessHarness::startProscess(const QString& args)
{
    QStringList arguments;
    arguments.append(args.trimmed());
    m_process->start(program, arguments);
}

void ProcessHarness::error(QProcess::ProcessError error)
{
    switch (error)
        {
        case QProcess::FailedToStart:
        case QProcess::Crashed:
        case QProcess::Timedout:
        case QProcess::ReadError:
        case QProcess::WriteError:
        case QProcess::UnknownError:
            {
            // TODO: Handle error
            break;
            }
        default:
            {
            break;
            }
        };
}

void ProcessHarness::finished(int /*st*/, QProcess::ExitStatus /*es*/)
{
    // notify parent that we ready to die
}

void ProcessHarness::stateChanged(QProcess::ProcessState state)
{
    qDebug () << "ProcessHarness::stateChanged" << state;
    switch (state)
        {
        case QProcess::NotRunning:
            {
            // Most probaply we want to notify our parent that we have died!
            emit processDied(this);
            }
        break;
        case QProcess::Starting:
        case QProcess::Running:
            {
            // TODO: do what you want with
            // different states
            break;
            }
        default:
            {
            break;
            }
        };
}
