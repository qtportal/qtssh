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

#include <QHBoxLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QToolButton>
#include <QStyle>
#include "qtfilechooser.h"

// http://www.kde.gr.jp/~ichi/qt/designer-manual-6.html

QtFileChooser::QtFileChooser (QWidget *p) : QWidget(p)
{
    QHBoxLayout *layout = new QHBoxLayout( this );
    layout->setMargin( 0 );

    m_lineEdit = new QLineEdit( this );
    layout->addWidget( m_lineEdit );

    connect( m_lineEdit, SIGNAL( textChanged( const QString & ) ),
             this, SIGNAL( fileNameChanged( const QString & ) ) );

    m_button = new QPushButton( "...", this );
    m_button->setFixedWidth( m_button->fontMetrics().width( " ... " ) );
    layout->addWidget( m_button );

    connect( m_button, SIGNAL( clicked() ),
             this, SLOT( chooseFile() ) );

    setFocusProxy( m_lineEdit );
}

void QtFileChooser::setFileName( const QString &fn )
{
    m_lineEdit->setText( fn );
}

QString QtFileChooser::fileName() const
{
    return m_lineEdit->text();
}

void QtFileChooser::setMode(Mode m)
{
    md = m;
}

QtFileChooser::Mode QtFileChooser::mode () const
{
    return md;
}

void QtFileChooser::chooseFile ()
{
    QString fn;
    if ( mode() == File )
        fn = QFileDialog::getOpenFileName(this, m_lineEdit->text(), QString::null) ;
    else
        fn = QFileDialog::getExistingDirectory(this,  m_lineEdit->text());

    if ( !fn.isEmpty() ) {
        m_lineEdit->setText( fn );
        emit fileNameChanged( fn );
    }
}
