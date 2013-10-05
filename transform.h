#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QtGui>
#include "dialog.h"
#include "menu.h"

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

    Dialog* integrateDialog;
    Dialog* differentiateDialog;
    Dialog* evaluateDialog;
    Dialog* regressionDialog;

private slots:
    void evaluate();
    void integrate();
    void differentiate();
    void regression();

};

#endif // TRANSFORM_H
