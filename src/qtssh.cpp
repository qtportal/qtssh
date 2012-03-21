// Copyright (c) 2012 Olli-Pekka Wallin
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

#include <QLocale>
#include <QLineEdit>
#include <QListWidget>
#include <QDesktopWidget>
#include <QDebug>
#include <QToolButton>
#include <QPushButton>
#include <QGroupBox>
#include <QLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>

#include "qtsshconstants.h"
#include "qtssh.h"

// optionsGB -> groupbox -> grbOptions
// optionsPB -> pushButton --> btnShowOptions
// editorF --> frame --> frmMore ???
// savePB --> pushbutton --> btnSaveAsDefault
// hostsCB --> cmbHosts
// userCB --> cmbUserName
// compUser -->
// moreF --> frame with more options
// userHostELB --> KEditListBox --> Users and Hosts editing (adding and removing items.

QtSSHUi::QtSSHUi(QWidget *parent) : QDialog(parent), ui(new Ui::QtSSHDialog)
{
    ui->setupUi(this);

    m_config = new QtConfig ();

    QLayout *lay;
    lay=layout();
    if(lay)  {
        lay->setSizeConstraint(QLayout::SetFixedSize);
    }

//    app=KApplication::kApplication();
//    config=app->config();

    m_opt=false;
    m_mopt=false;


    ui->frmHostUser->hide();

    // show();
//    QSize s=size();
//    QPoint p(s.width(),s.height());
//    QPoint po=pos();
//    QDesktopWidget *d = QApplication::desktop();
//    int w=d->width();                   // returns desktop width
//    int h=d->height ();                  // returns desktop height
//    int x=0,y=0;
//    if((p+po).x()>w)
//        po.setX(x=w-p.x());
//    if((p+po).y()>h)
//        po.setY(y=h-p.y());

//    if(x<0) po.setX(0);
//    if(y<0) po.setY(0);

//     move(po);
    ui->grbOptions->hide();
    ui->moreF->hide();

    adjustSize();

    ui->cmbHosts->setFocus();
    ui->cmbHosts->clearEditText();
    ui->listUserHostEditor->installEventFilter( this );

    ui->cmbUserName->insertItem(0,"");
    ui->cmbHosts->insertItem(0,"");

    loadHosts();
    loadOptions(GroupDefaultConfig);

    //    connect(aboutPB,SIGNAL(clicked()),this,SLOT(about()));
    connect(ui->btnShowOptions,SIGNAL(clicked()),this,SLOT(options()));
    connect(ui->btnMore,SIGNAL(clicked()),this,SLOT(moreOptions()));

    connect(ui->btnEditHosts,SIGNAL(clicked()),this,SLOT(hostEditor()));
    connect(ui->btnEditUsers,SIGNAL(clicked()),this,SLOT(userEditor()));
    connect(ui->cancelPB,SIGNAL(clicked()),this,SLOT(cancelEditor()));
    connect(ui->okPB,SIGNAL(clicked()),this,SLOT(okEditor()));

    connect(ui->btnConnect,SIGNAL(clicked()),this,SLOT(ssh()));
    connect(ui->btnSaveAsDefault,SIGNAL(clicked()),this,SLOT(saveAsDefault()));
    connect(ui->btnQuit,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(ui->cmbHosts,SIGNAL(editTextChanged(QString)), this, SLOT(checkTextChanged(QString)));
    connect(ui->cmbUserName,SIGNAL(editTextChanged(QString)), this, SLOT(checkTextChanged(QString)));
    connect(ui->listUserHostEditor, SIGNAL(itemChanged(QListWidgetItem*)), this,
            SLOT(currentItemChanged(QListWidgetItem*)));

    m_config->setGroup(GroupGeneral);
    QString lastHost = m_config->readEntry(EntryLastHost);
    int index = ui->cmbHosts->findData(lastHost);
    ui->cmbHosts->setCurrentIndex(index);

    checkTextChanged(QString());

}

QtSSHUi::~QtSSHUi()
{
    delete m_config;
    delete ui;
}

QString QtSSHUi::userathost()
{
    return QString(ui->cmbUserName->currentText()+"@"+ui->cmbHosts->currentText());
}

QString QtSSHUi::cmd()
{
    int n;
    QString ret;
    QStringList para=parameters();
    n=para.count();
    ret="ssh "+ui->cmbUserName->currentText()+"@"+ui->cmbHosts->currentText()+" ";
    for(int i=0;i<n;i++)
        ret+=para[i] + " ";
    return ret;
}

void QtSSHUi::options()
{
    ui->frmHostUser->hide();//to be sure
    m_opt=!m_opt;
    if(m_opt) {
        ui->btnShowOptions->setText(tr("Hide options"));
        ui->grbOptions->show();
     } else   {
        ui->btnShowOptions->setText(tr("Show options"));
        ui->grbOptions->hide();
     }
 }

void QtSSHUi::moreOptions()
{
      m_mopt=!m_mopt;
      if(m_mopt)  {
          ui->btnMore->setText(tr("Less..."));
          ui->moreF->show();
        }
     else
       {
        ui->btnMore->setText(tr("More.."));
        ui->moreF->hide();
      }

 }

void QtSSHUi::checkTextChanged(const QString &)
{
    bool ok = !ui->cmbHosts->currentText().isEmpty()
              && !ui->cmbUserName->currentText().isEmpty();
    ui->btnConnect->setEnabled(ok);
}

void QtSSHUi::about()
{
//    KAboutApplication *aa = new KAboutApplication;
//    aa->show();
}

void QtSSHUi::ssh()
{
    m_config->setGroup("General");
    m_config->writeEntry("LastHost",ui->cmbHosts->currentText());  

//    if(saveCB->isChecked())
//        saveOptions(hostCB->currentText()+"-Options");

    QStringList arglist = QApplication::arguments();
    if(arglist.contains("die") )
        qApp->exit(1);
    else  {
//        QString caption="KSSH: %1" ;
//        QString terminal = KGlobal::config()->readEntry("TerminalApplication", "konsole");
//        QString ex(terminal+" -T \""+caption.arg(userathost())+ "\"  -e "+cmd());
//        KRun::runCommand((const char *)ex.local8Bit());
//        if(!args->isSet("keepalive") ) qApp->quit();
    }
}

void QtSSHUi::loadHosts()
{
    m_config->setGroup(GroupHostList);
    m_hosts.clear();
    m_config->readEntry(EntryHosts, m_hosts);
    if (m_hosts.count())
        ui->cmbHosts->insertItems(1, m_hosts);
}

void QtSSHUi::saveAsDefault()
{
//    config->setGroup("DefaultConfig");
//    config->writeEntry("-X",XCB->isChecked());
//    config->writeEntry("-x",xCB->isChecked());
//    config->writeEntry("-p",pCB->isChecked());
//    config->writeEntry("-L",LCB->isChecked());
//    config->writeEntry("-R",RCB->isChecked());
//    config->writeEntry("-P",PCB->isChecked());
//    config->writeEntry("-1",ssh1CB->isChecked());
//    config->writeEntry("-2",ssh2CB->isChecked());
//    config->writeEntry("-a",aCB->isChecked());
//    config->writeEntry("-A",ACB->isChecked());
//    config->writeEntry("-c",cCB->isChecked());
//    config->writeEntry("-C",CCB->isChecked());
//    config->writeEntry("-F",FCB->isChecked());
//    config->writeEntry("-4",IPV4CB->isChecked());
//    config->writeEntry("-6",IPV6CB->isChecked());
//    config->writeEntry("-b",bCB->isChecked());
//    config->writeEntry("-c1",c1CB->isChecked());
//    config->writeEntry("-e",eCB->isChecked());
//    config->writeEntry("-f",fCB->isChecked());
//    config->writeEntry("-g",gCB->isChecked());
//    config->writeEntry("-i",iCB->isChecked());
//    config->writeEntry("-I",ICB->isChecked());
//    config->writeEntry("-k",kCB->isChecked());
//    config->writeEntry("-m",mCB->isChecked());
//    config->writeEntry("-n",nCB->isChecked());
//    config->writeEntry("-N",NCB->isChecked());
//    config->writeEntry("-q",qCB->isChecked());
//    config->writeEntry("-v",vCB->isChecked());
//    config->writeEntry("-s",sCB->isChecked());
//    config->writeEntry("-T",TCB->isChecked());
//    config->writeEntry("-t",tCB->isChecked());
//    config->writeEntry("-o",oCB->isChecked());

//    config->writeEntry("Port",portSB->value());
//    config->writeEntry("VerboseLevel",vSB->value());
//    config->writeEntry("Cipher",ccCB->currentItem());

//    config->writeEntry("LLE",LLE->text());
//    config->writeEntry("FLE",FLE->lineEdit()->text());
//    config->writeEntry("RLE",RLE->text());
//    config->writeEntry("cLE",cLE->text());

//    config->writeEntry("eLE",eLE->text());
//    config->writeEntry("bLE",bLE->text());
//    config->writeEntry("iLE",iLE->lineEdit()->text());

//    config->writeEntry("ILE1",ILE->lineEdit()->text());
//    config->writeEntry("mLE",mLE->text());
//    config->writeEntry("oLE",oLE->text());
//    config->writeEntry("Command",commandLE->text());
}

QStringList QtSSHUi::parameters()
{
  QStringList ret;
//    int count=0;
//   if(XCB->isChecked())
//    {
//      ret.append("-X");
//      count++;
//   }

//  if(xCB->isChecked())
//    {
//      ret.append("-x");
//      count++;
//   }
//  if(pCB->isChecked())
//    {
//      ret.append("-p");
//      ret.append(QString::number(portSB->value()));
//      count+=2;
//   }


//  if(LCB->isChecked())
//    {
//      ret.append("-L");
//      ret.append(LLE->text());
//      count+=2;
//   }
//  if(RCB->isChecked())
//    {
//      ret.append("-R");
//      ret.append(RLE->text());
//      count+=2;
//   }
//  if(PCB->isChecked())
//    {
//      ret.append("-P");
//      count++;
//   }
//  if(ssh1CB->isChecked())
//    {
//      ret.append("-1");
//      count++;
//   }
//  if(ssh2CB->isChecked())
//    {
//      ret.append("-2");
//      count++;
//   }
//  if(aCB->isChecked())
//    {
//      ret.append("-a");
//      count++;
//   }
//  if(ACB->isChecked())
//    {
//      ret.append("-A");
//      count++;
//   }
//  if(cCB->isChecked())
//    {
//      ret.append("-c");
//      ret.append(ccCB->currentText());
//      count+=2;
//   }
//  if(CCB->isChecked())
//    {
//      ret.append("-C");
//      count++;
//   }
//  if(FCB->isChecked())
//    {
//      ret.append("-F");
//      ret.append(FLE->lineEdit()->text());
//      count+=2;
//   }
//  if(IPV4CB->isChecked())
//    {
//      ret.append("-4");
//      count++;
//   }
//  if(IPV6CB->isChecked())
//    {
//      ret.append("-6");
//      count++;
//   }
//  if(bCB->isChecked())
//    {
//      ret.append("-b");
//      ret.append(bLE->text());
//      count+=2;
//   }
//  if(c1CB->isChecked())
//    {
//      ret.append("-c");
//      ret.append(cLE->text());
//      count+=2;
//   }
//  if(eCB->isChecked())
//    {
//      ret.append("-e");
//      ret.append(eLE->text());
//      count+=2;
//   }
//  if(fCB->isChecked())
//    {
//      ret.append("-f");
//      count++;
//   }
//  if(gCB->isChecked())
//    {
//      ret.append("-g");
//      count++;
//   }
//  if(iCB->isChecked())
//    {
//      ret.append("-i");
//      ret.append(iLE->lineEdit()->text());
//      count+=2;
//   }
//  if(ICB->isChecked())
//    {
//      ret.append("-I");
//      ret.append(ILE->lineEdit()->text());
//      count+=2;
//   }
//  if(kCB->isChecked())
//    {
//      ret.append("-k");
//      count++;
//   }
//  if(mCB->isChecked())
//    {
//      ret.append("-m");
//      ret.append(mLE->text());
//      count+=2;
//   }
//  if(nCB->isChecked())
//    {
//      ret.append("-n");
//      count++;
//   }
//  if(NCB->isChecked())
//    {
//      ret.append("-N");
//      count++;
//   }
//  if(qCB->isChecked())
//    {
//      ret.append("-q");
//      count++;
//   }
//  if(vCB->isChecked())
//    {
//      QString v="-";
//      for(int i=0;i<vSB->value();i++)
//         v+="v";
//      ret.append(v);
//      count++;
//   }
//  if(sCB->isChecked())
//    {
//      ret.append("-s");
//      count++;
//   }
//  if(TCB->isChecked())
//    {
//      ret.append("-T");
//      count++;
//   }
//  if(tCB->isChecked())
//    {
//      ret.append("-t");
//      count++;
//   }
//  if(oCB->isChecked())
//    {
//      ret.append("-o");
//      ret.append(oLE->text());
//      count+=2;
//    }

//  QString com=commandLE->text();
//  if(!com.isEmpty()) ret.append(com);

return ret;
}


void QtSSHUi::saveLists()
{
    QStringList hostData;
    int count = ui->cmbHosts->count();
    for (int i =0; i < count; i++)   {
        hostData.append(ui->cmbHosts->itemText(i));
    }

    m_config->setGroup(GroupHostList);
    // m_config->writeEntry("Host",ui->cmbHosts->itemData());
    m_config->setGroup(ui->cmbHosts->currentText()+"-User List");
    // m_config->writeEntry("User",compUser->items());
}


void QtSSHUi::saveOptions(QString group)
{

// bool setFlag;
// bool ret=false;

// saveLists();
// config->setGroup(hostCB->currentText()+"-User List");
// config->writeEntry("LastUsed",userCB->currentText());

//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-X");
//  config->setGroup(group);
//  if(XCB->isChecked()!=setFlag)
//   config->writeEntry("-X",XCB->isChecked());
//     else
//   config->deleteEntry("-X");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-x");
//  config->setGroup(group);
//  if(xCB->isChecked()!=setFlag)
//   config->writeEntry("-x",xCB->isChecked());
//     else
//   config->deleteEntry("-x");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-p");
//  config->setGroup(group);
//  if(pCB->isChecked()!=setFlag)
//   {
//     config->writeEntry("-p",pCB->isChecked());
//   }
//    else
//    {
//      config->deleteEntry("-p");
//   }

// config->setGroup("DefaultConfig");
//  int pp=setFlag=config->readNumEntry("Port");
//  config->setGroup(group);
// if(portSB->value()!=pp)
//   {
//     config->writeEntry("Port",portSB->value());
//   }
//    else
//    {
//      config->deleteEntry("Port");
//   }

//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-L");
//  config->setGroup(group);
//  if(LCB->isChecked()!=setFlag) {
//   config->writeEntry("-L",LCB->isChecked());
//    }
//     else {
//      config->deleteEntry("-L");
//     }

//  config->setGroup("DefaultConfig");
//  QString  Lstr=config->readEntry("LLE");
//  config->setGroup(group);
//  if(LLE->text()!=Lstr)
//   config->writeEntry("LLE",LLE->text());
//     else
//   config->deleteEntry("LLE");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-R");
//  config->setGroup(group);
//  if(RCB->isChecked()!=setFlag)
//   {config->writeEntry("-R",RCB->isChecked());
//  }   else
// {
//   config->deleteEntry("-R");
//}

//  config->setGroup("DefaultConfig");
//QString  str =config->readEntry("RLE");
//  config->setGroup(group);
//  if(RLE->text()!=str)
//   {
//  config->writeEntry("RLE",RLE->text());
//  }   else
// { config->deleteEntry("RLE");
//}


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-P");
//  config->setGroup(group);
//  if(PCB->isChecked()!=setFlag)
//   config->writeEntry("-P",PCB->isChecked());
//     else
//   config->deleteEntry("-P");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-1");
//  config->setGroup(group);
//  if(ssh1CB->isChecked()!=setFlag)
//   config->writeEntry("-1",ssh1CB->isChecked());
//     else
//   config->deleteEntry("-1");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-2");
//  config->setGroup(group);
//  if(ssh2CB->isChecked()!=setFlag)
//   config->writeEntry("-2",ssh2CB->isChecked());
//     else
//   config->deleteEntry("-2");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-a");
//  config->setGroup(group);
//  if(aCB->isChecked()!=setFlag)
//   config->writeEntry("-a",aCB->isChecked());
//     else
//   config->deleteEntry("-a");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-A");
//  config->setGroup(group);
//  if(ACB->isChecked()!=setFlag)
//   config->writeEntry("-A",ACB->isChecked());
//     else
//   config->deleteEntry("-A");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-c");
//  config->setGroup(group);
//  if(cCB->isChecked()!=setFlag)
//  {
//    config->writeEntry("-c",cCB->isChecked());
//   }  else
//   {
//     config->deleteEntry("-c");
//   }

//  config->setGroup("DefaultConfig");
//  int ii=config->readBoolEntry("Cipher");
//  config->setGroup(group);
//  if(ccCB->currentItem()!=ii)
//  {
//    config->writeEntry("Cipher",ccCB->currentItem());
//   }
//  else
//   {
//     config->deleteEntry("Cipher");
//   }


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-C");
//  config->setGroup(group);
//  if(CCB->isChecked()!=setFlag)
//   config->writeEntry("-C",CCB->isChecked());
//     else
//   config->deleteEntry("-C");



//  config->setGroup("DefaultConfig");
//  str=config->readEntry("cLE");
//  config->setGroup(group);
//  if(cLE->text()!=str)
//   config->writeEntry("cLE",cLE->text());
//     else
//   config->deleteEntry("cLE");


//  config->setGroup("DefaultConfig");
//  str=config->readEntry("FLE");
//  config->setGroup(group);
//  if(FLE->lineEdit()->text()!=str)
//  {
//    config->writeEntry("FLE",FLE->lineEdit()->text());
//  }
//  else
//  {
//    config->deleteEntry("FLE");
//  }

//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-F");
//  config->setGroup(group);
//  if(FCB->isChecked()!=setFlag)
//  {
//    config->writeEntry("-F",FCB->isChecked());
//  }
//  else
//  {
//    config->deleteEntry("-F");
//  }


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-4");
//  config->setGroup(group);
//  if(IPV4CB->isChecked()!=setFlag)
//   config->writeEntry("-4",IPV4CB->isChecked());
//     else
//   config->deleteEntry("-4");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-6");
//  config->setGroup(group);
//  if(IPV6CB->isChecked()!=setFlag)
//   config->writeEntry("-6",IPV6CB->isChecked());
//     else
//   config->deleteEntry("-6");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-b");
//  config->setGroup(group);
//  if(bCB->isChecked()!=setFlag)
//   config->writeEntry("-b",bCB->isChecked());
//     else
//   config->deleteEntry("-b");

//  config->setGroup("DefaultConfig");
//  str=config->readEntry("bLE");
//  config->setGroup(group);
//  if(bLE->text()!=str)
//   config->writeEntry("bLE",bLE->text());
//     else
//   config->deleteEntry("bLE");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-c1");
//  config->setGroup(group);
//  if(c1CB->isChecked()!=setFlag)
//  {
//    config->writeEntry("-c1",c1CB->isChecked());
//  }
//  else
//  {
//    config->deleteEntry("-c1");
//  }


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-e");
//  config->setGroup(group);
//  if(eCB->isChecked()!=setFlag)
//   config->writeEntry("-e",eCB->isChecked());
//     else
//   config->deleteEntry("-e");

//  config->setGroup("DefaultConfig");
//  str=config->readEntry("eLE");
//  config->setGroup(group);
//  if(eLE->text()!=str)
//   config->writeEntry("eLE",eLE->text());
//     else
//   config->deleteEntry("eLE");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-f");
//  config->setGroup(group);
//  if(fCB->isChecked()!=setFlag)
//   config->writeEntry("-f",fCB->isChecked());
//     else
//   config->deleteEntry("-f");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-g");
//  config->setGroup(group);
//  if(gCB->isChecked()!=setFlag)
//   config->writeEntry("-g",gCB->isChecked());
//     else
//   config->deleteEntry("-g");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-i");
//  config->setGroup(group);
//  if(iCB->isChecked()!=setFlag)
//   {
//     config->writeEntry("-i",iCB->isChecked());
//    }   else
//   {
//     config->deleteEntry("-i");
// }

//  config->setGroup("DefaultConfig");
//  str=config->readEntry("iLE");
//  config->setGroup(group);
//  if(iLE->lineEdit()->text()!=str)
//   {
//     config->writeEntry("iLE",iLE->lineEdit()->text());
//    }   else
//   {
//     config->deleteEntry("iLE");
// }

//  config->setGroup("DefaultConfig");
//  str=config->readEntry("ILE1");
//  config->setGroup(group);
//  if(ILE->lineEdit()->text()!=str)
//   {
//     config->writeEntry("ILE1",ILE->lineEdit()->text());
//    }   else
//   {
//     config->deleteEntry("ILE1");
// }


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-I");
//  config->setGroup(group);
//  if(ICB->isChecked()!=setFlag)
//   {
//     config->writeEntry("-I",ICB->isChecked());
//   }
//     else
//     {
//       config->deleteEntry("-I");
//     }

//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-k");
//  config->setGroup(group);
//  if(kCB->isChecked()!=setFlag)
//   config->writeEntry("-k",kCB->isChecked());
//     else
//   config->deleteEntry("-k");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-m");
//  config->setGroup(group);
//  if(mCB->isChecked()!=setFlag)
//  {
//    config->writeEntry("-m",mCB->isChecked());
//  }
//  else
//  {
//    config->deleteEntry("-m");
//  }

//  config->setGroup("DefaultConfig");
//  str=config->readEntry("mLE");
//  config->setGroup(group);
//  if(mLE->text()!=str)
//   {
//     config->writeEntry("mLE",mLE->text());
//    }   else
//   {
//     config->deleteEntry("mLE");
// }


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-n");
//  config->setGroup(group);
//  if(nCB->isChecked()!=setFlag)
//   config->writeEntry("-n",nCB->isChecked());
//     else
//   config->deleteEntry("-n");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-N");
//  config->setGroup(group);
//  if(NCB->isChecked()!=setFlag)
//   config->writeEntry("-N",NCB->isChecked());
//     else
//   config->deleteEntry("-N");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-q");
//  config->setGroup(group);
//  if(qCB->isChecked()!=setFlag)
//   config->writeEntry("-q",qCB->isChecked());
//     else
//   config->deleteEntry("-q");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-v");
//  config->setGroup(group);
//  if(vCB->isChecked()!=setFlag)
//  {
//    config->writeEntry("-v",vCB->isChecked());
//    config->writeEntry("VerboseLevel",vSB->value());
//  }
//  else
//  {
//    config->deleteEntry("-v");
//    config->deleteEntry("VerboseLevel");
//  }

//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-s");
//  config->setGroup(group);
//  if(sCB->isChecked()!=setFlag)
//   config->writeEntry("-s",sCB->isChecked());
//     else
//   config->deleteEntry("-s");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-T");
//  config->setGroup(group);
//  if(TCB->isChecked()!=setFlag)
//   config->writeEntry("-T",TCB->isChecked());
//     else
//   config->deleteEntry("-T");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-t");
//  config->setGroup(group);
//  if(tCB->isChecked()!=setFlag)
//   config->writeEntry("-t",tCB->isChecked());
//     else
//   config->deleteEntry("-t");


//  config->setGroup("DefaultConfig");
//  setFlag=config->readBoolEntry("-o");
//  config->setGroup(group);
//  if(oCB->isChecked()!=setFlag)
//  {
//    config->writeEntry("-o",oCB->isChecked());
//  } else
//  {
//    config->deleteEntry("-o");
//  }

//  config->setGroup("DefaultConfig");
//  str=config->readEntry("oLE");
//  config->setGroup(group);
//  if(oLE->text()!=str)
//   {
//     config->writeEntry("oLE",oLE->text());
//    }   else
//   {
//     config->deleteEntry("oLE");
// }

//  config->setGroup("DefaultConfig");
//  QString c=config->readEntry("Command");
//  config->setGroup(group);
//  if(commandLE->text()!=c)
//  config->writeEntry("Command",commandLE->text());
//  else
//  config->deleteEntry("Command");

}


bool QtSSHUi::loadOptions(QString group)
{

    return false;
// bool setFlag;
// bool ret=false;
// config->setGroup(group);
/*
x  config->writeEntry("Port",portSB->value());
  config->writeEntry("VerboseLevel",vSB->value());
  config->writeEntry("Cipher",ccCB->currentItem());

x  config->writeEntry("LLE",LLE->text());
x  config->writeEntry("FLE",FLE->text());
  config->writeEntry("RLE",RLE->text());
  config->writeEntry("cLE",cLE->text());
  config->writeEntry("iLE",iLE->text());
  config->writeEntry("ILE1",ILE->lineEdit()->text());
  config->writeEntry("mLE",mLE->text());
  config->writeEntry("oLE",oLE->text());
  config->writeEntry("Command",commandLE->text());
*/

//if(config->hasKey("VerboseLevel"))
//{
//     int ite=config->readNumEntry("VerboseLevel");
//     if(vSB->value()!=ite)ret=true;
//     vSB->setValue(ite);
//}

//if(config->hasKey("Cipher"))
//{
//     int ite=config->readNumEntry("Cipher");
//     if(ccCB->currentItem()!=ite)ret=true;
//     ccCB->setCurrentItem(ite);
//}

//if(config->hasKey("Command"))
//{
//     QString Lstr=config->readEntry("Command");
//     if(commandLE->text()!=Lstr)ret=true;
//     commandLE->setText(Lstr);
//}

//if(config->hasKey("eLE"))
//{
//     QString Lstr=config->readEntry("eLE");
//     if(eLE->text()!=Lstr)ret=true;
//     eLE->setText(Lstr);
//}

//if(config->hasKey("oLE"))
//{
//     QString Lstr=config->readEntry("oLE");
//     if(oLE->text()!=Lstr)ret=true;
//     oLE->setText(Lstr);
//}

//if(config->hasKey("bLE"))
//{
//     QString Lstr=config->readEntry("bLE");
//     if(bLE->text()!=Lstr)ret=true;
//     bLE->setText(Lstr);
//}

//if(config->hasKey("mLE"))
//{
//     QString Lstr=config->readEntry("mLE");
//     if(mLE->text()!=Lstr)ret=true;
//     mLE->setText(Lstr);
//}

//if(config->hasKey("ILE1"))
//{
//     QString Lstr=config->readEntry("ILE1");
//     if(ILE->lineEdit()->text()!=Lstr)ret=true;
//     ILE->lineEdit()->setText(Lstr);
//}

//if(config->hasKey("iLE"))
//{
//     QString Lstr=config->readEntry("iLE");
//     if(iLE->lineEdit()->text()!=Lstr)ret=true;
//     iLE->lineEdit()->setText(Lstr);
//}

//if(config->hasKey("cLE"))
//{
//     QString Lstr=config->readEntry("cLE");
//     if(cLE->text()!=Lstr)ret=true;
//     cLE->setText(Lstr);
//}

//if(config->hasKey("FLE"))
//{
//     QString Lstr=config->readEntry("FLE");
//     if(FLE->lineEdit()->text()!=Lstr)ret=true;
//     FLE->lineEdit()->setText(Lstr);
//}
//if(config->hasKey("RLE"))
//{
//     QString Lstr=config->readEntry("RLE");
//     if(RLE->text()!=Lstr)ret=true;
//     RLE->setText(Lstr);
//}

//if(config->hasKey("-X"))
// {
//    setFlag=config->readBoolEntry("-X");
//    if(XCB->isChecked()!=setFlag) ret=true;
//     XCB->setChecked(setFlag);
// }
//if(config->hasKey("-x"))
// {
//    setFlag=config->readBoolEntry("-x");
//    if(xCB->isChecked()!=setFlag) ret=true;
//     xCB->setChecked(setFlag);
// }
//if(config->hasKey("-p"))
// {
//    setFlag=config->readBoolEntry("-p");
//    if(pCB->isChecked()!=setFlag) ret=true;
//     pCB->setChecked(setFlag);

// }

//if(config->hasKey("Port"))
// {
//     int v=config->readNumEntry("Port");
//    if(portSB->value()!=v) ret=true;
//     portSB->setValue(v);

// }

//if(config->hasKey("-L"))
// {
//    setFlag=config->readBoolEntry("-L");
//     if(LCB->isChecked()!=setFlag) ret=true;
//     LCB->setChecked(setFlag);

//}
//if(config->hasKey("LLE"))
//{
//     QString Lstr=config->readEntry("LLE");
//     if(LLE->text()!=Lstr)ret=true;
//     LLE->setText(Lstr);
//}
//if(config->hasKey("-R"))
// {
//    setFlag=config->readBoolEntry("-R");
//    if(RCB->isChecked()!=setFlag) ret=true;
//     RCB->setChecked(setFlag);
// }
//if(config->hasKey("-P"))
// {
//    setFlag=config->readBoolEntry("-P");
//    if(PCB->isChecked()!=setFlag) ret=true;
//     PCB->setChecked(setFlag);
// }
//if(config->hasKey("-1"))
// {
//    setFlag=config->readBoolEntry("-1");
//    if(ssh1CB->isChecked()!=setFlag) ret=true;
//     ssh1CB->setChecked(setFlag);
// }
//if(config->hasKey("-2"))
// {
//    setFlag=config->readBoolEntry("-2");
//    if(ssh2CB->isChecked()!=setFlag) ret=true;
//     ssh2CB->setChecked(setFlag);
// }
//if(config->hasKey("-a"))
// {
//    setFlag=config->readBoolEntry("-a");
//    if(aCB->isChecked()!=setFlag) ret=true;
//     aCB->setChecked(setFlag);
// }
//if(config->hasKey("-A"))
// {
//    setFlag=config->readBoolEntry("-A");
//    if(ACB->isChecked()!=setFlag) ret=true;
//     ACB->setChecked(setFlag);
// }
//if(config->hasKey("-c"))
// {
//    setFlag=config->readBoolEntry("-c");
//    if(cCB->isChecked()!=setFlag) ret=true;
//     cCB->setChecked(setFlag);
// }
//if(config->hasKey("-C"))
// {
//    setFlag=config->readBoolEntry("-C");
//    if(CCB->isChecked()!=setFlag) ret=true;
//     CCB->setChecked(setFlag);
// }
//if(config->hasKey("-F"))
// {
//    setFlag=config->readBoolEntry("-F");
//    if(FCB->isChecked()!=setFlag) ret=true;
//     FCB->setChecked(setFlag);
// }
//if(config->hasKey("-4"))
// {
//    setFlag=config->readBoolEntry("-4");
//    if(IPV4CB->isChecked()!=setFlag) ret=true;
//     IPV4CB->setChecked(setFlag);
// }
//if(config->hasKey("-6"))
// {
//    setFlag=config->readBoolEntry("-6");
//    if(IPV6CB->isChecked()!=setFlag) ret=true;
//     IPV6CB->setChecked(setFlag);
// }
//if(config->hasKey("-b"))
// {
//    setFlag=config->readBoolEntry("-b");
//    if(bCB->isChecked()!=setFlag) ret=true;
//     bCB->setChecked(setFlag);
// }
//if(config->hasKey("-c1"))
// {
//    setFlag=config->readBoolEntry("-c1");
//    if(c1CB->isChecked()!=setFlag) ret=true;
//     c1CB->setChecked(setFlag);
// }
//if(config->hasKey("-e"))
// {
//    setFlag=config->readBoolEntry("-e");
//    if(eCB->isChecked()!=setFlag) ret=true;
//     eCB->setChecked(setFlag);
// }
//if(config->hasKey("-f"))
// {
//    setFlag=config->readBoolEntry("-f");
//    if(fCB->isChecked()!=setFlag) ret=true;
//     fCB->setChecked(setFlag);
// }
//if(config->hasKey("-g"))
// {
//    setFlag=config->readBoolEntry("-g");
//    if(gCB->isChecked()!=setFlag) ret=true;
//     gCB->setChecked(setFlag);
// }
//if(config->hasKey("-i"))
// {
//    setFlag=config->readBoolEntry("-i");
//    if(iCB->isChecked()!=setFlag) ret=true;
//     iCB->setChecked(setFlag);
// }
//if(config->hasKey("-I"))
// {
//    setFlag=config->readBoolEntry("-I");
//    if(ICB->isChecked()!=setFlag) ret=true;
//     ICB->setChecked(setFlag);
// }
//if(config->hasKey("-k"))
// {
//    setFlag=config->readBoolEntry("-k");
//    if(kCB->isChecked()!=setFlag) ret=true;
//     kCB->setChecked(setFlag);
// }
//if(config->hasKey("-m"))
// {
//    setFlag=config->readBoolEntry("-m");
//    if(mCB->isChecked()!=setFlag) ret=true;
//     mCB->setChecked(setFlag);
// }
//if(config->hasKey("-n"))
// {
//    setFlag=config->readBoolEntry("-n");
//    if(nCB->isChecked()!=setFlag) ret=true;
//     nCB->setChecked(setFlag);
// }
//if(config->hasKey("-N"))
// {
//    setFlag=config->readBoolEntry("-N");
//    if(NCB->isChecked()!=setFlag) ret=true;
//     NCB->setChecked(setFlag);
// }
//if(config->hasKey("-q"))
// {
//    setFlag=config->readBoolEntry("-q");
//    if(qCB->isChecked()!=setFlag) ret=true;
//     qCB->setChecked(setFlag);
// }
//if(config->hasKey("-v"))
// {
//    setFlag=config->readBoolEntry("-v");
//    if(vCB->isChecked()!=setFlag) ret=true;
//     vCB->setChecked(setFlag);
// }
//if(config->hasKey("-s"))
// {
//    setFlag=config->readBoolEntry("-s");
//    if(sCB->isChecked()!=setFlag) ret=true;
//     sCB->setChecked(setFlag);
// }
//if(config->hasKey("-T"))
// {
//    setFlag=config->readBoolEntry("-T");
//    if(TCB->isChecked()!=setFlag) ret=true;
//     TCB->setChecked(setFlag);
// }
//if(config->hasKey("-t"))
// {
//    setFlag=config->readBoolEntry("-t");
//    if(tCB->isChecked()!=setFlag) ret=true;
//     tCB->setChecked(setFlag);
// }

//if(config->hasKey("-o"))
// {
//    setFlag=config->readBoolEntry("-o");
//    if(oCB->isChecked()!=setFlag) ret=true;
//     oCB->setChecked(setFlag);
// }


//return ret;
}

void QtSSHUi::userFor(const QString& host)
{
    ui->cmbUserName->clear();
//  compUser->clear();

//  config->setGroup(host+"-User List");

//  hosts=config->readListEntry("User");
//  compUser->setItems(hosts);
//  userCB->insertStringList(hosts);

/*

 QString userString("User%1");
 QString tmpUser;
 unsigned int un,i;

  userCB->clear();
  compUser->clear();
  config->setGroup(host+"-User List");
  un=config->readNumEntry("NumUser",0);
  for(i=0;i<un;i++)
   {
      tmpUser = config->readEntry(userString.arg(i+1));
      warning(tmpUser);
      userCB->insertItem(tmpUser);
    //  compUser->addItem(tmpUser);
      userCB->completionObject()->addItem(tmpUser);
}
*/

//  userCB->setEditText(config->readEntry("LastUsed",""));


// loadOptions("DefaultConfig");

// if(loadOptions(host+"-Options"))
//  {
// QFont tmpFont=optionsPB->font();
// tmpFont.setItalic(true);
// optionsPB->setFont(tmpFont);
// }
//else
//  {
// QFont tmpFont=optionsPB->font();
// tmpFont.setItalic(false);
// optionsPB->setFont(tmpFont);
// }

}

void QtSSHUi::hostEditor()
{
    ui->listUserHostEditor->clear();

    ui->grbOptions->hide();
    ui->frmHostUser->setTitle(tr("Hosts: "));
    ui->frmHostUser->show ();

// userHostELB->clear();

    ui->cmbHosts->itemData()

    ui->listUserHostEditor->insertItem(0, "192.168.1.111");
    ui->listUserHostEditor->insertItem(1, "192.168.1.112");
    ui->listUserHostEditor->insertItem(2, "192.168.1.113");

    m_editor_is_user_mode = false;
    m_editor_is_hosts_mode = true;

   //ui->listUserHostEditor->setTitle(i18n("Hosts:"));
// userHostELB->insertStringList(compHost->items());
}


void QtSSHUi::userEditor()
{
    ui->listUserHostEditor->clear();
    ui->grbOptions->hide();
    ui->frmHostUser->setTitle(tr("User list for %1:").arg(ui->cmbHosts->currentText()));
    ui->frmHostUser->show ();

    m_editor_is_user_mode = true;
    m_editor_is_hosts_mode = false;

// QString host=hostCB->currentText();
//  userHostELB->setTitle(i18n("User list for %1:").arg(ui->cmbHosts->itemText(ui->cmbHosts->currentIndex())));
// userHostELB->insertStringList(compUser->items());
}

void QtSSHUi::currentItemChanged(QListWidgetItem* item)
{
    if (item)  {
        QString text = item->data(Qt::EditRole).toString();
        if (text.length()==0)  {
            item->setData(Qt::EditRole, m_item_text);
            m_item_text.clear();
        }
    }
}

void QtSSHUi::deleteCurrent()
{
    int currentItem = ui->listUserHostEditor->currentRow();
    if (currentItem!=-1)  {
        delete ui->listUserHostEditor->item(currentItem);
    }
}

void QtSSHUi::editCurrent()
{
    QListWidgetItem *item = ui->listUserHostEditor->currentItem();
    if (item)  {
        m_item_text = item->data(Qt::EditRole).toString();
        item->setFlags( item->flags() | Qt::ItemIsEditable );
        ui->listUserHostEditor->editItem( item );
    }
}

void QtSSHUi::insertNewItem()
{
    int currentItem = ui->listUserHostEditor->currentRow();
    QListWidgetItem *item = NULL;
    if (m_editor_is_user_mode)  {
        item = new QListWidgetItem(tr("newuser"));
    } else if (m_editor_is_hosts_mode)  {
        item = new QListWidgetItem(tr("192.168.1.1"));
    }
    ui->listUserHostEditor->insertItem(currentItem, item);
    ui->listUserHostEditor->setCurrentItem(item);
    editCurrent();
}

bool QtSSHUi::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->listUserHostEditor && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Insert) {
            insertNewItem ();
            return true;
        } else if (keyEvent->key() == Qt::Key_Delete)  {
            deleteCurrent ();
            return true;
        } else if (keyEvent->key() == Qt::Key_F2)  {
            editCurrent ();
            return true;
        } else
            return false;
    }
    return false;
}

void QtSSHUi::okEditor()
{
    ui->frmHostUser->hide();
    QList<QListWidgetItem *> items =
          ui->listUserHostEditor->findItems(QString("*"),
          Qt::MatchWrap | Qt::MatchWildcard);

    QList<QString> list;
    foreach(QListWidgetItem *item, items)
        list.append(item->text());

    if(m_editor_is_user_mode)     {
        ui->cmbUserName->clear();
        ui->cmbUserName->insertItems(0,list);
    }
    if(m_editor_is_hosts_mode)  {
        ui->cmbHosts->clear();
        ui->cmbHosts->insertItems(0,list);
    }
    ui->listUserHostEditor->clear();
    m_editor_is_user_mode=false;
    m_editor_is_hosts_mode=false;

    // config->sync();
}

void QtSSHUi::cancelEditor()
{
     ui->frmHostUser->hide();
     ui->listUserHostEditor->clear();
     m_editor_is_user_mode = false;
     m_editor_is_hosts_mode =  false;
}
