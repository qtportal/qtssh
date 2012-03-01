####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = kssh

## INCLUDES were found outside kdevelop specific part

kssh_SOURCES = ksshdialog.ui kssh.cpp main.cpp 
kssh_LDADD   =  $(LIB_KFILE) $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT) $(LIBSOCKET)


EXTRA_DIST = main.cpp kssh.cpp kssh.h kssh.desktop lo32-app-kssh.png ksshdialog.ui ssh.desktop lo16-app-kssh.png hi48-app-kssh.png hi16-app-kssh.png hi22-app-kssh.png 

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Internet/
	$(INSTALL_DATA) $(srcdir)/kssh.desktop $(kde_appsdir)/Internet/kssh.desktop
	$(mkinstalldirs) $(kde_icondir)/locolor/32x32/apps/
	$(INSTALL_DATA) $(srcdir)/lo32-app-kssh.png $(kde_icondir)/locolor/32x32/apps/kssh.png
	$(mkinstalldirs) $(kde_datadir)/konsole/
	$(INSTALL_DATA) $(srcdir)/ssh.desktop $(kde_datadir)/konsole/kssh.desktop
	$(mkinstalldirs) $(kde_icondir)/locolor/16x16/apps/
	$(INSTALL_DATA) $(srcdir)/lo16-app-kssh.png $(kde_icondir)/locolor/16x16/apps/kssh.png
	$(mkinstalldirs) $(kde_icondir)/hicolor/48x48/apps/
	$(INSTALL_DATA) $(srcdir)/hi48-app-kssh.png $(kde_icondir)/hicolor/48x48/apps/kssh.png
	$(mkinstalldirs) $(kde_icondir)/hicolor/16x16/apps/
	$(INSTALL_DATA) $(srcdir)/hi16-app-kssh.png $(kde_icondir)/hicolor/16x16/apps/kssh.png
	$(mkinstalldirs) $(kde_icondir)/hicolor/22x22/apps/
	$(INSTALL_DATA) $(srcdir)/hi22-app-kssh.png $(kde_icondir)/hicolor/22x22/apps/kssh.png

uninstall-local:
	-rm -f $(kde_appsdir)/Internet/kssh.desktop
	-rm -f $(kde_icondir)/locolor/32x32/apps/kssh.png
	-rm -f $(kde_datadir)/konsole/kssh.desktop
	-rm -f $(kde_icondir)/locolor/16x16/apps/kssh.png
	-rm -f $(kde_icondir)/hicolor/48x48/apps/kssh.png
	-rm -f $(kde_icondir)/hicolor/16x16/apps/kssh.png
	-rm -f $(kde_icondir)/hicolor/22x22/apps/kssh.png

####### kdevelop will overwrite this part!!! (end)############
# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_minidir       Where your mini icon should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
kssh_LDFLAGS = $(all_libraries) $(KDE_RPATH)

# Uncomment the following two lines if you add a ui.rc file for your application to make use of
# KDE
#rcdir = $(kde_datadir)/kssh
#rc_DATA = ksshui.rc

#WARNING: if you use a ui.rc file above, use:

# messages: rc.cpp

# instead of 

# messages:

messages: 
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/kssh.pot; \
	fi

