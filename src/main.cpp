/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : gio mar 14 18:37:43 CET 2002
    copyright            : (C) 2002 by Andrea Rizzi
    email                : rizzi@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//#include <kcmdlineargs.h>
//#include <kaboutdata.h>
//#include <klocale.h>

#include <QDebug>
#include <QProcess>
#include <QApplication>
#include <QVector>
#include <unistd.h>
#include <stdio.h>
#include "qtssh.h"

// http://www.kde.gr.jp/~ichi/qt/designer-manual-6.html

//static const char *description =
//	I18N_NOOP("KDE SSH - A KDE front end for ssh");
	
//static KCmdLineOptions options[] =
//{
//{"+[user@host]",I18N_NOOP("Connect to \"host\" as \"user\""),0},
//{ "die",I18N_NOOP("Use this for konsole sessions (ignore --keepalive)"),0},
//  { "keepalive",I18N_NOOP("Do not close the dialog after \"Connect\""),0},
//  { 0, 0, 0 }
//  // INSERT YOUR COMMANDLINE OPTIONS HERE
//};

int main(int argc, char *argv[])
{
//    KAboutData aboutData( "kssh", I18N_NOOP("KDE Secure Shell "),
//        VERSION, description, KAboutData::License_GPL,
//        "(c) 2000-2002, Andrea Rizzi", 0, 0, "rizzi@kde.org");
//  aboutData.addAuthor("Andrea Rizzi",0, "rizzi@kde.org");
//  aboutData.addCredit("OpenSSH","Documentation of ssh functions is taken\nfrom the OpenSSH man page",0,"man:/ssh");
//  KCmdLineArgs::init( argc, argv, &aboutData );
//  KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

    QApplication a(argc, argv);
    QtSSHUi *kssh = new QtSSHUi();
    kssh->show();
    int ret=a.exec();

    if(ret==1) {  //Go ssh...
        QString uah;
        uah=kssh->userathost().toLocal8Bit();
        QStringList para;//=kssh->parameters();
        para.append("ssh ollwalli@192.168.1.111");
        // para.insert(0, uah);
        qDebug() << "one " << para;
//        QProcess *sshProcess = new QProcess();
//        sshProcess->start("gnome-terminal", para);
        qDebug () << "sdd";
        system("ssh ollwalli@192.168.1.111");
        //delete sshProcess;
        //return execvp("ssh", "ollwalli@192.168.1.111");
    }
    return ret;
}
