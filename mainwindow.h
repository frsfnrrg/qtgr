#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class Menu;
class ViewMenu;
class FileMenu;
class EditMenu;
class ToolsMenu;
class TransformMenu;
class SetsMenu;
class GraphWidget;

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
    SetsMenu* setMenu;
    ToolsMenu* toolsMenu;
    TransformMenu* transformMenu;
    QMenu* helpMenu;

    void setFileName(QString name);
    void clearFileName();
    bool hasFileName();
    QString fileName();

    void setLastDirectory(QDir);
    QDir lastDirectory();

private:
    QSettings settings;

    QString fName;
    QDir lastDir;

protected:
    void closeEvent(QCloseEvent *);
private slots:
    void about();
    void dropEvent(QDropEvent *);
    void writeToolBarSettings(bool);
    void initialize();

private:
    void addToolBar(Menu* m, bool showdef);
    void readSettings();
    void writeSettings();
    void createMenus();
    void createHelpMenu();
};

#endif
