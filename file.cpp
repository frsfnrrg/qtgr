#include "mainwindow.h"
#include "graphwidget.h"
#include "file.h"
#include "base/globals.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"
#include "file/openset.h"
#include "file/export.h"
#include "file/saveall.h"

#include <QToolBar>
#include <QString>
#include <QStatusBar>
#if QT_VERSION >= 0x050000
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#else
#include <QPrinter>
#include <QPrintDialog>
#endif

FileMenu::FileMenu(MainWindow* mainWin) :
    Menu(mainWin, "File", true)
{  
    createActions();

    opensetDialog = NULL;
    exportDialog = NULL;
    saveallDialog = NULL;

    populateMenu(this);
}

void FileMenu::populateToolBar(QToolBar* t) {
    t->addAction(openAct);
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
    m->addAction(resetAct);
    m->addSeparator();
    m->addAction(openAct);
    m->addAction(readSetAct);
    m->addAction(readParaAct);
    m->addAction(readBlockAct);
    m->addSeparator();
    m->addAction(writeSetAct);
    m->addAction(writeParaAct);
    m->addAction(saveAct);
    m->addAction(saveAsAct);
    m->addSeparator();
    m->addAction(printAct);
    m->addAction(exportAct);
    m->addSeparator();
    m->addAction(exitAct);
}

void FileMenu::createActions()
{
    resetAct = makeAction("New",
                          "Reset the graph to its original state",
                          "Ctrl+N", SLOT(reset()));

    openAct = makeAction("Open graph",
                            "Load a set or graph from file or pipe onto the graph",
                            "Ctrl+O", SLOT(open_file()));

    readSetAct = makeAction("Read set",
                            "Read a set but to not adopt its file name",
                            "Ctrl+R", SLOT(read_set()));

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

    saveAct = makeAction("Save",
                          "Save graph",
                           "Ctrl+S", SLOT(save()));

    saveAsAct = makeAction("Save As",
                          "Save graph with a new filename",
                           "Ctrl+Shift+S", SLOT(save_as()));
	
    printAct = makeAction("Print",
                          "Print the current view to file or printer.",
                          "Ctrl+p", SLOT(print()));

    exportAct = makeAction("Export",
                           "Export display to an image",
                           "Ctrl+E", SLOT(export_file()));

    exitAct = new QAction(tr("Quit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this->mainWindow, SLOT(close()));
}

void FileMenu::open_file() {
    if (opensetDialog) {
        opensetDialog->setVisible(true);
        opensetDialog->raise();
    } else {
       opensetDialog = new FileOpenSet(mainWindow);
       opensetDialog->show();
    }
    opensetDialog->setAdoptName(true);
    opensetDialog->setDirectory(mainWindow->lastDirectory());
}

void FileMenu::read_set() {
    if (opensetDialog) {
        opensetDialog->setVisible(true);
        opensetDialog->raise();
    } else {
       opensetDialog = new FileOpenSet(mainWindow);
       opensetDialog->show();
    }
    opensetDialog->setAdoptName(false);
    opensetDialog->setDirectory(mainWindow->lastDirectory());
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

void FileMenu::save() {
    if (mainWindow->hasFile()) {
        QString outformat("%g %g");
        do_writesets(MAXGRAPH, -1, -1, mainWindow->fullFileName().toUtf8().data(),
                     outformat.toUtf8().data());
        QString message = "Saved file: " + mainWindow->fullFileName();
        mainWindow->statusBar()->showMessage(message, 2000);
    } else {
        save_as();
    }
}

void FileMenu::save_as() {
    if (saveallDialog) {
        saveallDialog->setVisible(true);
        saveallDialog->raise();
    } else {
        saveallDialog = new FileSaveAll(mainWindow);
        saveallDialog->show();
    }
    if (mainWindow->hasFile()) {
        saveallDialog->selectFile(mainWindow->shortFileName() + "." + saveallDialog->defaultSuffix());
    } else {
        saveallDialog->selectFile(QString());
    }
    saveallDialog->setDirectory(mainWindow->lastDirectory());
}

void FileMenu::reset()
{
    wipeout(0);
 
    inwin = TRUE;
    set_graph_active(0);
    drawgraph();

    mainWindow->clearFile();

    SetsSender::send();
}

void FileMenu::print()
{
    QPrinter *printer = new QPrinter();
    
    //set printer defaults
    printer->setPageSize(QPrinter::Letter);
    printer->setOrientation(QPrinter::Landscape);
    printer->setResolution(600);
    
    QPrintDialog *dialog = new QPrintDialog(printer, this);
    dialog->setWindowTitle(tr("Print Document"));
    if (dialog->exec() != QDialog::Accepted) return;

    QPainter* painter = new QPainter(); 
    painter->begin(printer);
    this->mainWindow->gwidget->scene()->render(painter);
    painter->end();   
}

void FileMenu::export_file()
{
    if (exportDialog) {
        exportDialog->setVisible(true);
        exportDialog->raise();
    } else {
        exportDialog = new FileExport(mainWindow);
        exportDialog->show();
    }
    // technically, this could be reduced to signal-slot connection between
    // FileMenu & the four name-inducing actions/dialogs. Why put mainWindow into
    // this?
    if (mainWindow->hasFile()) {
        QString ending = exportDialog->selectedNameFilter();
        exportDialog->selectFile(mainWindow->shortFileName()+ending.right(ending.size() - 1));
    } else {
        exportDialog->selectFile(QString());
    }
    exportDialog->setDirectory(mainWindow->lastDirectory());
}
