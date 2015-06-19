#include "menu.h"
#include "dialog.h"
#include "util.h"
#include "mainwindow.h"

#include <QToolBar>

Menu::Menu(MainWindow *mainWin, const char *title, bool tearoff)
    : QMenu(mainWin) {
    this->setTitle(tr(title));
    this->setTearOffEnabled(tearoff);
    mainWindow = mainWin;
}

void Menu::updateDialog(Dialog *d) {
    if (d)
        d->updateDialog();
}

QToolBar *Menu::createToolBar(bool show) {
    QToolBar *f = new QToolBar(title());
    if (!show)
        f->hide();
    populateToolBar(f);
    return f;
}

QAction *Menu::makeAction(const char *name, const char *desc,
                          const char *shortcut, const char *slot) {
    QAction *f = createQAction(name, desc, shortcut, this);
    connect(f, SIGNAL(triggered()), this, slot);
    return f;
}

void Menu::populateToolBar(QToolBar *) {
    printf("YOU SHOULD NOT BE CALLING THIS\n");
}
