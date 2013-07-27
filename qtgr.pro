HEADERS       = edit.h \
    file.h \
    graphwidget.h \
    globals.h \
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
