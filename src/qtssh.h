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
#include <QApplication>
#include <QWidget>
#include <QVector>
#include <QStringList>

#include "../ui_qtsshdialog.h"

namespace Ui  {
    class QtSSHDialog;
}

class QtSSHUi : public QDialog
{
  Q_OBJECT 
public:

    /** construtor */
    QtSSHUi(QWidget* parent=0);

    /** destructor */
    ~QtSSHUi();

    QString userathost();
    QString cmd();
    QStringList parameters();
private:
  //  QVector<QString> users;
    //KCompletion *compUser;
   // KCompletion *compHost;

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

private:
   QStringList hosts;
   bool opt;
   bool mopt;
   bool uEditor;
   bool hEditor;
   QApplication *app;
//   KConfig   *config;

   Ui::QtSSHDialog *ui;
};

#endif
