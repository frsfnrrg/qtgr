/****************************************************************************

****************************************************************************/

#ifndef MENUTOOLS_H
#define MENUTOOLS_H

#include <QtGui>
#include "mainwindow.h"
#include "overlay.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

/**
 * @brief The ToolsMenu class
 *
 * This menu encompasses all the view manipulation tools:
 * Autoscale, zoom in, zoom out, zoom rectangle, move left,
 * move right, move up, move down
 *
 */
class ToolsMenu : public QMenu, public RectReceiver
{
    Q_OBJECT

public:
    ToolsMenu(MainWindow* );

    void finishRect(double, double, double, double);

    QToolBar* createToolBar();

public slots:
    void autoScale();
    void zoom();

protected:
   

private slots:
    
private:
    MainWindow *mainWindow;
    void createMenus();
    void createActions();
    QAction *autoScaleAct;
    QAction *zoomRectAct;
};

#endif
