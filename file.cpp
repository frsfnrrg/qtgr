#include <QtGui>
#include "mainwindow.h"
#include "file.h"
#include "base/globals.h"
#include "prop.h"
#include "tools.h"
#include "tools/options.h"

FileMenu::FileMenu(MainWindow* mainWin)

{  
    this->mainWindow = mainWin;
    this->setTitle(tr("&File"));
    createActions();
    createMenus();
}


void FileMenu::createMenus()
{
    this->setTearOffEnabled(true);
    this->addAction(readSetAct);
    this->addAction(readParaAct);
    this->addAction(readBlockAct);
    this->addSeparator();
    this->addAction(writeSetAct);
    this->addAction(writeParaAct);
    this->addAction(saveAllAct);
    this->addSeparator();
    this->addAction(clearAct);
    this->addSeparator();
    this->addAction(printAct);
    this->addAction(exportAct);
    this->addSeparator();
    this->addAction(exitAct);
}

void FileMenu::createActions()
{
    readSetAct = createQAction(tr("Read sets"),
                               tr("Load a set from file or pipe onto the graph"),
                               tr("Ctrl+O"),
                               this);
    connect(readSetAct, SIGNAL(triggered()), this, SLOT(open()));

    readParaAct = new QAction(tr("Read parameters..."), this);
//     connect(readParaAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    readBlockAct = new QAction(tr("Read block data..."), this);
//     connect(readBlockAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    writeSetAct = new QAction(tr("Write sets..."), this);
//     connect(writeSetAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    writeParaAct = new QAction(tr("Write parameters..."), this);
//     connect(writeParaAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    saveAllAct = new QAction(tr("Save all..."), this);
//     connect(saveAllAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    clearAct = createQAction(tr("Clear all"),
                             tr("Reset the graph to its original state"),
                             tr("Ctrl+Shift+d"),
                             this);
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clear()));
	
    printAct = createQAction(tr("&Print"),
                             tr("Print the current view to file or printer."),
                             tr("Ctrl+p"),
                             this);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
    
    exportAct = createQAction(tr("Export"),
                              tr("Export display to an image"),
                              tr("Ctrl+E"),
                              this);
    connect(exportAct, SIGNAL(triggered()), this, SLOT(exportProc()));
    
    printSetupAct = new QAction(tr("&Printer setup..."), this);
		
//     connect(saveAllAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this->mainWindow, SLOT(close()));
}

void FileMenu::open()
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

    ToolsOptions* t = mainWindow->toolsMenu->getOptions();
    if (t->isRescaleOnLoad()) {
        mainWindow->toolsMenu->autoScale();
    } else {
        drawgraph();
    }

    SetsSender::send();
}

void FileMenu::clear() 
{
    wipeout(0);
 
    inwin = TRUE;
    set_graph_active(0);
    drawgraph();

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
    if (dialog->exec() != QDialog::Accepted)
	return;

    QPainter* painter = new QPainter(); 
    painter->begin(printer);
    this->mainWindow->gwidget->scene()->render(painter);
    painter->end();   
}

void FileMenu::exportProc()
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
