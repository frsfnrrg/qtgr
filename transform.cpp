#include "transform.h"
#include "transform/integration.h"

TransformMenu::TransformMenu(MainWindow* mainWin) :
    QMenu(mainWin)
{
    this->mainWindow = mainWin;
    this->setTitle(tr("Transforms"));
    createActions();
    createMenus();
    integrateDialog = NULL;
    differentiateDialog = NULL;
}

void TransformMenu::createActions() {
    integrateAct = new QAction(tr("Integrate"), this);
    integrateAct->setStatusTip(tr("Integrate a set"));
    connect(integrateAct, SIGNAL(triggered()), this, SLOT(integrate()));


    differentiateAct = new QAction(tr("Differentiate"), this);
    differentiateAct->setStatusTip(tr("Differentiate a set"));
    connect(differentiateAct, SIGNAL(triggered()), this, SLOT(differentiate()));
}

void TransformMenu::createMenus() {
    this->setTearOffEnabled(true);
    this->addAction(integrateAct);
    this->addAction(differentiateAct);
}

//#define SHOW_AND_UPDATE(thing, )

void TransformMenu::integrate() {
  //  _This_, would be a good preprocessor macro
  //
  //  SHOW_AND_UPDATE(integrateDialog,
  //                  TransformIntegration,
  //                  this->mainWindow);
    if (integrateDialog) {
        integrateDialog->setVisible(true);
    } else {
        integrateDialog = new TransformIntegration(this->mainWindow);
        integrateDialog->show();
    }
    integrateDialog->updateDialog();
}

void TransformMenu::differentiate() {

}

// TODO: create the set of dialogs...
// (maybe in a subfolder?)
