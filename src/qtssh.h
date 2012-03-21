
// Copyright (c) 2012 Olli-Pekka Wallin.
//
// Original idea and concept by Andrea Rizzi 2002
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

#ifndef QTSSH_H
#define QTSSH_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QApplication>
#include <QWidget>
#include <QVector>
#include <QStringList>

#include "../ui_qtsshdialog.h"
#include "qtconfig.h"

namespace Ui  {
    class QtSSHDialog;
}

class QListWidgetItem;

class QtSSHUi : public QDialog
{
  Q_OBJECT 
public:

    // construtor
    QtSSHUi(QWidget* parent=0);

    // destructor
    ~QtSSHUi();

    QString userathost();
    QString cmd();
    QStringList parameters();

private:
    QVector<QString> users;
    //KCompletion *compUser;
   // KCompletion *compHost;

    bool eventFilter(QObject *object, QEvent *event);

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

    void checkTextChanged (const QString&);
    void currentItemChanged(QListWidgetItem*);

private:
    void deleteCurrent ();
    void editCurrent ();
    void insertNewItem ();

private:
    QStringList m_hosts;
    bool m_opt;
    bool m_mopt;
    bool m_editor_is_user_mode;
    bool m_editor_is_hosts_mode;
    QApplication *app;
    QtConfig    *m_config;
    Ui::QtSSHDialog *ui;
    QString m_item_text;
};

#endif      // QTSSH_H
