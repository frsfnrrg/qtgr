#include "transform.h"
#include "transform/integration.h"
#include "transform/differentiation.h"
#include "transform/evaluate.h"
#include "transform/regression.h"
#include "transform/fouriertransform.h"

TransformMenu::TransformMenu(MainWindow* mainWin) :
    Menu(mainWin,"Transforms",true)
{
    createActions();
    integrateDialog = NULL;
    differentiateDialog = NULL;
    evaluateDialog = NULL;
    regressionDialog = NULL;
    fourierDialog = NULL;
    populateMenu(this);
}

void TransformMenu::createActions() {
    integrateAct = makeAction("Integrate",
                              "Integrate a set",
                              "Alt+Shift+I",
                              SLOT(integrate()));
    differentiateAct = makeAction("Differentiate",
                              "Differentiate a set",
                              "Alt+Shift+D",
                              SLOT(differentiate()));
    evaluateAct = makeAction("Evaluate",
                              "Apply an arbitrary simple operation to a set",
                              "Alt+Shift+E",
                              SLOT(evaluate()));
    regressionAct = makeAction("Regression",
                              "Apply regression to a set",
                              "Alt+Shift+R",
                              SLOT(regression()));
    fourierAct = makeAction("Fourier Transform",
                              "Apply inverse or forward FFT or DFT to a set",
                              "Alt+Shift+F",
                              SLOT(fourier()));
}

void TransformMenu::populateMenu(QMenu* q) {
    q->addAction(evaluateAct);
    q->addAction(integrateAct);
    q->addAction(differentiateAct);
    q->addAction(regressionAct);
    q->addAction(fourierAct);
}

void TransformMenu::populateToolBar(QToolBar* q) {
    q->addAction(evaluateAct);
    q->addAction(integrateAct);
    q->addAction(differentiateAct);
    q->addAction(regressionAct);
    q->addAction(fourierAct);
}

void TransformMenu::integrate() {
    launchOrRelaunch<TransformIntegration>(&integrateDialog, mainWindow);
}

void TransformMenu::differentiate() {
    launchOrRelaunch<TransformDifferentiation>(&differentiateDialog, mainWindow);
}

void TransformMenu::evaluate() {
    launchOrRelaunch<TransformEvaluate>(&evaluateDialog, mainWindow);
}

void TransformMenu::regression() {
    launchOrRelaunch<TransformRegression>(&regressionDialog, mainWindow);
}

void TransformMenu::fourier() {
    launchOrRelaunch<TransformFourier>(&fourierDialog, mainWindow);
}
