#include "menu.h"

Menu::Menu(MainWindow* mainWin, const char* title, bool tearoff) :
    QMenu(mainWin)
{
    this->setTitle(tr(title));
    this->setTearOffEnabled(tearoff);
    mainWindow = mainWin;
}

void Menu::updateDialog(Dialog* d) {
    if (d) d->updateDialog();
}

void Menu::loadDialog(Dialog* d) {
    d->show();
    d->updateDialog();
}

bool Menu::showDialog(Dialog* d) {
    if (d) {
        d->setVisible(true);
        d->updateDialog();
        return true;
    } else {
        return false;
    }
}

QAction* Menu::makeAction(const char* name, const char* desc, const char* shortcut,
                          const char* slot) {
    QAction* f = createQAction(name, desc, shortcut, this);
    connect(f, SIGNAL(triggered()), this, slot);
    return f;
}
