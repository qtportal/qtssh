/***************************************************************************
                          kssh.h  -  description
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

#ifndef KSSH_H
#define KSSH_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
//#include <kcombobox.h>
//#include <kcompletion.h>
#include <QApplication>
// #include <kconfig.h>
#include <QWidget>
#include <QVector>
#include <QStringList>

#include "ksshdialog.h"

// class KCompletion;

/** KSSH is the base class of the project */
class KSSH : public KSSHDialog
{
  Q_OBJECT 
  public:
    /** construtor */
    KSSH(QWidget* parent=0, const char *name=0);
    /** destructor */
    ~KSSH();

  QString userathost();
  QString cmd();
  QStringList parameters();
  private:
  //  QVector<QString> users;
    QStringList hosts;
    bool opt;
    bool mopt;
    bool uEditor;
    bool hEditor;
    QApplication *app;
    KConfig   *config;
   KCompletion *compUser;
   KCompletion *compHost;

    void saveLists();
    void loadHosts();
    void saveOptions(QString group);
    bool loadOptions(QString group);
 public slots:
   void userFor(const QString&);
   void options();
   void saveAsDefault();
   void moreOptions();
   void ssh();
   void about();
   void userEditor();
   void hostEditor();
   void okEditor();
   void cancelEditor();
};

#endif
