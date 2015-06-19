#include "file/saveall.h"
#include "base/globals.h"
#include "mainwindow.h"

#include <QStatusBar>

FileSaveAll::FileSaveAll(MainWindow *mwin) :
    QFileDialog(mwin, tr("Save graph"), QDir::currentPath(), "*;;*.xvgr")
{
    mainWindow = mwin;

    this->setOptions(QFileDialog::DontUseNativeDialog);
    this->setAcceptMode(QFileDialog::AcceptSave);
    this->setFileMode(QFileDialog::AnyFile);
    this->setDefaultSuffix("xvgr");
    this->setModal(true);
}

void FileSaveAll::accept() {
    // There are two sources for accept(); a buttonbox, and the filechooser
    // frame. We do not want to accept on frame click. Keypresses take buttons
    if (sender()->inherits("QFrame")) {
        return;
    }
    QFileDialog::accept();

    QStringList files = this->selectedFiles();
    if (files.size() == 0) return;

    QString outformat("%g %g");

    QString file = files[0];

    mainWindow->setFile(directory().absolutePath(), files[0]);
    mainWindow->setLastDirectory(directory());
    QString message = "Saved file: " + mainWindow->fullFileName();
    mainWindow->statusBar()->showMessage(message, 2000);

    do_writesets(MAXGRAPH, -1, -1, file.toUtf8().data(), outformat.toUtf8().data());
}
