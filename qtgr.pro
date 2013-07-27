HEADERS       = edit.h \
		file.h \
		graphwidget.h \
		globals.h \
		mainwindow.h \
		mousecall.h \
		view.h \ 
		view_ticks.h \
		view_symbols.h \
		view_world.h \
		tools.h \
    view_graphtype.h \
    view_legends.h \
    transform.h
		
SOURCES       = edit.cpp \	
		file.cpp \
		graphwidget.cpp \
		main.cpp \
		mainwindow.cpp \
		tools.cpp \
		view.cpp \
		view_ticks.cpp \
		view_symbols.cpp \
		view_world.cpp \		
		alerts.c \
		checkon.c \
		chersh.c \
		defaults.c \
		draw.c \
		drawticks.c \
		events.c \
		files.c \
		fit.c \
		graphutils.c \
		objutils.c \
		pars.c \
		plotone.c \
		qtlib.c \
		utils.c \
		setprops.c \
		setutils.c \
		getparms.c \
    view_graphtype.cpp \
    view_legends.cpp \
    transform.cpp

RESOURCES     = qtgr.qrc


# install
target.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/qtgr
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS qtgr.pro images
sources.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/qtgr
INSTALLS += target sources
