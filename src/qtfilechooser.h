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

#ifndef QTFILECHOOSER
#define QTFILECHOOSER

#include <QLineEdit>
#include <QResizeEvent>
#ifdef _DESIGNER_EXPORT
#include <QDesignerExportWidget>
#else
#define QDESIGNER_WIDGET_EXPORT
#endif

class QPushButton;

class QDESIGNER_WIDGET_EXPORT QtFileChooser : public QWidget
{
    Q_OBJECT

    Q_ENUMS( Mode )
    Q_PROPERTY( Mode mode READ mode WRITE setMode )
    Q_PROPERTY( QString fileName READ fileName WRITE setFileName )

public:
    QtFileChooser (QWidget* p=0);

    enum Mode { File, Directory };
    QString fileName() const;
    Mode mode() const;

public slots:
    void setFileName( const QString &fn );
    void setMode( Mode m );

private slots:
    void chooseFile();

signals:
    void fileNameChanged( const QString & );

private:
    QLineEdit *m_lineEdit;
    QPushButton*  m_button;
    Mode md;
};

#endif // QTFILECHOOSER
