#include "transform.h"
#include "transform/integration.h"
#include "transform/differentiation.h"
#include "transform/evaluate.h"
#include "transform/regression.h"

TransformMenu::TransformMenu(MainWindow* mainWin) :
    Menu(mainWin,"Transforms",true)
{
    createActions();
    integrateDialog = NULL;
    differentiateDialog = NULL;
    evaluateDialog = NULL;
    regressionDialog = NULL;
    populateMenu(this);
}

void TransformMenu::createActions() {
    integrateAct = makeAction("Integrate",
                              "Integrate a set",
                              "",
                              SLOT(integrate()));
    differentiateAct = makeAction("Differentiate",
                              "Differentiate a set",
                              "",
                              SLOT(differentiate()));
    evaluateAct = makeAction("Evaluate",
                              "Apply an arbitrary simple operation to a set",
                              "",
                              SLOT(evaluate()));
    regressionAct = makeAction("Regression",
                              "Apply regression to a set",
                              "",
                              SLOT(regression()));
}

void TransformMenu::populateMenu(QMenu* q) {
    q->addAction(evaluateAct);
    q->addAction(integrateAct);
    q->addAction(differentiateAct);
    q->addAction(regressionAct);
}

void TransformMenu::populateToolBar(QToolBar* q) {
    q->addAction(evaluateAct);
    q->addAction(integrateAct);
    q->addAction(differentiateAct);
    q->addAction(regressionAct);
}

void TransformMenu::integrate() {
    if (showDialog(integrateDialog)) return;
    integrateDialog = new TransformIntegration(mainWindow);
    loadDialog(integrateDialog);
}

void TransformMenu::differentiate() {
    if (showDialog(differentiateDialog)) return;
    differentiateDialog = new TransformDifferentiation(mainWindow);
    loadDialog(differentiateDialog);
}

void TransformMenu::evaluate() {
    if (showDialog(evaluateDialog)) return;
    evaluateDialog = new TransformEvaluate(mainWindow);
    loadDialog(evaluateDialog);
}

void TransformMenu::regression() {
    if (showDialog(regressionDialog)) return;
    regressionDialog = new TransformRegression(mainWindow);
    loadDialog(regressionDialog);
}
