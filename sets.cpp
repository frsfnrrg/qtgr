#include "sets.h"

SetsMenu::SetsMenu(MainWindow* mwin) :
    QMenu(mwin)
{
    this->mainWindow = mwin;
    this->setTitle(tr("Sets"));
    this->setTearOffEnabled(true);
}
