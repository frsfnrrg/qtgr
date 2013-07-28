#include "transform.h"
#include "transform/integration.h"
#include "transform/differentiation.h"
#include "transform/evaluate.h"

TransformMenu::TransformMenu(MainWindow* mainWin) :
    QMenu(mainWin)
{
    this->mainWindow = mainWin;
    this->setTitle(tr("Transforms"));
    createActions();
    createMenus();
    integrateDialog = NULL;
    differentiateDialog = NULL;
    evaluateDialog = NULL;
}

void TransformMenu::createActions() {
    integrateAct = new QAction(tr("Integrate"), this);
    integrateAct->setStatusTip(tr("Integrate a set"));
    connect(integrateAct, SIGNAL(triggered()), this, SLOT(integrate()));

    differentiateAct = new QAction(tr("Differentiate"), this);
    differentiateAct->setStatusTip(tr("Differentiate a set"));
    connect(differentiateAct, SIGNAL(triggered()), this, SLOT(differentiate()));

    evaluateAct = new QAction(tr("Evaluate"), this);
    evaluateAct->setStatusTip(tr("Apply an arbitrary simple operation to a set"));
    connect(evaluateAct, SIGNAL(triggered()), this, SLOT(evaluate()));
}

void TransformMenu::createMenus() {
    this->setTearOffEnabled(true);
    this->addAction(evaluateAct);
    this->addAction(integrateAct);
    this->addAction(differentiateAct);
}

void TransformMenu::integrate() {
    if (integrateDialog) {
        integrateDialog->setVisible(true);
    } else {
        integrateDialog = new TransformIntegration(this->mainWindow);
        integrateDialog->show();
    }
    integrateDialog->updateDialog();
}

void TransformMenu::differentiate() {
    if (differentiateDialog) {
        differentiateDialog->setVisible(true);
    } else {
        differentiateDialog = new TransformDifferentiation(this->mainWindow);
        differentiateDialog->show();
    }
    differentiateDialog->updateDialog();
}

void TransformMenu::evaluate() {
    if (evaluateDialog) {
        evaluateDialog->setVisible(true);
    } else {
        evaluateDialog = new TransformEvaluate(this->mainWindow);
        evaluateDialog->show();
    }
    evaluateDialog->updateDialog();
}
