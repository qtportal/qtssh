# This spec file was generated using Kpp
# If you find any problems with this spec file please report
# the error to ian geiser <geiseri@msoe.edu>
Summary:   KDE Secure Shell
Name:      kssh
Version:   0.7
Release:   01
Copyright: GPL
Vendor:    Andrea Rizzi <rizzi@kde.org>
Url:       http://kssh.sourceforge.net/

Packager:  Andrea Rizzi <rizzi@kde.org>
Group:     Graphical desktop/KDE
Source:    ./kssh-0.7.tar.gz
BuildRoot: /home/bilibao/tmpssh

%description
KDE 3 Secure Shell frontend
KSSH allows you to access ssh via a nice GUI that remembers the 
host -> username/options associations. 
It also install a new Konsole session that open an ssh connection.

%prep
%setup
CFLAGS="$RPM_OPT_FLAGS" CXXFLAGS="$RPM_OPT_FLAGS" ./configure \
                 --build=i386-linux --host=i386-linux --target=i386-linux --prefix=/opt/kde3 --with-qt-dir=/usr/lib/qt3  \
                $LOCALFLAGS
%build
# Setup for parallel builds
numprocs=`egrep -c ^cpu[0-9]+ /proc/stat || :`
if [ "$numprocs" = "0" ]; then
  numprocs=1
fi

make -j$numprocs

%install
make install-strip DESTDIR=$RPM_BUILD_ROOT

cd $RPM_BUILD_ROOT
find . -type d | sed '1,2d;s,^\.,\%attr(-\,root\,root) \%dir ,' > $RPM_BUILD_DIR/file.list.kssh
find . -type f | sed 's,^\.,\%attr(-\,root\,root) ,' >> $RPM_BUILD_DIR/file.list.kssh
find . -type l | sed 's,^\.,\%attr(-\,root\,root) ,' >> $RPM_BUILD_DIR/file.list.kssh

%clean
rm -rf $RPM_BUILD_ROOT/*
rm -rf $RPM_BUILD_DIR/kssh
rm -rf ../file.list.kssh


%files -f ../file.list.kssh
