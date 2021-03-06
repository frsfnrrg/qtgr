#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "menu.h"

class Dialog;

class TransformMenu : public Menu
{
    Q_OBJECT
public:
    explicit TransformMenu(MainWindow* mainWin);

    void populateMenu(QMenu* q);

protected:
    void populateToolBar(QToolBar*);

private:
    void createActions();

    QAction* integrateAct;
    QAction* differentiateAct;
    QAction* evaluateAct;
    QAction* regressionAct;
    QAction* fourierAct;

    Dialog* integrateDialog;
    Dialog* differentiateDialog;
    Dialog* evaluateDialog;
    Dialog* regressionDialog;
    Dialog* fourierDialog;

private slots:
    void evaluate();
    void integrate();
    void differentiate();
    void regression();
    void fourier();

};

#endif // TRANSFORM_H
