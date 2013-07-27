HEADERS       = edit.h \
    file.h \
    graphwidget.h \
    core/globals.h \
    core/defines.h \
    core/pars.h \
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
    view/viewport.h

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
    core/alerts.c \
    core/checkon.c \
    core/chersh.c \
    core/defaults.c \
    core/draw.c \
    core/drawticks.c \
    core/events.c \
    core/files.c \
    core/fit.c \
    core/graphutils.c \
    core/objutils.c \
    core/pars.c \
    core/plotone.c \
    core/qtlib.c \
    core/utils.c \
    core/setutils.c \
    core/getparms.c \
    view/graphtype.cpp \
    view/legends.cpp \
    transform.cpp \
    transform/integration.cpp \
    dialog.cpp \
    view/viewport.cpp

RESOURCES     = qtgr.qrc


# install
target.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/qtgr
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS qtgr.pro images
sources.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/qtgr
INSTALLS += target sources
