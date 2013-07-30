#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "graphwidget.h"

// where should this utility function go? create a util.cpp?
QAction* createQAction(const QString &name, const QString &explained, QObject* parent);

class ViewMenu;
class FileMenu;
class EditMenu;
class ToolsMenu;

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    QGraphicsView* view;
    GraphWidget* gwidget;

    ViewMenu* viewMenu;
    FileMenu* fileMenu;
    EditMenu* editMenu;
    ToolsMenu* toolsMenu;
    QMenu* helpMenu;

protected:
    void closeEvent(QCloseEvent *);
private slots:
    void about();
private:
    void readSettings();
    void writeSettings();
    void createMenus();
    void createHelpMenu();
};

#endif
