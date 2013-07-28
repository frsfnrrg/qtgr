HEADERS       = edit.h \
    file.h \
    graphwidget.h \
    base/globals.h \
    base/defines.h \
    base/pars.h \
    base/externs.h \
    base/hersh.h \
    base/patterns.h \
    base/special.h \
    base/symdefs.h \
    base/f2c.h \
    mainwindow.h \
    mousecall.h \
    view.h \ 
    view/ticks.h \
    view/symbols.h \
    view/world.h \
    tools.h \
    view/graphtype.h \
    view/legends.h \
    transform.h \
    transform/integration.h \
    dialog.h \
    view/viewport.h \
    transform/differentiation.h \
    transform/evaluate.h \
    view/title.h \
    setcombobox.h

SOURCES       = edit.cpp \
    file.cpp \
    graphwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    tools.cpp \
    view.cpp \
    view/ticks.cpp \
    view/symbols.cpp \
    view/world.cpp \
    base/alerts.c \
    base/checkon.c \
    base/chersh.c \
    base/defaults.c \
    base/draw.c \
    base/drawticks.c \
    base/events.c \
    base/files.c \
    base/fit.c \
    base/graphutils.c \
    base/objutils.c \
    base/pars.c \
    base/plotone.c \
    base/qtlib.c \
    base/utils.c \
    base/setutils.c \
    base/getparms.c \
    base/setprops.c \
    base/compute.c \
    base/computils.c \
    base/fourier.c \
    base/lmdif1.c \
    base/params.c \
    base/regionutils.c \
    view/graphtype.cpp \
    view/legends.cpp \
    transform.cpp \
    transform/integration.cpp \
    dialog.cpp \
    view/viewport.cpp \
    transform/differentiation.cpp \
    transform/evaluate.cpp \
    view/title.cpp \
    setcombobox.cpp

RESOURCES     = qtgr.qrc


# install
target.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/qtgr
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS qtgr.pro images
sources.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/qtgr
INSTALLS += target sources
