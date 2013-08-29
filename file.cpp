#include <QtGui>
#include "mainwindow.h"
#include "file.h"
#include "base/globals.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"
#include "file/openset.h"
#include "file/export.h"
#include "file/saveall.h"

FileMenu::FileMenu(MainWindow* mainWin) :
    Menu(mainWin, "File", true)
{  
    createActions();

    opensetDialog = NULL;
    exportDialog = NULL;
    saveallDialog = new FileSaveAll(this->mainWindow);   

    populateMenu(this);
}

void FileMenu::populateToolBar(QToolBar* t) {
    t->addAction(readSetAct);
    t->addAction(resetAct);
    t->addSeparator();
    t->addAction(printAct);
    t->addAction(exportAct);
    t->addSeparator();
    t->addAction(exitAct);
}


void FileMenu::populateMenu(QMenu* m)
{
    m->addAction(readSetAct);
    m->addAction(readParaAct);
    m->addAction(readBlockAct);
    m->addSeparator();
    m->addAction(writeSetAct);
    m->addAction(writeParaAct);
    m->addAction(writeBlockAct);
    m->addSeparator();
    m->addAction(resetAct);
    m->addSeparator();
    m->addAction(printAct);
    m->addAction(exportAct);
    m->addSeparator();
    m->addAction(exitAct);
}

void FileMenu::createActions()
{
    readSetAct = makeAction("Open",
                            "Load a set or graph from file or pipe onto the graph",
                            "Ctrl+O", SLOT(open_set()));

    readParaAct = makeAction("Read parameters",
                             "Read instructions to create a graph",
                             "", SLOT(open_param()));
    readParaAct->setEnabled(false);
    
    readBlockAct = makeAction("Read block data",
                              "Read block data",
                              "", SLOT(open_block()));
    readBlockAct->setEnabled(false);
    
    writeSetAct = makeAction("Write sets",
                             "Write sets",
                             "", SLOT(write_set()));
    writeSetAct->setEnabled(false);

    writeParaAct = makeAction("Write parameters",
                              "Write parameters",
                              "", SLOT(write_param()));
    writeParaAct->setEnabled(false);

    writeBlockAct = makeAction("Save graph",
                               "Save graph to a file",
                               "", SLOT(save_all()));

    resetAct = makeAction("Clear all",
                          "Reset the graph to its original state",
                          "Ctrl+Shift+d", SLOT(reset()));
	
    printAct = makeAction("Print",
                          "Print the current view to file or printer.",
                          "Ctrl+p", SLOT(print()));

    exportAct = makeAction("Export",
                           "Export display to an image",
                           "Ctrl+E", SLOT(save_as()));

    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this->mainWindow, SLOT(close()));
}

void FileMenu::open_set() {
    if (opensetDialog) {
        opensetDialog->setVisible(true);
        opensetDialog->raise();
    } else {
       opensetDialog = new FileOpenSet(this->mainWindow);
       opensetDialog->show();
    }
}

void FileMenu::open_param() {
    // TODO
}

void FileMenu::open_block() {
    // TODO
}

void FileMenu::write_set() {
    // TODO
}

void FileMenu::write_param() {
    // TODO
}

void FileMenu::save_all() {

       saveallDialog->exec();
}

void FileMenu::reset()
{
    wipeout(0);
 
    inwin = TRUE;
    set_graph_active(0);
    drawgraph();

    SetsSender::send();
}

// WARNING LEAKS: make a dialog
void FileMenu::print()
{
    QPrinter *printer = new QPrinter();
    
    //set printer defaults
    printer->setPageSize(QPrinter::Letter);
    printer->setOrientation(QPrinter::Landscape);
    printer->setResolution(600);
    
    QPrintDialog *dialog = new QPrintDialog(printer, this);
    dialog->setWindowTitle(tr("Print Document"));
    if (dialog->exec() != QDialog::Accepted)
	return;

    QPainter* painter = new QPainter(); 
    painter->begin(printer);
    this->mainWindow->gwidget->scene()->render(painter);
    painter->end();   
}

// WARNING LEAKS: make a dialog
void FileMenu::save_as()
{
    if (exportDialog) {
        exportDialog->setVisible(true);
        opensetDialog->raise();
    } else {
        exportDialog = new FileExport(mainWindow);
        exportDialog->show();
    }
}
