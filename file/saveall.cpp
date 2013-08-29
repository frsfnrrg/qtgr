#include "file/saveall.h"
#include "base/globals.h"


FileSaveAll::FileSaveAll(MainWindow *mwin) :
    QFileDialog(mwin, tr("Save graph"), QDir::currentPath(), "*")
{
    mainWindow = mwin;

    this->setOptions(QFileDialog::DontUseNativeDialog);
    this->setAcceptMode(QFileDialog::AcceptSave);
    this->setFileMode(QFileDialog::AnyFile);
}

void FileSaveAll::accept() {
    QFileDialog::accept();
    QStringList files = this->selectedFiles();
    if (files.size() == 0) return;

    QString outformat("%g %g");

    QString file = files.at(0);
    if (!file.contains(QChar('.'))) {
        file.append(".gr");
    }

    do_writesets(MAXGRAPH, -1, -1, file.toAscii().data(), outformat.toAscii().data());
}
