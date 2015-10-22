#ifndef MENUTOOLS_H
#define MENUTOOLS_H

#include "menu.h"
#include "graphwidget.h"

class ToolsOptions;
class ToolsStatus;
class MainWindow;

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

    void populateMenu(QMenu*);

protected:
    void populateToolBar(QToolBar*);

public slots:
    void autoScale();

private slots:
    void zoom();
    void options();
    void status();

private:
    void createActions();
    QAction *autoScaleAct;
    QAction *zoomRectAct;
    QAction *optionsAct;
    QAction *statusAct;
    ToolsOptions* optionsDialog;
    ToolsStatus* statusDialog;
};

#endif
