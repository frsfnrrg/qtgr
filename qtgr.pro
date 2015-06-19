HEADERS       = edit.h \
    file.h \
    graphwidget.h \
    base/globals.h \
    base/defines.h \
    base/pars.h \
    base/externs.h \
    base/patterns.h \
    base/symdefs.h \
    base/f2c.h \
    mainwindow.h \
    view.h \ 
    view/symbols.h \
    tools.h \
    transform.h \
    transform/integration.h \
    dialog.h \
    transform/differentiation.h \
    transform/evaluate.h \
    view/title.h \
    prop.h \
    overlay.h \
    sets.h \
    view/frame.h \
    sets/kad.h \
    sets/sedit.h \
    menu.h \
    sets/mcs.h \
    tools/options.h \
    util.h \
    choosers.h \
    file/openset.h \
    file/export.h \
    file/saveall.h \
    view/dimensions.h \
    view/legend.h \
    view/axis.h \
    transform/regression.h \
    view/text.h \
    tools/status.h \
    transform/fouriertransform.h

SOURCES       = edit.cpp \
    file.cpp \
    graphwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    tools.cpp \
    view.cpp \
    view/symbols.cpp \
    base/alerts.c \
    base/checkon.c \
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
    transform.cpp \
    transform/integration.cpp \
    dialog.cpp \
    transform/differentiation.cpp \
    transform/evaluate.cpp \
    view/title.cpp \
    prop.cpp \
    overlay.cpp \
    sets.cpp \
    view/frame.cpp \
    sets/kad.cpp \
    sets/sedit.cpp \
    menu.cpp \
    sets/mcs.cpp \
    tools/options.cpp \
    util.cpp \
    choosers.cpp \
    file/openset.cpp \
    file/export.cpp \
    file/saveall.cpp \
    view/dimensions.cpp \
    view/legend.cpp \
    view/axis.cpp \
    transform/regression.cpp \
    view/text.cpp \
    tools/status.cpp \
    transform/fouriertransform.cpp

RESOURCES     = qtgr.qrc

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
QT += svg

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

QMAKE_CXXFLAGS += -pipe
