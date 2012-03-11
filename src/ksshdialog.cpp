
/****************************************************************************
** Form implementation generated from reading ui file './ksshdialog.ui'
**
** Created: sab apr 27 10:19:35 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "ui_qtsshdialog.h"

//#include <keditlistbox.h>
//#include <kurlrequester.h>
#include <QLineEdit>
#include <QVariant>
#include <QComboBox>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a KSSHDialog which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
KSSHDialog::KSSHDialog( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "KSSHDialog" );
    resize( 612, 786 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setCaption( tr2i18n( "kssh" ) );
    KSSHDialogLayout = new QGridLayout( this, 1, 1, 5, 6, "KSSHDialogLayout"); 

    optionsGB = new QGroupBox( this, "optionsGB" );
    optionsGB->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, optionsGB->sizePolicy().hasHeightForWidth() ) );
    optionsGB->setTitle( tr2i18n( "SSH options:" ) );
    optionsGB->setColumnLayout(0, Qt::Vertical );
    optionsGB->layout()->setSpacing( 6 );
    optionsGB->layout()->setMargin( 2 );
    optionsGBLayout = new QGridLayout( optionsGB->layout() );
    optionsGBLayout->setAlignment( Qt::AlignTop );

    PCB = new QCheckBox( optionsGB, "PCB" );
    PCB->setText( tr2i18n( "non privileged port (-P)" ) );
    QWhatsThis::add( PCB, tr2i18n( "<qt><b> -P</b><br>      Use a non-privileged port for outgoing connections.  This can be used if a firewall does not permit connections from privileged\n"
" ports.  Note that this option turns off <i>RhostsAuthentication</i> and\n"
"<i>RhostsRSAAuthentication</i> for older servers.</qt>" ) );

    optionsGBLayout->addWidget( PCB, 4, 0 );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    pCB = new QCheckBox( optionsGB, "pCB" );
    pCB->setText( tr2i18n( "Specifiy port (-p nn):" ) );
    QWhatsThis::add( pCB, tr2i18n( "<qt><b> -p port</b><br>\n"
" Port to connect to on the remote host.  This can be specified on  a per-host basis in the configuration file.</qt>" ) );
    Layout1->addWidget( pCB );

    portSB = new QSpinBox( optionsGB, "portSB" );
    portSB->setEnabled( FALSE );
    portSB->setMaxValue( 65535 );
    portSB->setMinValue( 1 );
    portSB->setValue( 22 );
    QWhatsThis::add( portSB, tr2i18n( "<qt><b> -p port</b><br>\n"
" Port to connect to on the remote host.  This can be specified on  a per-host basis in the configuration file.</qt>" ) );
    Layout1->addWidget( portSB );

    optionsGBLayout->addMultiCellLayout( Layout1, 1, 1, 0, 1 );

    Layout2 = new QHBoxLayout( 0, 0, 6, "Layout2"); 

    LCB = new QCheckBox( optionsGB, "LCB" );
    LCB->setText( tr2i18n( "Forward local (-L p:h:p):" ) );
    QWhatsThis::add( LCB, tr2i18n( "<qt><b>-L port:host:hostport</b><br>\n"
"Specifies that the given port on the local (client) host is to be\n"
"forwarded to the given host and port on the remote side.  This\n"
"works by allocating a socket to listen to port on the local side,\n"
"and whenever a connection is made to this port, the connection is\n"
"forwarded over the secure channel, and a connection is made to\n"
"host port hostport from the remote machine.  Port forwardings can\n"
"also be specified in the configuration file.  Only root can for­\n"
"ward privileged ports.  IPv6 addresses can be specified with an\n"
"alternative syntax: port/host/hostport</qt>" ) );
    Layout2->addWidget( LCB );

    LLE = new QLineEdit( optionsGB, "LLE" );
    QWhatsThis::add( LLE, tr2i18n( "<qt><b>-L port:host:hostport</b><br>\n"
"Specifies that the given port on the local (client) host is to be\n"
"forwarded to the given host and port on the remote side.  This\n"
"works by allocating a socket to listen to port on the local side,\n"
"and whenever a connection is made to this port, the connection is\n"
"forwarded over the secure channel, and a connection is made to\n"
"host port hostport from the remote machine.  Port forwardings can\n"
"also be specified in the configuration file.  Only root can for­\n"
"ward privileged ports.  IPv6 addresses can be specified with an\n"
"alternative syntax: port/host/hostport</qt>" ) );
    Layout2->addWidget( LLE );

    optionsGBLayout->addMultiCellLayout( Layout2, 2, 2, 0, 1 );

    Layout3 = new QHBoxLayout( 0, 0, 6, "Layout3"); 

    RCB = new QCheckBox( optionsGB, "RCB" );
    RCB->setText( tr2i18n( "Forward Remote (-R p:h:p):" ) );
    QWhatsThis::add( RCB, tr2i18n( "<qt><b>-R port:host:hostport</b><br>\n"
"Specifies that the given port on the remote (server) host is to\n"
"be forwarded to the given host and port on the local side.  This\n"
"works by allocating a socket to listen to port on the remote\n"
"side, and whenever a connection is made to this port, the connection is forwarded over the secure channel, and a connection is made to host port hostport from the local machine.  Port forward­ings can also be specified in the configuration file.  Privileged ports can be forwarded only when logging in as root on the remote      machine.  IPv6 addresses can be specified with an alternative            syntax: port/host/hostport</qt>" ) );
    Layout3->addWidget( RCB );

    RLE = new QLineEdit( optionsGB, "RLE" );
    QWhatsThis::add( RLE, tr2i18n( "<qt><b>-R port:host:hostport</b><br>\n"
"Specifies that the given port on the remote (server) host is to\n"
"be forwarded to the given host and port on the local side.  This\n"
"works by allocating a socket to listen to port on the remote\n"
"side, and whenever a connection is made to this port, the connection is forwarded over the secure channel, and a connection is made to host port hostport from the local machine.  Port forward­ings can also be specified in the configuration file.  Privileged ports can be forwarded only when logging in as root on the remote      machine.  IPv6 addresses can be specified with an alternative            syntax: port/host/hostport</qt>" ) );
    Layout3->addWidget( RLE );

    optionsGBLayout->addMultiCellLayout( Layout3, 3, 3, 0, 1 );

    Layout4 = new QHBoxLayout( 0, 0, 6, "Layout4"); 

    ssh1CB = new QCheckBox( optionsGB, "ssh1CB" );
    ssh1CB->setText( tr2i18n( "Try to use ssh1 (-1) " ) );
    QWhatsThis::add( ssh1CB, tr2i18n( "<qt><b>-1</b><br>      Forces ssh to try protocol version 1 only.</qt>" ) );
    Layout4->addWidget( ssh1CB );

    ssh2CB = new QCheckBox( optionsGB, "ssh2CB" );
    ssh2CB->setText( tr2i18n( "Try to use ssh2 (-2) " ) );
    QWhatsThis::add( ssh2CB, tr2i18n( "<qt><b>-2</b><br>      Forces ssh to try protocol version 2 only.</qt>" ) );
    Layout4->addWidget( ssh2CB );

    optionsGBLayout->addMultiCellLayout( Layout4, 5, 5, 0, 1 );

    Layout7 = new QHBoxLayout( 0, 0, 6, "Layout7"); 

    XCB = new QCheckBox( optionsGB, "XCB" );
    XCB->setText( tr2i18n( "Enable X11 (-X)" ) );
    QWhatsThis::add( XCB, tr2i18n( "<qt><b>-X</b><br> Enables X11 forwarding.  This can also be specified on a per-host basis in a configuration file.</qt>" ) );
    Layout7->addWidget( XCB );

    xCB = new QCheckBox( optionsGB, "xCB" );
    xCB->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, xCB->sizePolicy().hasHeightForWidth() ) );
    xCB->setText( tr2i18n( "Disable X11 (-x)" ) );
    QWhatsThis::add( xCB, tr2i18n( "<qt><b>  -x</b><br>      Disables X11 forwarding.</qt>" ) );
    Layout7->addWidget( xCB );

    optionsGBLayout->addMultiCellLayout( Layout7, 0, 0, 0, 1 );

    Layout6 = new QHBoxLayout( 0, 0, 6, "Layout6"); 

    cCB = new QCheckBox( optionsGB, "cCB" );
    cCB->setText( tr2i18n( "Cipher to use (-c cipher):" ) );
    QWhatsThis::add( cCB, tr2i18n( "<qt><b>-c blowfish|3des|des</b><br>        Selects the cipher to use for encrypting the session.  3des is used by default.  It is believed to be secure.  3des (triple-des) is an encrypt-decrypt-encrypt triple with three different keys. blowfish is a fast block cipher, it appears very secure and is much faster than 3des.  des is only supported in the ssh client for interoperability with legacy protocol 1 implementations that\n"
"do not support the 3des cipher.  Its use is strongly discouraged\n"
"due to cryptographic weaknesses.</qt>" ) );
    Layout6->addWidget( cCB );

    ccCB = new QComboBox( FALSE, optionsGB, "ccCB" );
    ccCB->insertItem( tr2i18n( "3des" ) );
    ccCB->insertItem( tr2i18n( "blowfish" ) );
    ccCB->insertItem( tr2i18n( "des" ) );
    ccCB->setEnabled( FALSE );
    Layout6->addWidget( ccCB );

    optionsGBLayout->addMultiCellLayout( Layout6, 8, 8, 0, 1 );

    CCB = new QCheckBox( optionsGB, "CCB" );
    CCB->setText( tr2i18n( "Compression of all data (-C)" ) );
    QWhatsThis::add( CCB, tr2i18n( "<qt><b> -C</b><br>      Requests compression of all data (including stdin, stdout,\n"
"stderr, and data for forwarded X11 and TCP/IP connections).  The\n"
"compression algorithm is the same used by gzip, and the\n"
"``level'' can be controlled by the CompressionLevel option (see\n"
"man:/ssh).  Compression is desirable on modem lines and other slow\n"
"connections, but will only slow down things on fast networks. The default value can be set on a host-by-host basis in the configuration files; see the Compression option in man:/ssh." ) );

    optionsGBLayout->addMultiCellWidget( CCB, 9, 9, 0, 1 );

    Layout9 = new QHBoxLayout( 0, 0, 6, "Layout9"); 

    savePB = new QPushButton( optionsGB, "savePB" );
    savePB->setText( tr2i18n( "Save as default configuration" ) );
    Layout9->addWidget( savePB );

    morePB = new QPushButton( optionsGB, "morePB" );
    morePB->setText( tr2i18n( "More..." ) );
    Layout9->addWidget( morePB );

    optionsGBLayout->addMultiCellLayout( Layout9, 16, 16, 0, 1 );

    saveCB = new QCheckBox( optionsGB, "saveCB" );
    saveCB->setText( tr2i18n( "Save this connection" ) );
    saveCB->setChecked( TRUE );

    optionsGBLayout->addWidget( saveCB, 15, 0 );

    aboutPB = new QPushButton( optionsGB, "aboutPB" );
    aboutPB->setText( tr2i18n( "About kssh..." ) );

    optionsGBLayout->addWidget( aboutPB, 15, 1 );

    Line1 = new QFrame( optionsGB, "Line1" );
    Line1->setProperty( "frameShape", (int)QFrame::HLine );
    Line1->setFrameShadow( QFrame::Sunken );
    Line1->setFrameShape( QFrame::HLine );

    optionsGBLayout->addMultiCellWidget( Line1, 14, 14, 0, 1 );

    commandLE = new KLineEdit( optionsGB, "commandLE" );
    commandLE->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, commandLE->sizePolicy().hasHeightForWidth() ) );

    optionsGBLayout->addMultiCellWidget( commandLE, 13, 13, 0, 1 );

    TextLabel3 = new QLabel( optionsGB, "TextLabel3" );
    TextLabel3->setText( tr2i18n( "Execute command:" ) );

    optionsGBLayout->addWidget( TextLabel3, 12, 0 );

    Layout20 = new QHBoxLayout( 0, 0, 6, "Layout20"); 

    IPV4CB = new QCheckBox( optionsGB, "IPV4CB" );
    IPV4CB->setText( tr2i18n( "Force IPv4 (-4)" ) );
    QWhatsThis::add( IPV4CB, tr2i18n( "<qt><b> -4</b><br>  Forces ssh to use IPv4 addresses only.</qt>" ) );
    Layout20->addWidget( IPV4CB );

    IPV6CB = new QCheckBox( optionsGB, "IPV6CB" );
    IPV6CB->setText( tr2i18n( "Force IPv6 (-6)" ) );
    QWhatsThis::add( IPV6CB, tr2i18n( "<qt><b> -6</b><br>  Forces ssh to use IPv6 addresses only.</qt>" ) );
    Layout20->addWidget( IPV6CB );

    optionsGBLayout->addMultiCellLayout( Layout20, 11, 11, 0, 1 );

    aCB = new QCheckBox( optionsGB, "aCB" );
    aCB->setText( tr2i18n( "Disable auth agent forwarding (-a)" ) );
    QWhatsThis::add( aCB, tr2i18n( "<qt><b>-a</b><br>      Disables forwarding of the authentication agent connection.</qt>" ) );

    optionsGBLayout->addMultiCellWidget( aCB, 6, 6, 0, 1 );

    Layout24 = new QHBoxLayout( 0, 0, 6, "Layout24"); 

    FCB = new QCheckBox( optionsGB, "FCB" );
    FCB->setText( tr2i18n( "Config file (-F):" ) );
    QWhatsThis::add( FCB, tr2i18n( "<qt><b> -F configfile</b><br>     Specifies an alternative per-user configuration file.  If a configuration file is given on the command line, the system-wide\n"
"configuration file (/etc/ssh/ssh_config) will be ignored.  The\n"
"default for the per-user configuration file is $HOME/.ssh/config.</qt>" ) );
    Layout24->addWidget( FCB );

    FLE = new KURLRequester( optionsGB, "FLE" );
    Layout24->addWidget( FLE );

    optionsGBLayout->addMultiCellLayout( Layout24, 10, 10, 0, 1 );

    moreF = new QFrame( optionsGB, "moreF" );
    moreF->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)7, 0, 0, moreF->sizePolicy().hasHeightForWidth() ) );
    moreF->setFrameShape( QFrame::NoFrame );
    moreF->setFrameShadow( QFrame::Plain );
    moreFLayout = new QGridLayout( moreF, 1, 1, 0, 6, "moreFLayout"); 

    Layout5 = new QHBoxLayout( 0, 0, 6, "Layout5"); 

    bCB = new QCheckBox( moreF, "bCB" );
    bCB->setText( tr2i18n( "Bind address (-b address):" ) );
    QWhatsThis::add( bCB, tr2i18n( "<qt><b>-b bind_address</b> <br>Specify the interface to transmit from on machines with multiple interfaces or aliased addresses.</qt>" ) );
    Layout5->addWidget( bCB );

    bLE = new QLineEdit( moreF, "bLE" );
    QWhatsThis::add( bLE, tr2i18n( "<qt><b>-b bind_address</b> <br>Specify the interface to transmit from on machines with multiple interfaces or aliased addresses.</qt>" ) );
    Layout5->addWidget( bLE );

    moreFLayout->addLayout( Layout5, 0, 0 );

    layyyy = new QHBoxLayout( 0, 0, 6, "layyyy"); 

    c1CB = new QCheckBox( moreF, "c1CB" );
    c1CB->setText( tr2i18n( "Cipher to use (-c list):" ) );
    QWhatsThis::add( c1CB, tr2i18n( "<qt><b>-c cipher_spec</b><br>   Additionally, for protocol version 2 a comma-separated list of ciphers can be specified in order of preference. See man:/ssh, Ciphers dor more info.</qt>" ) );
    layyyy->addWidget( c1CB );

    cLE = new QLineEdit( moreF, "cLE" );
    QWhatsThis::add( cLE, tr2i18n( "<qt><b>-c cipher_spec</b><br>   Additionally, for protocol version 2 a comma-separated list of ciphers can be specified in order of preference. See man:/ssh, Ciphers dor more info.</qt>" ) );
    layyyy->addWidget( cLE );

    moreFLayout->addLayout( layyyy, 1, 0 );

    Layout12 = new QHBoxLayout( 0, 0, 6, "Layout12"); 

    eCB = new QCheckBox( moreF, "eCB" );
    eCB->setText( tr2i18n( "Escape character (-e):" ) );
    QWhatsThis::add( eCB, tr2i18n( "<qt><b> -e ch|^ch|none  </b> <br>   Sets the escape character for sessions with a pty (default: `~').The escape character is only recognized at the beginning of a line.  The escape character followed by a dot (`.') closes the connection, followed by control-Z suspends the connection, and followed by itself sends the escape character once.  Setting the character to ``none'' disables any escapes and makes the session fully transparent.</qt>" ) );
    Layout12->addWidget( eCB );

    eLE = new QLineEdit( moreF, "eLE" );
    QWhatsThis::add( eLE, tr2i18n( "<qt><b> -e ch|^ch|none  </b> <br>   Sets the escape character for sessions with a pty (default: `~').The escape character is only recognized at the beginning of a line.  The escape character followed by a dot (`.') closes the connection, followed by control-Z suspends the connection, and followed by itself sends the escape character once.  Setting the character to ``none'' disables any escapes and makes the session fully transparent.</qt>" ) );
    Layout12->addWidget( eLE );

    moreFLayout->addLayout( Layout12, 2, 0 );

    Layout13 = new QHBoxLayout( 0, 0, 6, "Layout13"); 

    mCB = new QCheckBox( moreF, "mCB" );
    mCB->setText( tr2i18n( "Mac spec (-m):" ) );
    QWhatsThis::add( mCB, tr2i18n( "<qt><b>-m mac_spec</b><br>Additionally, for protocol version 2 a comma-separated list of MAC (message authentication code) algorithms can be specified in  order of preference.  See <a href=\"man:/ssh\">man:/ssh</a>, MACs keyword for more information.</qt>" ) );
    Layout13->addWidget( mCB );

    mLE = new QLineEdit( moreF, "mLE" );
    QWhatsThis::add( mLE, tr2i18n( "<qt><b>-m mac_spec</b><br>Additionally, for protocol version 2 a comma-separated list of MAC (message authentication code) algorithms can be specified in  order of preference.  See <a href=\"man:/ssh\">man:/ssh</a>, MACs keyword for more information.</qt>" ) );
    Layout13->addWidget( mLE );

    moreFLayout->addLayout( Layout13, 8, 0 );

    Layout16 = new QHBoxLayout( 0, 0, 6, "Layout16"); 

    vCB = new QCheckBox( moreF, "vCB" );
    vCB->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, vCB->sizePolicy().hasHeightForWidth() ) );
    vCB->setText( tr2i18n( "Verbose (-v,-vv,-vvv):" ) );
    QWhatsThis::add( vCB, tr2i18n( " <qt><b>-v</b><br>      Verbose mode.  Causes ssh to print debugging messages about its progress.  This is helpful in debugging connection, authentica­tion, and configuration problems. Verbosity level \n"
"could be configured from 1 to 3 (3 is the maximum).</qt>" ) );
    Layout16->addWidget( vCB );

    vSB = new QSpinBox( moreF, "vSB" );
    vSB->setEnabled( FALSE );
    vSB->setMaxValue( 3 );
    vSB->setMinValue( 1 );
    QWhatsThis::add( vSB, tr2i18n( "<qt>Verbosity level. 1=minimum, 2=medium,3=maximum (It means -v,-vv,-vvv on ssh command line)</qt>" ) );
    Layout16->addWidget( vSB );

    moreFLayout->addLayout( Layout16, 12, 0 );

    Layout15 = new QHBoxLayout( 0, 0, 6, "Layout15"); 

    TCB = new QCheckBox( moreF, "TCB" );
    TCB->setText( tr2i18n( "Disbale TTY (-T)" ) );
    QWhatsThis::add( TCB, tr2i18n( "<qt><b>-T</b><br>      Disable pseudo-tty allocation.</qt>" ) );
    Layout15->addWidget( TCB );

    tCB = new QCheckBox( moreF, "tCB" );
    tCB->setText( tr2i18n( "Force TTY (-t)" ) );
    QWhatsThis::add( tCB, tr2i18n( "<qt><b>-t</b><br>Force pseudo-tty allocation.  This can be used to execute arbitrary screen-based programs on a remote machine, which can be\n"
"very useful, e.g., when implementing menu services.  Multiple -t options force tty allocation, even if ssh has no local tty.</qt>" ) );
    Layout15->addWidget( tCB );

    moreFLayout->addLayout( Layout15, 14, 0 );

    sCB = new QCheckBox( moreF, "sCB" );
    sCB->setText( tr2i18n( "Subsystem (-s)" ) );
    QWhatsThis::add( sCB, tr2i18n( "<qt><b> -s</b><br>      May be used to request invocation of a subsystem on the remote system. Subsystems are a feature of the SSH2 protocol which\n"
"facilitate the use of SSH as a secure transport for other applications (<i>eg. sftp</i>). The subsystem is specified as the remote command.</qt>" ) );

    moreFLayout->addWidget( sCB, 13, 0 );

    Layout17 = new QHBoxLayout( 0, 0, 6, "Layout17"); 

    oCB = new QCheckBox( moreF, "oCB" );
    oCB->setText( tr2i18n( "More option (-o):" ) );
    QWhatsThis::add( oCB, tr2i18n( "<qt><b>-o option</b><br>Can be used to give options in the format used in the configuration file.  This is useful for specifying options for which there is no separate command-line flag.</qt>" ) );
    Layout17->addWidget( oCB );

    oLE = new QLineEdit( moreF, "oLE" );
    QWhatsThis::add( oLE, tr2i18n( "<qt><b>-o option</b><br>Can be used to give options in the format used in the configuration file.  This is useful for specifying options for which there is no separate command-line flag.</qt>" ) );
    Layout17->addWidget( oLE );

    moreFLayout->addLayout( Layout17, 15, 0 );

    nCB = new QCheckBox( moreF, "nCB" );
    nCB->setText( tr2i18n( "Redirect stdin from /dev/null (-n)" ) );
    QWhatsThis::add( nCB, tr2i18n( "<qt><b>-n</b> <br>Redirects stdin from <tt>/dev/null</tt> (actually, prevents reading from stdin).  This must be used when ssh is run in the background.  A common trick is to use this to run X11 programs on a remote machine.  For example, ssh -n shadows.cs.hut.fi emacs & will start an emacs on shadows.cs.hut.fi, and the X11 connection will be automatically forwarded over an encrypted channel.  The ssh  program will be put in the background.  (This does not work if ssh needs to ask for a password or passphrase; see also the -f option.)</qt>" ) );

    moreFLayout->addWidget( nCB, 9, 0 );

    Layout22 = new QHBoxLayout( 0, 0, 6, "Layout22"); 

    ICB = new QCheckBox( moreF, "ICB" );
    ICB->setText( tr2i18n( "SmartCard device (-I):" ) );
    QWhatsThis::add( ICB, tr2i18n( "<qt><b>-I smartcard_device</b><br> Specifies which smartcard device to use. The argument is the device ssh should use to communicate with a smartcard used for storing the user's private RSA key.</qt>" ) );
    Layout22->addWidget( ICB );

    ILE = new KURLRequester( moreF, "ILE" );
    QWhatsThis::add( ILE, tr2i18n( "<qt><b>-I smartcard_device</b><br> Specifies which smartcard device to use. The argument is the device ssh should use to communicate with a smartcard used for storing the user's private RSA key.</qt>" ) );
    Layout22->addWidget( ILE );

    moreFLayout->addLayout( Layout22, 6, 0 );

    kCB = new QCheckBox( moreF, "kCB" );
    kCB->setText( tr2i18n( "Disable Kerberos forwarding (-k)" ) );
    QWhatsThis::add( kCB, tr2i18n( "<qt><b> -k</b><br>Disables forwarding of Kerberos tickets and AFS tokens.  This may also be specified on a per-host basis in the configuration file.</qt>" ) );

    moreFLayout->addWidget( kCB, 7, 0 );

    Layout23 = new QHBoxLayout( 0, 0, 6, "Layout23"); 

    iCB = new QCheckBox( moreF, "iCB" );
    iCB->setText( tr2i18n( "Identity file (-i):" ) );
    QWhatsThis::add( iCB, tr2i18n( "<qt><b>-i identity_file</b><br>Selects a file from which the identity (private key) for  <i>RSA</i> or <i>DSA</i> authentication is read.  The default is $HOME/.ssh/identity for protocol version 1, and $HOME/.ssh/id_rsa and $HOME/.ssh/id_dsa for protocol version 2.  Identity files may also be specified on a per-host basis in the configuration file. It is possible to have multiple -i options (and multiple identities specified in configuration files).</qt>" ) );
    Layout23->addWidget( iCB );

    iLE = new KURLRequester( moreF, "iLE" );
    QWhatsThis::add( iLE, tr2i18n( "<qt><b> -e ch|^ch|none  </b> <br>   Sets the escape character for sessions with a pty (default: `~').The escape character is only recognized at the beginning of a line.  The escape character followed by a dot (`.') closes the connection, followed by control-Z suspends the connection, and followed by itself sends the escape character once.  Setting the character to ``none'' disables any escapes and makes the session fully transparent.</qt>" ) );
    Layout23->addWidget( iLE );

    moreFLayout->addLayout( Layout23, 5, 0 );

    gCB = new QCheckBox( moreF, "gCB" );
    gCB->setText( tr2i18n( "Allow remote connection (-g)" ) );
    QWhatsThis::add( gCB, tr2i18n( "<qt><b> -g</b><br>      Allows remote hosts to connect to local forwarded ports.</qt>" ) );

    moreFLayout->addWidget( gCB, 4, 0 );

    qCB = new QCheckBox( moreF, "qCB" );
    qCB->setText( tr2i18n( "Quiet mode (-q)" ) );
    QWhatsThis::add( qCB, tr2i18n( "<qt><b> -q</b><br> Quiet mode.  Causes all warning and diagnostic messages to be suppressed.</qt>" ) );

    moreFLayout->addWidget( qCB, 11, 0 );

    NCB = new QCheckBox( moreF, "NCB" );
    NCB->setText( tr2i18n( "Do not execute command (-N)" ) );
    QWhatsThis::add( NCB, tr2i18n( "<qt><b> -N</b><br>      Do not execute a remote command.  This is useful for just forwarding ports (protocol version 2 only).</qt>" ) );

    moreFLayout->addWidget( NCB, 10, 0 );

    fCB = new QCheckBox( moreF, "fCB" );
    fCB->setText( tr2i18n( "Go in background (-f)" ) );
    QWhatsThis::add( fCB, tr2i18n( "<qt><b> -f  </b><br>    Requests ssh to go to background just before command execution. This is useful if ssh is going to ask for passwords or\n"
"passphrases, but the user wants it in the background.  This\n"
"implies -n.  The recommended way to start X11 programs at a\n"
"remote site is with something like<br> <tt>ssh -f host xterm</tt>.</qt>" ) );

    moreFLayout->addWidget( fCB, 3, 0 );

    optionsGBLayout->addMultiCellWidget( moreF, 0, 16, 2, 2 );

    ACB = new QCheckBox( optionsGB, "ACB" );
    ACB->setText( tr2i18n( "Enable auth agent forwarding (-A)" ) );
    QWhatsThis::add( ACB, tr2i18n( "<qt><b>-A</b><br>      Enables forwarding of the authentication agent connection. This can also be specified on a per-host basis in a configuration file.</qt>" ) );

    optionsGBLayout->addMultiCellWidget( ACB, 7, 7, 0, 1 );

    KSSHDialogLayout->addWidget( optionsGB, 2, 0 );

    Layout20_2 = new QHBoxLayout( 0, 0, 6, "Layout20_2"); 

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, TextLabel2->sizePolicy().hasHeightForWidth() ) );
    TextLabel2->setText( tr2i18n( "Host:" ) );
    Layout20_2->addWidget( TextLabel2 );

    hostCB = new KHistoryCombo( this, "hostCB" );
    hostCB->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, hostCB->sizePolicy().hasHeightForWidth() ) );
    hostCB->setInsertionPolicy( KHistoryCombo::AtTop );
    hostCB->setDuplicatesEnabled( FALSE );
    Layout20_2->addWidget( hostCB );

    hostTB = new QToolButton( this, "hostTB" );
    hostTB->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)1, 0, 0, hostTB->sizePolicy().hasHeightForWidth() ) );
    hostTB->setText( tr2i18n( "..." ) );
    QToolTip::add( hostTB, tr2i18n( "Edit host list" ) );
    QWhatsThis::add( hostTB, tr2i18n( "This button opens a list editor to edit the host list" ) );
    Layout20_2->addWidget( hostTB );

    KSSHDialogLayout->addLayout( Layout20_2, 0, 0 );

    Layout21 = new QHBoxLayout( 0, 0, 6, "Layout21"); 

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, TextLabel1->sizePolicy().hasHeightForWidth() ) );
    TextLabel1->setText( tr2i18n( "Username:" ) );
    Layout21->addWidget( TextLabel1 );

    userCB = new KHistoryCombo( this, "userCB" );
    userCB->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, userCB->sizePolicy().hasHeightForWidth() ) );
    userCB->setInsertionPolicy( KHistoryCombo::AtTop );
    userCB->setDuplicatesEnabled( FALSE );
    Layout21->addWidget( userCB );

    userTB = new QToolButton( this, "userTB" );
    userTB->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)1, 0, 0, userTB->sizePolicy().hasHeightForWidth() ) );
    userTB->setText( tr2i18n( "..." ) );
    QToolTip::add( userTB, tr2i18n( "Edit this host user list" ) );
    QWhatsThis::add( userTB, tr2i18n( "This button opens an editor to modify the list of users associated with the currently selected host" ) );
    Layout21->addWidget( userTB );

    KSSHDialogLayout->addLayout( Layout21, 1, 0 );

    Layout24_2 = new QHBoxLayout( 0, 0, 6, "Layout24_2"); 

    connectPB = new QPushButton( this, "connectPB" );
    connectPB->setText( tr2i18n( "Connect" ) );
    connectPB->setDefault( TRUE );
    Layout24_2->addWidget( connectPB );

    optionsPB = new QPushButton( this, "optionsPB" );
    optionsPB->setText( tr2i18n( "Show options" ) );
    optionsPB->setToggleButton( FALSE );
    Layout24_2->addWidget( optionsPB );

    quitPB = new QPushButton( this, "quitPB" );
    quitPB->setText( tr2i18n( "Quit" ) );
    Layout24_2->addWidget( quitPB );

    KSSHDialogLayout->addLayout( Layout24_2, 4, 0 );

    editorF = new QFrame( this, "editorF" );
    editorF->setFrameShape( QFrame::StyledPanel );
    editorF->setFrameShadow( QFrame::Plain );
    editorF->setLineWidth( 0 );
    editorFLayout = new QGridLayout( editorF, 1, 1, 0, 6, "editorFLayout"); 

    okPB = new QPushButton( editorF, "okPB" );
    okPB->setText( tr2i18n( "OK" ) );

    editorFLayout->addWidget( okPB, 1, 1 );

    cancelPB = new QPushButton( editorF, "cancelPB" );
    cancelPB->setText( tr2i18n( "Cancel" ) );

    editorFLayout->addWidget( cancelPB, 2, 1 );

    userHostELB = new KEditListBox( editorF, "userHostELB" );
    userHostELB->setTitle( QString::null );

    editorFLayout->addMultiCellWidget( userHostELB, 0, 2, 0, 0 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    editorFLayout->addItem( spacer, 0, 1 );

    KSSHDialogLayout->addWidget( editorF, 3, 0 );

    // signals and slots connections
    connect( optionsPB, SIGNAL( toggled(bool) ), optionsGB, SLOT( setEnabled(bool) ) );
    connect( pCB, SIGNAL( toggled(bool) ), portSB, SLOT( setEnabled(bool) ) );
    connect( cCB, SIGNAL( toggled(bool) ), ccCB, SLOT( setEnabled(bool) ) );
    connect( vCB, SIGNAL( toggled(bool) ), vSB, SLOT( setEnabled(bool) ) );

    // tab order
    setTabOrder( hostCB, userCB );
    setTabOrder( userCB, XCB );
    setTabOrder( XCB, xCB );
    setTabOrder( xCB, pCB );
    setTabOrder( pCB, portSB );
    setTabOrder( portSB, LCB );
    setTabOrder( LCB, LLE );
    setTabOrder( LLE, RCB );
    setTabOrder( RCB, RLE );
    setTabOrder( RLE, PCB );
    setTabOrder( PCB, ssh1CB );
    setTabOrder( ssh1CB, ssh2CB );
    setTabOrder( ssh2CB, aCB );
    setTabOrder( aCB, ACB );
    setTabOrder( ACB, cCB );
    setTabOrder( cCB, ccCB );
    setTabOrder( ccCB, CCB );
    setTabOrder( CCB, FCB );
    setTabOrder( FCB, FLE );
    setTabOrder( FLE, IPV4CB );
    setTabOrder( IPV4CB, IPV6CB );
    setTabOrder( IPV6CB, commandLE );
    setTabOrder( commandLE, saveCB );
    setTabOrder( saveCB, aboutPB );
    setTabOrder( aboutPB, savePB );
    setTabOrder( savePB, morePB );
    setTabOrder( morePB, bCB );
    setTabOrder( bCB, bLE );
    setTabOrder( bLE, c1CB );
    setTabOrder( c1CB, cLE );
    setTabOrder( cLE, eCB );
    setTabOrder( eCB, eLE );
    setTabOrder( eLE, fCB );
    setTabOrder( fCB, gCB );
    setTabOrder( gCB, iCB );
    setTabOrder( iCB, iLE );
    setTabOrder( iLE, ICB );
    setTabOrder( ICB, ILE );
    setTabOrder( ILE, kCB );
    setTabOrder( kCB, mCB );
    setTabOrder( mCB, mLE );
    setTabOrder( mLE, nCB );
    setTabOrder( nCB, NCB );
    setTabOrder( NCB, qCB );
    setTabOrder( qCB, vCB );
    setTabOrder( vCB, vSB );
    setTabOrder( vSB, sCB );
    setTabOrder( sCB, TCB );
    setTabOrder( TCB, tCB );
    setTabOrder( tCB, oCB );
    setTabOrder( oCB, oLE );
    setTabOrder( oLE, okPB );
    setTabOrder( okPB, cancelPB );
    setTabOrder( cancelPB, connectPB );
    setTabOrder( connectPB, optionsPB );
    setTabOrder( optionsPB, quitPB );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
KSSHDialog::~KSSHDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

#include "ksshdialog.moc"
