#include <QtGui>
#include "mainwindow.h"
#include "file.h"
#include "base/globals.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"

FileMenu::FileMenu(MainWindow* mainWin) :
    Menu(mainWin, "File", true)

{  
    createActions();
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
    readSetAct = makeAction("Read sets",
                            "Load a set from file or pipe onto the graph",
                            "Ctrl+O", SLOT(open_set()));

    readParaAct = makeAction("Read parameters",
                             "Read instructions to create a graph",
                             "", SLOT(open_param()));
    
    readBlockAct = makeAction("Read block data",
                              "Read block data",
                              "", SLOT(open_block()));
    
    writeSetAct = makeAction("Write sets",
                             "Write sets",
                             "", SLOT(write_set()));

    writeParaAct = makeAction("Write parameters",
                              "Write parameters",
                              "", SLOT(write_param()));

    writeBlockAct = makeAction("Write block data",
                               "Write block data",
                               "", SLOT(write_block()));

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

// WARNING LEAKS: make a dialog
void FileMenu::open_set()
{
    QComboBox* fileType = new QComboBox;
    fileType->addItem("X Y");
    fileType->addItem("X Y1 Y2");
    QComboBox* graphNum = new QComboBox;
    graphNum->addItem("0");
    graphNum->addItem("1");
    
    QWidget* fromButtons = new QWidget();
    QHBoxLayout* fromButtonsLayout = new QHBoxLayout();
    fromButtonsLayout->addWidget(new QRadioButton("File"));
    fromButtonsLayout->addWidget(new QRadioButton("Pipe"));
    fromButtonsLayout->addStretch(1);
    fromButtons->setLayout(fromButtonsLayout);
    
    QFileDialog::Options options = QFileDialog::DontUseNativeDialog;

    QFileDialog* fd = new QFileDialog(this, tr("Read Sets"), QDir::homePath(), "*");
    fd->setOptions(options);
    QLayout* layout = fd->layout();
    QGridLayout* gridbox = qobject_cast<QGridLayout*>(layout);
    
    if (gridbox) {
	    gridbox->addWidget(new QLabel("File type:"),4,0);
	    gridbox->addWidget(fileType,4,1);
	    gridbox->addWidget(new QLabel("Read from:"),5,0);
	    gridbox->addWidget(fromButtons,5,1);
	    gridbox->addWidget(new QLabel("Read to graph:"),6,0);
	    gridbox->addWidget(graphNum,6,1);
    }

    fd->setLayout(gridbox);
    QStringList fileNames;
    if (fd->exec())
	fileNames = fd->selectedFiles();
    
//  nothing selected      
    if (fileNames.size() == 0) return; 
      
    for (int i = 0; i < fileNames.size(); ++i)
	  printf("%s \n",fileNames.at(i).toAscii().constData());

    getdata(0,fileNames.at(0).toAscii().data(),DISK,XY);

    if (ToolsOptions::isRescaleOnLoad()) {
        mainWindow->toolsMenu->autoScale();
    } else {
        drawgraph();
    }

    SetsSender::send();
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

void FileMenu::write_block() {
    // TODO
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
    QPixmap* image = new QPixmap(800*3,600*3);
    QPainter *pngPainter = new QPainter(image);
    
    printf("Export\n");
    
//     pngPainter->setRenderHint(QPainter::Antialiasing);
    this->mainWindow->gwidget->scene()->render(pngPainter);
    pngPainter->end();
    image->save("qtgr.png");
    delete pngPainter;
    delete image;
    
}
