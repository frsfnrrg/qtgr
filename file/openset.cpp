#include "file/openset.h"
#include "base/globals.h"
#include "tools/options.h"
#include "prop.h"
#include "tools.h"

FileOpenSet::FileOpenSet(MainWindow *mwin) :
    QFileDialog(mwin, tr("Read Sets"), QDir::homePath(), "*")
{
    mainWindow = mwin;

    this->setOptions(QFileDialog::DontUseNativeDialog);
    this->setAcceptMode(QFileDialog::AcceptOpen);
    this->setFileMode(QFileDialog::ExistingFiles);

    fileType = new QComboBox();
    fileType->addItem("X Y");
    fileType->addItem("X Y1 Y2");

    graphNum = new QComboBox();
    graphNum->addItem("0");
    graphNum->addItem("1");

    fromFile = new QRadioButton(tr("File"));
    fromPipe = new QRadioButton(tr("Pipe"));

    QWidget* fromButtons = new QWidget();
    QHBoxLayout* fromButtonsLayout = new QHBoxLayout();
    fromButtonsLayout->addWidget(fromFile);
    fromButtonsLayout->addWidget(fromPipe);
    fromButtonsLayout->addStretch(1);
    fromButtons->setLayout(fromButtonsLayout);

    QLayout* layout = this->layout();
    QGridLayout* gridbox = qobject_cast<QGridLayout*>(layout);

    if (gridbox) {
        gridbox->addWidget(new QLabel("File type:"),4,0);
        gridbox->addWidget(fileType,4,1);
        gridbox->addWidget(new QLabel("Read from:"),5,0);
        gridbox->addWidget(fromButtons,5,1);
        gridbox->addWidget(new QLabel("Read to graph:"),6,0);
        gridbox->addWidget(graphNum,6,1);
    }

    this->setLayout(gridbox);
}

void FileOpenSet::accept() {
    QFileDialog::accept();
    QStringList files = this->selectedFiles();

    if (files.size() == 0) return;

    for (int i = 0; i < files.size(); ++i) {
        QByteArray v = files.at(i).toAscii();
        printf("%s \n",v.constData());
        getdata(0,v.data(),DISK,XY);
    }

    if (ToolsOptions::isRescaleOnLoad()) {
        mainWindow->toolsMenu->autoScale();
    } else {
        drawgraph();
    }

    SetsSender::send();
}