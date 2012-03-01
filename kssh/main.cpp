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

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include <qvector.h>

#include <unistd.h>

#include "kssh.h"

#include <stdio.h>

static const char *description =
	I18N_NOOP("KDE SSH - A KDE front end for ssh");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
	
static KCmdLineOptions options[] =
{
{"+[user@host]",I18N_NOOP("Connect to \"host\" as \"user\""),0},
{ "die",I18N_NOOP("Use this for konsole sessions (ignore --keepalive)"),0},
  { "keepalive",I18N_NOOP("Do not close the dialog after \"Connect\""),0},
  { 0, 0, 0 }
  // INSERT YOUR COMMANDLINE OPTIONS HERE
};

int main(int argc, char *argv[])
{

  KAboutData aboutData( "kssh", I18N_NOOP("KDE Secure Shell "),
    VERSION, description, KAboutData::License_GPL,
    "(c) 2000-2002, Andrea Rizzi", 0, 0, "rizzi@kde.org");
  aboutData.addAuthor("Andrea Rizzi",0, "rizzi@kde.org");
  aboutData.addCredit("OpenSSH","Documentation of ssh functions is taken\nfrom the OpenSSH man page",0,"man:/ssh");
  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

  KApplication a;
  KSSH *kssh = new KSSH();
  a.setMainWidget(kssh);
  kssh->show();  
  int ret=a.exec();

  if(ret==1)  //Go ssh...
    {
    QCString uah;
   uah=kssh->userathost().local8Bit();
     QVector<char> vec;
     int n;
     QCString *q;
     QStringList para=kssh->parameters();
     vec.resize(n=(para.count()+3));
     vec.insert(0,"ssh");
     vec.insert(1,(const char*)uah);
     for(int i=2;i<n-1;i++) {
         q = new QCString(para[i-2].local8Bit());
         vec.insert(i,(const char*)*q);
    //     fprintf(stderr,"%d %d %s\n",n,i,vec[i]);
      //    usleep(100000);
    }
     vec.insert(n-1,0);
   //  warning(uah);
   //   fprintf(stderr,"%d #%s %s#\n",n,vec[0],vec[1]);
   //       usleep(100000);

   //   usleep(900000);

   printf("\033]0;%s... \007\n", (const char *)uah);
    return execvp("ssh",vec.data());
    }


  return 0;
}
