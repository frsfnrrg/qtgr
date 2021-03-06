#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QMainWindow>
#include <QDir>
#include <QSettings>
#include <QTime>

class Menu;
class ViewMenu;
class FileMenu;
class EditMenu;
class ToolsMenu;
class TransformMenu;
class SetsMenu;
class GraphWidget;

class QGraphicsView;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
    QGraphicsView* view;
    GraphWidget* gwidget;

    ViewMenu* viewMenu;
    FileMenu* fileMenu;
    EditMenu* editMenu;
    SetsMenu* setMenu;
    ToolsMenu* toolsMenu;
    TransformMenu* transformMenu;
    QMenu* helpMenu;

    void setFile(QString directory, QString name);
    void clearFile();
    bool hasFile();
    QString fullFileName();
    QString fileName();
    QString shortFileName();
    QString fileDirectory();

    void setLastDirectory(QDir);
    QDir lastDirectory();

private:
    QSettings settings;

    QString fName;
    QString fDir;
    QDir lastDir;

    QTime startuptime;

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
