#include "file/openset.h"
#include "base/globals.h"
#include "tools/options.h"
#include "prop.h"
#include "tools.h"
#include "mainwindow.h"

#include <QComboBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QLabel>

typedef struct {const char* name; int type;} FType;

FType FILETYPES[] = {
    {"X Y [Y2] [Y3] ...", SET_NXY},
    {"X Y", SET_XY},
    {"X Y DX",  SET_XYDX},
    {"X Y DY",  SET_XYDY},
    {"X Y DX DX",  SET_XYDXDX},
    {"X Y DY DY",  SET_XYDYDY},
    {"X Y DX DY",  SET_XYDXDY},
    {"X Y Z",  SET_XYZ},
    {"X Y RT",  SET_XYRT},
    {"X Y HI LO",  SET_XYHILO},
    {"X Y U V",  SET_XYUV},
    {"X Y BOX",  SET_XYBOX},
    {"IHL", SET_IHL}
};

FileOpenSet::FileOpenSet(MainWindow *mwin) :
    QFileDialog(mwin, "", QDir::currentPath(), "*")
{
    mainWindow = mwin;
    setAdoptName(true);

#if QT_VERSION >= 0x040500
    this->setOptions(QFileDialog::DontUseNativeDialog);
#endif
    this->setAcceptMode(QFileDialog::AcceptOpen);
    this->setFileMode(QFileDialog::ExistingFiles);
    this->setModal(true);

    fileType = new QComboBox();
    for (unsigned int i=0;i< sizeof(FILETYPES) /sizeof(FILETYPES[0]);i++) {
        fileType->addItem(FILETYPES[i].name);
    }

    graphNum = new QComboBox();
    graphNum->addItem("0");
    graphNum->addItem("1");
    graphNum->setDisabled(true);

    fromFile = new QRadioButton(tr("File"));
    fromPipe = new QRadioButton(tr("Pipe"));
    fromFile->setChecked(true);
    fromPipe->setDisabled(true);

    QWidget* fromButtons = new QWidget();
    QHBoxLayout* fromButtonsLayout = new QHBoxLayout();
    fromButtonsLayout->addWidget(fromFile);
    fromButtonsLayout->addWidget(fromPipe);
    fromButtonsLayout->addStretch(1);
    fromButtons->setLayout(fromButtonsLayout);

    QLayout* layout = this->layout();
    QGridLayout* gridbox = qobject_cast<QGridLayout*>(layout);

    if (gridbox) {
        gridbox->addWidget(new QLabel("File type"),4,0);
        gridbox->addWidget(fileType,4,1);
        gridbox->addWidget(new QLabel("Read from"),5,0);
        gridbox->addWidget(fromButtons,5,1);
        gridbox->addWidget(new QLabel("Read to graph"),6,0);
        gridbox->addWidget(graphNum,6,1);
    }

    this->setLayout(gridbox);
}

void FileOpenSet::accept() {
    // There are two sources for accept(); a buttonbox, and the filechooser
    // frame. We do not want to accept on frame click. Keypresses take buttons
    if (sender()->inherits("QFrame")) {
        return;
    }
    QFileDialog::accept();

    QStringList files = this->selectedFiles();
    if (files.size() == 0) return;

    int type = FILETYPES[fileType->currentIndex()].type;


    for (int i = 0; i < files.size(); ++i) {
        QByteArray v = files.at(i).toUtf8();
        printf("%s \n",v.constData());
        getdata(0,v.data(),SOURCE_DISK,type);
    }

    if (ToolsOptions::isRescaleOnLoad()) {
        mainWindow->toolsMenu->autoScale();
    } else {
        drawgraph();
    }
    if (adoptingName) {
        mainWindow->setFile(directory().absolutePath(), files[0]);
        mainWindow->setLastDirectory(directory());
    }

    SetsSender::send();
}

void FileOpenSet::setAdoptName(bool adopt) {
    adoptingName = adopt;
    if (adoptingName) {
        this->setWindowTitle(tr("Open graph"));
    } else {
        this->setWindowTitle(tr("Read sets or parameters"));
    }
}
