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
    QToolBar* createToolBar();

private:
    void createActions();
    QAction* integrateAct;
    QAction* differentiateAct;
    QAction* evaluateAct;
    Dialog* integrateDialog;
    Dialog* differentiateDialog;
    Dialog* evaluateDialog;

signals:
    
public slots:
    void evaluate();
    void integrate();
    void differentiate();

private slots:
};

#endif // TRANSFORM_H
