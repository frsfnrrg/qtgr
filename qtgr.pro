HEADERS       = edit.h \
    file.h \
    graphwidget.h \
    base/globals.h \
    base/defines.h \
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
    transform.cpp \
    transform/integration.cpp \
    dialog.cpp \
    transform/differentiation.cpp \
    transform/evaluate.cpp \
    view/title.cpp \
    prop.cpp \
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
    transform/fouriertransform.cpp \
    base/checkon.c \
    base/defaults.c \
    base/draw.c \
    base/drawticks.c \
    base/events.c \
    base/files.c \
    base/fit.c \
    base/objutils.c \
    base/plotone.c \
    base/qtlib.c \
    base/utils.c \
    base/setutils.c \
    base/compute.c \
    base/computils.c \
    base/fourier.c \
    base/lmdif.c \
    base/params.c \
    base/regionutils.c \
    base/graphu1.c \
    base/graphu2.c \
    base/misc.c \
    base/symfunc.c \
    base/dlmodule.c \
    base/nonlfit.c \
    base/as274c.c

YSOURCES =  base/pars.yacc

yaccsource.input = YSOURCES
yaccsource.output = ${QMAKE_FILE_BASE}.yacctmp.c
yaccsource.commands = yacc -d -o ${QMAKE_FILE_BASE}.yacctmp.c ${QMAKE_FILE_IN}
yaccsource.variable_out = SOURCES
yaccsource.name = Yacc Sources ${QMAKE_FILE_IN}
yaccsource.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += yaccsource


# Need to figure out how to handle yacc cleanly

RESOURCES     = qtgr.qrc

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
QT += svg

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

QMAKE_CXXFLAGS += -pipe
