#ifndef MENUTOOLS_H
#define MENUTOOLS_H

#include <QtGui>
#include "mainwindow.h"
#include "overlay.h"
#include "menu.h"
#include "tools/options.h"

/**
 * @brief The ToolsMenu class
 *
 * This menu encompasses all the view manipulation tools:
 * Autoscale, zoom in, zoom out, zoom rectangle, move left,
 * move right, move up, move down
 *
 */
class ToolsMenu : public Menu, public RectReceiver
{
    Q_OBJECT

public:
    ToolsMenu(MainWindow* );

    void finishRect(double, double, double, double);

    QToolBar* createToolBar();
    void populateMenu(QMenu*);

    ToolsOptions* getOptions();

public slots:
    void autoScale();
    void zoom();
    void options();

protected:
   

private slots:
    
private:
    void createActions();
    QAction *autoScaleAct;
    QAction *zoomRectAct;
    QAction *optionsAct;
    ToolsOptions* optionsDialog;
};

#endif
